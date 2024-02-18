/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:59:21 by irodrigo          #+#    #+#             */
/*   Updated: 2024/02/18 14:54:49 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC_Server.hpp"
#include "IRC_ACommand.hpp"
#include "IRC_Errors.hpp"
#include "IRC_Message.hpp"
#include "IRC_Utils.hpp"
#include "IRC_Response.hpp"
#include "IRC_Exception.hpp"
#include "terminal.hpp"

#include <signal.h>
#include <exception>
#include <sstream>

 void IRC_Server::_printfds(pollfd* fds, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		std::cout << i << ": " << fds[i].fd << std::endl;
	std::cout << "-----\n";

	int i = 1;
	for (IRC_Server::usersFdIterator it = this->_usersByFd.begin(); it != this->_usersByFd.end(); ++it, ++i)
	{
		std::cout << i << " -> " << it->second->getPollPosition()->fd << std::endl;
	}
	std::cout << "--------------\n";
}


bool IRC_Server::_forceDie = false;

IRC_Server::IRC_Server() {}

IRC_Server::IRC_Server(char *port, const std::string &password)
	: _port(port)
	, _password(password)
	, _serverName("irc.inconight.es")
	, _host("127.0.0.1")
	, _MOTD("")
	, _connectedClientsNum(0)
	, _die(false)
{
	Console::Console::setLogLevel(Console::LOGLEVEL_DEBUG);
	Console::Console::setDisplayManager(this);
	this->_setSignals();

	if (!_createServerSocket())
	{
		throw IRC_Exception("Unable initialize socket");
  }
	if (!listen(10))
	{
		throw IRC_Exception("Unable initialize port");
	}

	this->fillMOTDMsg("./images/ascii-art5.txt");
	this->_fillCommands();
	this->_createPoll();
}

IRC_Server::~IRC_Server()
{
	this->_clearUsers();
	this->_clearChannels();
	this->_clearCommands();
}

void IRC_Server::_clearCommands()
{
	for (commandsNameIterator it = this->_commandsByName.begin(); it != this->_commandsByName.end(); ++it)
	{
		delete it->second;
	}
}

void IRC_Server::_clearUsers()
{
	for (usersFdIterator it = this->_usersByFd.begin(); it != this->_usersByFd.end(); ++it)
	{
		delete it->second;
	}
}

void IRC_Server::_clearChannels()
{
	for (channelsNameIterator it = this->_channelsByName.begin(); it != this->_channelsByName.end(); ++it)
	{
		delete it->second;
	}
}

bool IRC_Server::_createServerSocket()
{
	struct addrinfo		hints;
	struct addrinfo*	res;
	const char  *serverPort = this->_port.c_str(); // Get char* pointer from the string std::string
	int rv;									// Control error output messages
	int yes = 1;							// For setsockopt() SO_REUSEADDR, below
	struct addrinfo *p;						// auxiliar variable for check listener lists

	std::memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;       		// Fill in my IP for me
	hints.ai_family = AF_INET;       		// Don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;   		// TCP stream sockets

	if ((rv = getaddrinfo(NULL, serverPort, &hints, &res)) != 0)
	{
        	fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        	return (false);	//exit no está permitida. Hay que cambiar esto.
	}
	for (p = res; p != NULL; p = p->ai_next)
	{
		this->_serverFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (this->_serverFd < 0)
			continue;

		// Lose the pesky "address already in use" error message
		setsockopt(this->_serverFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		// FIXME: bind debería recibir 0.0.0.0 como IP para, posteriormente, poner
		// el socket en estucha. Ahora mismo está usando 127.0.0.1, Esto hará
		// imposible que nadie desde fuera de la máquina pueda conectar.
		if (bind(this->_serverFd, p->ai_addr, p->ai_addrlen) < 0)
		{
			close(this->_serverFd);
			continue;
		}
		break;
	}
	freeaddrinfo(res); // All done with this
	if (p == NULL)
		return (false);
	return (true);
}

bool IRC_Server::listen(int backlog)
{
    // If we got here, it means we didn't get bound
	Console::debug << "listener: " << this->_serverFd << std::endl;
	if (::listen(this->_serverFd, backlog) == -1)
		return (false);
	return (true);
}

const std::string& IRC_Server::getPort() const
{
	return (this->_port);
}

const std::string& IRC_Server::getPassword() const
{
	return (this->_password);
}

const std::string& IRC_Server::getServerName() const
{
	return (this->_serverName);
}

const std::string IRC_Server::getMOTD() const
{
	return (this->_MOTD);
}

void IRC_Server::_createPoll()
{
	// Add the server listener to set
	this->_pfds[0].fd = this->_serverFd;
	this->_pfds[0].events = POLLIN; // Ready to read on incoming connection
	this->_connectedClientsNum = 1; // For the listener
}

void    IRC_Server::start()
{
	struct sockaddr_storage remoteaddr; // client address
	socklen_t				addrlen;
	int						newFd;
	IRC_User*				user;

	this->_startTime = std::time(NULL);

	terminal.disableEcho();
	terminal.hideCursor();

	Console::log << "Server started (" << this->_host << ":" << this->_port << ")" << std::endl;

	// Main loop
	//Console::Console::displayBottom();
	while (!this->_die || !this->_usersByFd.empty())
	{
		int poll_count = poll(this->_pfds, this->_connectedClientsNum, 200);

		if (poll_count < 0 && IRC_Server::_forceDie)
		{
			this->_die = true;
			continue ;
		}

		// Run through the existing connections looking for data to read
		for (int i = 0; i < this->_connectedClientsNum; ++i)    // Check if someone's ready to read
		{
			//if (this->_pfds[i].revents)
			user = this->findUserByFd(this->_pfds[i].fd);
			if (this->_pfds[i].revents & POLLIN)             // We got one!!
			{
				if (this->_pfds[i].fd == this->_serverFd)    // If listener is ready to read, handle new connection
				{
					addrlen = sizeof(remoteaddr);
					newFd = accept(this->_serverFd, (struct sockaddr *)&remoteaddr, &addrlen);
					if (newFd == -1)
						ft_err_msg("can not allocate socket client information", ERR_STILL_SAVED, 2);
					//perror("accept");
					else
					{   
						this->_createUser(newFd, &remoteaddr);
						//addToPfds(&this->_clients, newFd, &this->_connectedClientsNum, &fdMaxSize);
						//sendMOTDMsg(newFd); //¿qué hacemos si no se manda?
					}
				}
				else                        // If not the listener, we're just a regular client
				{
					this->_readFromUser(user);
				}   // END handle data from client
			}       // END got ready-to-read from poll()
			if (user && this->_checkClientTime(user))
			{
				//std::cout << "me encuentro viendo el tiempo" << std::endl;
			}        
			if (this->_pfds[i].revents & POLLOUT)
			{
				this->_sendToUser(user);
				this->_handleDeletionAndDisconnect(user);
			}
			if (IRC_Server::_forceDie)
			{
				IRC_Server::_forceDie = false;
				this->shutdown("Server stopped");
			}        
		}						// END looping through file descriptors
		//Console::Console::displayBottom();
	}							// END for(;;)--and you thought it would never end!
	terminal.clearCurrentRow();
	terminal.showCursor();
	terminal.enableEcho();
}

void IRC_Server::_handleDeletionAndDisconnect(IRC_User* user)
{
	if (user->_deleteMarked && user->_inputBuffer.empty())
	{	
		this->_deleteUser(user);
	}
}

void IRC_Server::_sendToUser(IRC_User *user)
{
	int bytesToSend;
	int bytesSent;
	std::string& buffer = user->_outputBuffer;

	if (buffer.size() > SOCKET_BUFFER)
		bytesToSend = SOCKET_BUFFER;
	else
		bytesToSend = buffer.size();

	bytesSent = ::send(user->getPollPosition()->fd, buffer.c_str(), bytesToSend, 0);

	if (bytesSent == bytesToSend)
		user->_pollPosition->events &= ~POLLOUT;
	if (bytesSent == -1)
		Console::debug << "Error writing to client (TODO, handle it!)" << std::endl;
		//ERROR socket desconectado, hay que gestionarlo
	buffer.erase(0, bytesSent);
}

void IRC_Server::_readFromUser(IRC_User* user)
{
	char buffer[SOCKET_BUFFER + 1];
	int nbytes;

	if (user->deleteMarked())
		return ;
	nbytes = recv(user->getPollPosition()->fd, buffer, SOCKET_BUFFER, 0);
	if (nbytes <= 0)        // Got error or connection closed by client
	{
		if (nbytes == 0)    // Connection closed
			Console::debug << "pollserver: Socket " << user->getFd() << " hung up" << std::endl;
		else
		{
			Console::error << "Can not receive client data" << std::endl;
			this->_die = true;
			return ;
		}
		this->_deleteUser(user);
	}
	else // We got some good data from a client
	{
		buffer[nbytes] = '\0';
		user->addReceiveData(buffer);
		this->_processUserCommand(user);
	}
}

void IRC_Server::_processUserCommand(IRC_User* user)
{
	size_t position;
	size_t command_lenght;
	std::string& mydata = user->_inputBuffer;
	//std::cout << user->getBuffer();

	// para que pruebes todo el contenido, cambia mydata, por el comando que quieres probar, yo, esta tarde
	// te entregaré un parser básico que deberia ejecutar ya todo
	// descomenta estas primera linea para pruebas y pon tu comando entre "" (te incluyo un ejemplo)
	// deberia de parsearse del todo.

	//   IRC_Message procesed = IRC_Message(user, this, "NICK hola");
	//   this->_runCommand(procesed);

	while ((position = mydata.find("\r\n")) != std::string::npos)
	{
		if (position > LINELEN - 2)
		{
			command_lenght = LINELEN - 2;
		}
		else
		{
			command_lenght = position;
		}
	
		IRC_Message procesed = IRC_Message(user, this, mydata.substr(0, command_lenght));

		this->_runCommand(procesed);
		mydata.erase(0, position + 2);
  }
}

IRC_User* IRC_Server::findUserByName(const std::string& name)
{
	IRC_Server::usersNameIterator it = this->_usersByName.find(toUpperNickname(name));

	if (it == this->_usersByName.end())
	{
		return (NULL);
	}
	return (it->second);
}

bool	IRC_Server::findInvitedUserToAChannel(IRC_User& user, const std::string& channelName)
{
	for (IRC_Server::invitedChannelsNameConstIterator it = this->_invitedByName.begin(); it != this->_invitedByName.end(); ++it)
	{
		if ((*it).first == &user && (*it).second->getName() == channelName)
			return (true);
	}
	return (false);
}

void	IRC_Server::insertInvitedUser(IRC_User& user, IRC_Channel& channel)
{	
	this->_invitedByName.insert(std::make_pair(&user, &channel));
	Console::log << "he llenado con " << user.getName() << std::endl;
}

void	IRC_Server::deleteInvitedUser(IRC_User& user, const std::string& channelName)
{
	for (IRC_Server::invitedChannelsNameIterator it = this->_invitedByName.begin(); it != this->_invitedByName.end(); ++it)
	{
		if ((*it).first == &user && (*it).second->getName() == channelName)
		{	
			this->_invitedByName.erase(it);
			break ;
		}
	}
}

IRC_User* IRC_Server::findUserByFd(int fd)
{
	IRC_Server::usersFdIterator it = this->_usersByFd.find(fd);

	if (it == this->_usersByFd.end())
	{
		return (NULL);
	}
	return (it->second);
}

IRC_Channel* IRC_Server::findChannelByName(const std::string& name)
{
	IRC_Server::channelsNameIterator it = this->_channelsByName.find(name);

	if (it == this->_channelsByName.end())
	{
		return (NULL);
	}
	return (it->second);
}

IRC_ACommand* IRC_Server::findCommandByName(const std::string& name)
{
	IRC_Server::commandsNameIterator it = this->_commandsByName.find(toUpper(name));

	if (it == this->_commandsByName.end())
	{
		return (NULL);
	}
	return (it->second);
}

void    IRC_Server::userPolloutByFd(int fd)
{
	this->_pfds[fd].events = POLLOUT;
}

void    *IRC_Server::getInAddr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in *)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

struct pollfd* IRC_Server::_addToPfds(int newfd)
{
	int pos = this->_connectedClientsNum;

	if (this->_connectedClientsNum == MAX_CLIENTS)
	{
		::send(newfd, "Too many users connected", 25, 0);
		::close(newfd);
		return NULL;
	}
	this->_pfds[pos].fd = newfd;
	this->_pfds[pos].events = POLLIN; // Verificar lectura disponible
	++this->_connectedClientsNum;
	return this->_pfds + pos;
}

void IRC_Server::send(const std::string& data)
{
	for (usersFdIterator it = this->_usersByFd.begin(); it != this->_usersByFd.end(); ++it)
	{
		it->second->send(data);
	}
}

void IRC_Server::send(const IRC_Server& server, const std::string& data)
{
	this->send(":" + server.getServerName() + " " + data);
}

void IRC_Server::send(const IRC_User& user, const std::string& data)
{
	this->send(":" + user.getMask() + " " + data);
}

void IRC_Server::shutdown(const std::string& message)
{
	for (usersFdIterator it = this->_usersByFd.begin(); it != this->_usersByFd.end(); ++it)
	{
		this->quitUser(*it->second, message);
	}
	this->_die = true;
}

/* esta funcion se encarga de localizar el último FD y copiar ese valor a la posición de quien se acaba de ir
   si tenemos 4 conexiones
   index	fd
   # 0  	4
   # 1		5
   # 2		6
   # 3		7

   si se va el usuario 1, se copia el valor del 3 a esa posición. 1 > 7
*/

void IRC_Server::_delFromPfds(struct pollfd* pollPosition)
{
	// Copy the one from the end over this one
	struct pollfd* last = this->_pfds + this->_connectedClientsNum - 1;
	IRC_User* lastUser = this->findUserByFd(last->fd);

	*pollPosition = *last;
	lastUser->setPollPosition(pollPosition);
	--this->_connectedClientsNum;
}

IRC_User* IRC_Server::_createUser(int fd, struct sockaddr_storage* addrStorage)
{
	char remoteIP[INET_ADDRSTRLEN];
	struct pollfd* pollPosition = this->_addToPfds(fd);

	if (!pollPosition)
		return (NULL);
	IRC_User* user = new IRC_User(pollPosition);
	this->_printfds(this->_pfds, this->_connectedClientsNum);

	inet_ntop(addrStorage->ss_family, getInAddr((struct sockaddr *)addrStorage), remoteIP, INET_ADDRSTRLEN);
	user->setHost(remoteIP);
	this->_usersByFd[fd] = user;

	Console::debug << "New connection accepted (" << fd << ")" << std::endl;
	
//		co << "paco paco" << "porras porras" << 44 << std::endl;
		//Console::dd << "New connection accepted. FD: " << fd;
	return (user);
}

void IRC_Server::_deleteUser(IRC_User* user)
{
	this->_usersByFd.erase(user->getFd());
	if (user->getName() != "*")
	{
		// erase all invitations asociated to an user nickname
		for (IRC_Server::invitedChannelsNameIterator it = this->_invitedByName.begin(); it != this->_invitedByName.end();)
		{
			//Console::log << "Invited user: " << (*it).first << " invited to " << (*it).second->getName() << std::endl;
			if ((*it).first == user)
			{
				this->_invitedByName.erase(it++);
			}
			else
				++it;
		}
		this->_usersByName.erase(toUpperNickname(user->getName()));
	}
	Console::debug << "User " << user->getMask() << " destroyed (" << user->getFd() << ")" << std::endl;
	::close(user->getFd());
	
	this->_delFromPfds(user->getPollPosition());
	this->_printfds(this->_pfds, this->_connectedClientsNum);
	delete user;
}

IRC_Channel* IRC_Server::createChannel(const std::string& name, IRC_User& user)
{
	IRC_Channel* channel = new IRC_Channel(name, user);

	this->_channelsByName[name] = channel;
	Console::log << "User " << user.getMask() << " created the channel " << name << std::endl;
	return channel;
}

void IRC_Server::deleteChannel(IRC_Channel& channel)
{
	for (IRC_Server::invitedChannelsNameIterator it = this->_invitedByName.begin(); it != this->_invitedByName.end(); ++it)
	{
		//Console::log << "Invited user: " << (*it).first << " invited to " << (*it).second->getName() << std::endl;
		if ((*it).second == &channel)
		{
			this->_invitedByName.erase(it++);
		}
		else
			++it;
	}
	this->_channelsByName.erase(channel.getName());	
	Console::log << "Channel " << channel.getName() << " deleted" << std::endl;
	delete &channel;
}

bool IRC_Server::setPendingUser(IRC_User& user)
{
	std::string random = generateRandomText();

	if (user.getName() != "*" && !user.getIdent().empty() && user.getAccess() == UNREGISTERED)
	{
		if (this->_password != user.getPass())
		{
			user.reply(*this, ERR_PASSWDMISMATCH(user.getName()));
			this->quitUser(user, "Password incorrect");
			return false;
		}
		user.setAccess(PENDING);
		user._pingText = random;
		this->ping(&user, random);
		Console::log << "User " << user.getMask() << " pending" << std::endl;
		Console::debug << "PING >> " << random << std::endl;
		return true;
	}
	return false;
}  

bool IRC_Server::quitUser(IRC_User& user, const std::string& text)
{
	std::string message = text;

	if (message.empty())
		message = "Client exited";
    
	user.sendCommonUsersExceptMe(user, "QUIT", message);
	this->removeUserFromChannels(user);
	user.send("ERROR : Closing link: (" + user.getIdent() + "@" + user.getHost() + ") [" + message + "]");
	user.markForDelete();
	return true;
}

bool IRC_Server::killUser(const IRC_User& user, IRC_User& targetUser, const std::string& text)
{
		return this->quitUser(targetUser, "Killed by " + user._name + ": " + text);
}

void IRC_Server::fillMOTDMsg(const char *filename)
{
    std::ifstream file(filename, std::ios::in | std::ios::binary);  //Open the file in read mode

    if (file.is_open())
    {
        file.read(this->_MOTD, sizeof(this->_MOTD));
        this->_MOTD[file.gcount()] = '\0';  //Make sure that the string ends with a null character
        file.close();
        std::strncat(this->_MOTD, "Somos un equipo,\nvaliente y luchador,\n", sizeof(_MOTD) - std::strlen(_MOTD) - 1);
        std::strncat(this->_MOTD, "que defiende su IRC,\ncon el corazón.\n", sizeof(_MOTD) - std::strlen(_MOTD) - 1);
        std::strncat(this->_MOTD, "Los años pasando,\ny seguimos aquí,\n", sizeof(_MOTD) - std::strlen(_MOTD) - 1);
        std::strncat(this->_MOTD, "porque somos los currelas,\ny esto nunca va a morir ...\n", sizeof(_MOTD) - std::strlen(_MOTD) - 1);
    }
    else
        std::strncat(this->_MOTD, "Bienvenido al IRC de irodrigo e icastell\n\n", sizeof(_MOTD) - std::strlen(_MOTD) - 1);
}

void IRC_Server::sendMOTDMsg(IRC_User& user)  //esto hay que leerlo de línea en línea e ir imprimiéndolo
{
    std::string MOTD = this->_MOTD;
    std::stringstream ss(MOTD);
    std::string line;
    
    // inicio del MOTD
    line = ":" + this->getServerName() + " " + RPL_MOTDSTART(user.getName(), this->getServerName());
    user.send(line);
    line = "";
    //int i = 0;
    
    while (std::getline(ss, line))
    {
        //user->sendMessage(":" + this->getServerName() + " " + RPL_MOTD(user->getName(), line)); // message 372 per line
        std::string msgline  = ":" + this->getServerName() + " " + RPL_MOTD(user.getName(), line);
        //std::cout << "en la linea : " << i << ": " <<  line << std::endl;
        user.send(msgline);
        //i++;
    }
    // finish MOTD
    line = ":" + this->getServerName() + " " + RPL_ENDOFMOTD(user.getName());
    user.send(line);
}

void    IRC_Server::sendWelcomeMsg(IRC_User& user)
{
    std::stringstream ss;
    
		ss << "CHANLIMIT=" << CHANLIMIT << " ";
		ss << "CHANNELLEN=" << CHANNELLEN << " ";
		ss << "CHANTYPES=" << CHANTYPES << " ";
		ss << "KEYLEN=" << KEYLEN << " ";
		ss << "KICKLEN=" << KICKLEN << " ";
		ss << "LINELEN=" << LINELEN << " ";
		ss << "MAXTARGETS=" << MAXTARGETS << " ";
		ss << "MODES=" << MODES << " ";
		ss << "NAMELEN=" << NAMELEN << " ";
		ss << "NETWORK=" << NETWORK << " ";
		ss << "NICKLEN=" << NICKLEN << " ";
		ss << "TOPICLEN=" << TOPICLEN << " ";
		ss << "USERLEN=" << USERLEN << " ";

    user.reply(*this, RPL_WELCOME(user.getName(), NETWORK, user.getMask()));
    user.reply(*this, RPL_YOURHOST(user.getName(), this->getServerName(), IRC_VERSION));
    user.reply(*this, RPL_CREATED(user.getName(), __TIME__ + " " + __DATE__));
    user.reply(*this, RPL_MYINFO(user.getName(), this->getServerName(), IRC_VERSION));
    user.reply(*this, RPL_ISUPPORT(user.getName(), ss.str()));
}

IRC_Server::State	IRC_Server::getState() const
{
	return (ALIVE);
}

IRC_Response	IRC_Server::changeNameUser(IRC_User& user, const std::string& nickname)
{
	if (!checkNickname(nickname))
	{
		return (ERRONEOUS_NICK);
	}
	if (user._name == nickname)
	{
		return (NONE);
	}
	if (toUpperNickname(user._name) != toUpperNickname(nickname))
	{
		if (this->findUserByName(nickname))
		{
				return (NICK_IN_USE);
		}
	}
	this->_usersByName.erase(toUpperNickname(user._name));
	this->_usersByName[toUpperNickname(nickname)] = &user;
	if (user._name != "*")
	{
		user.sendCommonUsers(":" + user.getMask() + " NICK " + nickname);
		Console::log << "User " << user._name << " change nick to " << nickname << std::endl;			
	}
	user.setName(nickname);
	return (SUCCESS);
}

IRC_Response	IRC_Server::addUserToChannel(IRC_User& user, IRC_Channel& channel)
{
	if (user.isInChannel(channel))
		return (ALREADY_IN_CHANNEL);
	user.addChannel(channel);
	channel.addUser(user);
	return (SUCCESS);
}

IRC_Response	IRC_Server::removeUserFromChannel(IRC_User& user, IRC_Channel& channel)
{
	if (!user.isInChannel(channel))
	{
		return (NOT_IN_CHANNEL);
	}

	user.removeChannel(channel);
	channel.removeUser(user);

	if (channel.empty())
	{
		this->deleteChannel(channel);
	}
	return (SUCCESS);
}

/*void	IRC_Server::removeUserInvitationToAChannel(IRC_User& user, IRC_Channel& channel)
{
	for (IRC_Server::invitedChannelsNameConstIterator it = this->_invitedByName.begin(); it != this->_invitedByName.end(); ++it)
	{
		//Console::log << "Invited user: " << (*it).first << " invited to " << (*it).second->getName() << std::endl;
		if ((*it).first == user && (*it).second == channel)
	 		this->_invitedByName.erase(it);
	}
}*/

void	IRC_Server::removeUserFromChannels(IRC_User& user)
{
	const channelsType& channels = user.getChannels();

	for (channelsIterator it = channels.begin(); it != channels.end(); ++it)
	{
		removeUserFromChannel(user, **it);
	}
}

IRC_Response	IRC_Server::joinUser(IRC_User& user, IRC_Channel& channel, const std::string& key)
{
	IRC_Response response;

	// ToDo: En pruebas  toavien en pruebas.
	// TODO: Aquí es donde hay que comprobar si ha sido invitado
	//      y, en caso afirmativo, saltar hasta addUserToChannel.
	if (!this->findInvitedUserToAChannel(user, channel.getName()))
	{
		if (channel.isBanned(user))
			return (USER_BANNED);
		if (channel.isFull())
			return (CHANNEL_IS_FULL);
		if (!channel.isSameKey(key))
			return (CHANNEL_KEY_MISMATCH);
		if (channel.hasInvite())
			return (INVITE_ONLY);
	}
	// modo i (invitacion para mañana) pendientes
	response = this->addUserToChannel(user, channel);
	if (response == SUCCESS)
	{
		channel.send(user, "JOIN " + channel.getName());
		deleteInvitedUser(user, channel.getName());	
	}
	return (response);
}

IRC_Response	IRC_Server::partUser(IRC_User& user, IRC_Channel& channel, const std::string& msg)
{
	IRC_Response response;

	response = this->removeUserFromChannel(user, channel);
	if (response == SUCCESS)
	{
		channel.send(user, "PART " + channel.getName(), msg);
		user.send(user, "PART " + channel.getName(), msg);
	}
	return (response);
}

IRC_Response	IRC_Server::kickUser(IRC_User& user, IRC_Channel& channel, const std::string& message)
{
	IRC_Response response;

	response = this->removeUserFromChannel(user, channel);
	if (response == SUCCESS)
	{
		channel.send(user, "KICK " + channel.getName(), message);
		user.send(user, "KICK " + channel.getName(), message);
	}	
    return (response);
}

void	IRC_Server::_fillCommands()
{
	this->_addCommand(new IRC_DieCommand);
	this->_addCommand(new IRC_InviteCommand);
	this->_addCommand(new IRC_JoinCommand);
	this->_addCommand(new IRC_KickCommand);
	this->_addCommand(new IRC_KillCommand);
	this->_addCommand(new IRC_ListCommand);
	this->_addCommand(new IRC_ModeCommand);
	this->_addCommand(new IRC_MOTDCommand);
	this->_addCommand(new IRC_NamesCommand);
	this->_addCommand(new IRC_NickCommand);
	this->_addCommand(new IRC_NoticeCommand);
	this->_addCommand(new IRC_OperCommand);
	this->_addCommand(new IRC_PartCommand);
	this->_addCommand(new IRC_PassCommand);
	this->_addCommand(new IRC_PingCommand);
	this->_addCommand(new IRC_PongCommand);
	this->_addCommand(new IRC_PrivMsgCommand);
	this->_addCommand(new IRC_QuitCommand);
	this->_addCommand(new IRC_TopicCommand);
	this->_addCommand(new IRC_UserCommand);
	this->_addCommand(new IRC_WelcomeCommand);
}

void	IRC_Server::_addCommand(IRC_ACommand* command)
{
	this->_commandsByName[command->cmd] = command;
}
//:server_name NUMERIC target 

void	IRC_Server::_runCommand(IRC_Message& message)
{
	IRC_ACommand* command = this->findCommandByName(message.getCmd());
	IRC_User& user = message.getUser();

    user.resetIdle();

	if (message.getCmd().empty())
	    return ;
	if (!command)
    {
		user.send(*this, ERR_UNKNOWNCOMMAND(user.getName(), message.getCmd()));
		//Console::log(user.getName() + ": unknown command '" + message.getCmd() + "'");
		return ;
	}

	if (user.getAccess() < command->access)
    {
        if (command->access == OPERATOR)
            user.send(*this, ERR_NOPRIVILEGES(user.getName()));
        else
            user.send(*this, ERR_NOTREGISTERED(user.getName(), command->cmd));
		return ;
	}
    // std::cout << command->params << std::endl;
	if (message.size() < command->params)
    {
        user.send(*this, ERR_NEEDMOREPARAMS(user.getName(), message.getCmd()));
		return ;
	}
	command->execute(message);
}

bool	IRC_Server::_checkClientTime(IRC_User *user)
{
    if (user->getAccess() <= PENDING) // user is not registered in IRC_Server.
    {
        std::string message;
        if (user->getPingTimeout() <= time(NULL))
        {
            //user->send(random);
            //user->send(ERR_PONG(user->getMask(), "[Registration timeout]"));
            this->quitUser(*user, user->getMask() + " [Registration timeout]");
            return (true);
            // reply "PONG ERROR [Registration timeout]\r\n"  ok
            // send_all user(REPLY);                          ok
            // eliminar el usuario (no ha entrado en canales) ok
            // eliminar instancia y fd del usuario            ok
        }
    }
    else
    {
        if (!user->getPingTimeout() && user->getIdleTime() < time(NULL))
        {
            this->ping(user, this->getServerName());
            user->setPingTimeout(PINGTOUT);
            // enviar el ping al usuario con PONG_STR
           
            // necesitamos un iterador para todos los usuarios cuyo tiempo se haya pasado
            // enviar a todos los usuarios un evento ping
            
        }
        else if (user->getPingTimeout() && user->getPingTimeout() < time(NULL))
        {
            
            			//TODO: enviar mensaje
			std::stringstream ss;

			ss << "[Ping timeout: " << PINGTOUT << " seconds]";
            user->send(ERR_PONG(user->getMask(), ss.str()));
            this->quitUser(*user, "Ping timeout");
            
            // cerrar usuarios por timeout                                                                                ok
            // reply  "ERROR :Closing link: (" + user->get_username() + "@" + user->get_host() + ") [Ping timeout]\r\n";  ok
            // send_all_user(REPLY);                                                                                      revisar
            // line = ":" + user->get_mask() + " QUIT :Ping timeout\r\n";                                                 ok
            // eliminar el usuario de todos los canales e informar de ello                                                ok
            // eliminar la instancia y fd del usuario                                                                     ok
            return (true);
        }
    }
    return (false);
}

void    IRC_Server::channelList(IRC_User& user)
{
	std::ostringstream oss;
	std::string line;
    
	for (channelsNameConstIterator it = this->_channelsByName.begin(); it != this->_channelsByName.end(); ++it)
	{
		IRC_Channel *channel = (*it).second;

		oss << channel->getNumUsers();
		user.reply(*this, RPL_LIST(user.getName(), channel->getName(), oss.str(), "[" + channel->getModes(user) + "] " + channel->getTopic()));
		oss.str("");
		oss.clear();
	}
	user.reply(*this, RPL_LISTEND(user.getName()));
}

void	IRC_Server::channelListByName(IRC_User& user, std::string name)
{
	std::ostringstream oss;
	std::string line;
	IRC_Channel *channel = this->findChannelByName(name);
    
	if (channel)
	{
		oss << channel->getNumUsers();
        user.reply(*this, RPL_LIST(user.getName(), channel->getName(), oss.str(), "[" + channel->getModes(user) + "] " + channel->getTopic()));
	}
}

bool	IRC_Server::changeChannelTopic(IRC_User& user, IRC_Channel& channel, const std::string &topic)
{
    if (channel.getTopic() != topic)
    {
     //   channel->setUserTopic(user->getName());
     //   channel->setTimestampTopic(time(NULL));
        channel.setTopic(user, topic);
        //informar
        //(todos -> :mask TOPIC canal :value)
        channel.send(":" + user.getMask() + " TOPIC " + channel.getName() + " :" + topic);
        return (true);
    }
    return (false);
}

void	IRC_Server::displayBottom(std::stringstream& ss, int /*width*/)
{
		struct tm	*timeinfo;
		time_t		timestamp = std::difftime(std::time(NULL), this->_startTime);
		char buffer[9];

		timeinfo = gmtime(&timestamp);
		strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);

		ss << "[ Unregistered users: " << this->_usersByFd.size() - this->_usersByName.size() << " ]  "; 
		ss << "[ Registered users: " << this->_usersByName.size() << " ]  ";
		ss << "[ Opers: " << this->_opers.size() << " ]  ";
		ss << "[ Open channels: " << this->_channelsByName.size() << " ]  ";
		ss << "[ Invites: " << this->_invitedByName.size() << " ]  ";
		ss << "[ Load commands: " << this->_commandsByName.size() << " ]  ";
		ss << "[ Uptime: " << buffer << " ]";
}

void IRC_Server::_sigintHandler(int)
{
	IRC_Server::_forceDie = true;	
}

void IRC_Server::_setSignals()
{
	signal(SIGINT, IRC_Server::_sigintHandler);
}

const IRC_Server::channelsNameType &IRC_Server::getChannels() const
{
    return (this->_channelsByName);
}

void IRC_Server::ping(IRC_User *sender, std::string const &message)
{
    sender->send("PING :" + message);
}

void IRC_Server::pong(IRC_User *sender, std::string const &message)
{
    sender->reply(*this, "PONG " + this->getServerName() + " :" + message);
}

// void                IRC_Server::sendMSG(std::string message, int type)
// {
//     // We got some good data from a client
//     for (int j = 0; j < this->_connectedClientsNum; j++)
//     {
//         // Send to everyone!
//         int destFd = this->_clients[j].fd;

//         // Except the listener and ourselves
//         if (destFd != this->_srvFd && destFd != senderFd)
//         {
//             if (send(destFd, message, nbytes, 0) == -1)
//                 perror("send");
//         }
//     }

// }
// IRC_Server::State	IRC_Server::getState()
// {
// 	return (this->srvState); // colocar el valor al devolver el estado
// }

// void 	IRC_Server::setState(State myst)
// {
// 	this->srvState = myst;
// }
/*int IRC_Server::getServerFd() const
{
    return (this->_serverFd);
}

int IRC_Server::getConnectedClientsNum() const
{
    return (this->_connectedClientsNum);
}

void    IRC_Server::setServerFd(int serverSocket)
{
    this->_serverFd = serverSocket;
}*/

/* hay que revisar el código de esta funcion
void    IRC_Server::setClients(struct pollfd *clients)
{
    // revisar como tiene que quedar la struct pollfd
    //this->_clients = clients;
}*/
/*
bool    IRC_Server::initializeSocket()
{
    int srvFd = _myAddrInfo(this->_port);

    if (srvFd < 0)
        return (false);
    else
        this->_serverFd = srvFd;
    return (true);
}
*/
/*int IRC_Server::findPollPosition(IRC_User* user)
{
    for (int i = 0; i < this->_connectedClientsNum; i++)
    {
		if (this->_pfds[i].fd == user->getFd())
			return (i);
    }
	return (-1);
}*/
