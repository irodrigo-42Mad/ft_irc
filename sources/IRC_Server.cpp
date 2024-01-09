/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:59:21 by irodrigo          #+#    #+#             */
/*   Updated: 2024/01/09 13:14:59 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRC_Server.hpp"
# include "IRC_ACommand.hpp"
# include "IRC_Message.hpp"
# include "IRC_Utils.hpp"
# include "IRC_User.hpp"
# include <exception>
# include "console.hpp"

IRC_Server::IRC_Server() {}

IRC_Server::IRC_Server(char *port, const std::string &password)
		: _port(port)
		, _password(password)
    , _serverName("ircserv")
    , _host("127.0.0.1")
    , _MOTD("")
    , _connectedClientsNum(0)
    , _die(false)
{
		//Console::setLogLevel(LOGLEVEL_DEBUG);
    if (!_createServerSocket()) {
			std::cout << "no es posible inicializar el socket" << std::endl;
			return ;
    }
		if (!listen(10)) {
			std::cout << "No se puede abrir el puerto" << std::endl;
			return ;
		}

    fillMOTDMsg("./images/ascii-art5.txt");
    _fillCommands();
    
    std::time_t now = std::time(NULL);
    std::tm     *localTime = std::localtime(&now);

    std::cout << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec //solo de momento
              << std::endl;

		this->_createPoll();
}

IRC_Server::~IRC_Server()
{
    /* recorrer la lista de FDS y ver el nivel de registro, si es no registrado eliminamos de FD
    solamente, sino, habrá que eliminarlo de todas las posiciones en las que está registrado.
    */
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
    std::cout << "listener: " << this->_serverFd << std::endl;
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
    socklen_t			addrlen;
		int						newFd;
		IRC_User*			user = NULL;

		// Main loop
    while (!this->_die || !this->_usersByFd.empty())
    {
        int poll_count = poll(this->_pfds, this->_connectedClientsNum, -1);
        if (poll_count < 0)
        {
            if (poll_count == -1)
                ft_err_msg("Server::start fatal server error", ERR_COMPLETELY_SCREWED, 1);
            else if (poll_count == 0)
                ft_err_msg("Server::start timeout error", ERR_COMPLETELY_SCREWED, 1);
            exit(1);
        }

        // Run through the existing connections looking for data to read
        for (int i = 0; i < this->_connectedClientsNum; ++i)    // Check if someone's ready to read
        {
						if (this->_pfds[i].revents)
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
                        IRC_User *newUser = this->_createUser(newFd, &remoteaddr);
                        std::cout << newUser->getFd() << std::endl;
                        
                        //addToPfds(&this->_clients, newFd, &this->_connectedClientsNum, &fdMaxSize);
                        //sendMOTDMsg(newFd); //¿qué hacemos si no se manda?
                    }
                }
                else                        // If not the listener, we're just a regular client
                {
                    // if (this->_checkClientTime(user))
                    // {
                            // std::cout << "me encuentro viendo el tiempo" << std::endl;
                    // }
                    this->_readFromUser(user);
                }   // END handle data from client
            }       // END got ready-to-read from poll()
						if (this->_pfds[i].revents & POLLOUT)
						{
								this->_sendToUser(user);
								this->_handleDeletionAndDisconnect(user);
						}
				}						// END looping through file descriptors
    }								// END for(;;)--and you thought it would never end!
}

void IRC_Server::_handleDeletionAndDisconnect(IRC_User* user)
{
	if (user->_deleteMarked && user->_inputBuffer.empty())
		this->_deleteUser(user);
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
		//ERROR socket desconectado, hay que gestionarlo
		;
	buffer.erase(0, bytesSent);
}

void IRC_Server::_readFromUser(IRC_User* user)
{
		char buffer[SOCKET_BUFFER + 1];
    
		if (user->deleteMarked())
				return ;
    //std::cout << senderUser->getName() << std::endl;
    //if (!senderUser)
	//  	throw std::runtime_error("User not exists");

		int nbytes = recv(user->getPollPosition()->fd, buffer, SOCKET_BUFFER, 0);

    if (nbytes <= 0)        // Got error or connection closed by client
    {
        if (nbytes == 0)    // Connection closed
            std::cout << "pollserver: Socket " << user->getFd() << " hung up" << std::endl;
        else
            ft_err_msg("can not receive client data", ERR_STILL_SAVED, 2);
        this->_deleteUser(user);
    }
    else                    // We got some good data from a client
    {
        buffer[nbytes] = '\0';
  	    user->addReceiveData(buffer);
  	    //TODO: Deberíamos verificar que buffer tiene un \r\n en lugar de verificar
  	    //todo lo que ha recibido hasta ese momento el cliente. Eso ya se verificó
  	    //en operaciones anteriores.
  	    this->_processUserCommand(user);
    }
}

void IRC_Server::_processUserCommand(IRC_User* user) {
		size_t position;
		std::string& mydata = user->_inputBuffer;
    //std::cout << user->getBuffer();
    
    // para que pruebes todo el contenido, cambia mydata, por el comando que quieres probar, yo, esta tarde
    // te entregaré un parser básico que deberia ejecutar ya todo
    // descomenta estas primera linea para pruebas y pon tu comando entre "" (te incluyo un ejemplo)
    // deberia de parsearse del todo.
    
    //   IRC_Message procesed = IRC_Message(user, this, "NICK hola");
    //   this->_runCommand(procesed);
    
    if ((position = mydata.find("\r\n")) != std::string::npos)
    {
				//std::cout << "my data = $" << mydata << "$ " << position <<  std::endl;
				//TODO: Falta acortar el comando a 510
        IRC_Message procesed = IRC_Message(user, this, mydata);

        this->_runCommand(procesed);
				mydata.erase(0, position + 2);
    }
    /*
    else
        std::cout << "incomplete command" << std::endl;
    */
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
		IRC_Server::commandsIterator it = this->_commandsByName.find(toUpper(name));

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

void IRC_Server::send(const IRC_Server* server, const std::string& data)
{
		this->send(":" + server->getServerName() + " " + data);
}

void IRC_Server::send(const IRC_User* user, const std::string& data)
{
		this->send(":" + user->getMask() + " " + data);
}

void IRC_Server::shutdown(const IRC_User* user, const std::string& /*msg*/)
{
		this->_die = true;
		this->send("ERROR :Closing Link: " + user->getName() + "[" + user->getHost() + "] (Oper request: DIE)");
}

void IRC_Server::_delFromPfds(struct pollfd* pollPosition)
{
    // Copy the one from the end over this one
    struct pollfd* last = this->_pfds + this->_connectedClientsNum - 1;

		*pollPosition = *last;
		--this->_connectedClientsNum;
}

IRC_User* IRC_Server::_createUser(int fd, struct sockaddr_storage* addrStorage)
{
		char remoteIP[INET_ADDRSTRLEN];
    struct pollfd* pollPosition = this->_addToPfds(fd);
		IRC_User* user = new IRC_User(pollPosition);

		inet_ntop(addrStorage->ss_family, getInAddr((struct sockaddr *)addrStorage), remoteIP, INET_ADDRSTRLEN);
		user->setHost(remoteIP);
		this->_usersByFd[fd] = user;

		Console::debug << "New connection accepted. fd " << fd << std::endl;
	
//		co << "paco paco" << "porras porras" << 44 << std::endl;
		//Console::dd << "New connection accepted. FD: " << fd;
		return (user);
}

void IRC_Server::_deleteUser(IRC_User* user)
{
		this->_usersByFd.erase(user->getFd());
		if (!user->getName().empty())
		{
				this->_usersByName.erase(toUpperNickname(user->getName()));
		}
		this->_delFromPfds(user->getPollPosition());
    ::close(user->getFd());
    delete user;
}

IRC_Channel* IRC_Server::createChannel(const std::string& name, IRC_User* user)
{
    IRC_Channel* channel = new IRC_Channel(user, name);

    this->_channelsByName[name] = channel;
    return channel;
}

void IRC_Server::deleteChannel(IRC_Channel* channel)
{
		this->_channelsByName.erase(channel->getName());	
}


bool IRC_Server::setRegisteredUser(IRC_User& user)
{
	// ?? check pong valid value
    if (!user.getName().empty() && !user.getIdent().empty() && user.getAccess() == 0)
	{
		// creemos que tenemos que hacer esto aqui
        // this->_checkClientTime(&user);
        
        
        // ToDo: lanzar un ping, ya veremos como y contar tiempo
        // if ping correcto y pong a tiempo setAccess = 1
        // llamar a un pong


        //TODO: check password?  and.... return function can be boolean?
		user.setAccess(1);
		return true;
	}
	return false;
}  

bool IRC_Server::quitUser(IRC_User* user, const std::string& text)
{
    const IRC_Channel::usersSetType* commonUsers = user->getCommonUsersExcept(user);
    std::string reply = user->getMask() + " QUIT :" + text;
    
    //IRC_Message message(user, this, "QUIT :" + text);
    for (IRC_Channel::usersSetConstIterator it = commonUsers->begin(); it != commonUsers->end(); ++it)
    {
        (*it)->send(reply);
    }
    user->send("ERROR :[" + text + "]");
    user->markForDelete();
    //this->_deleteUser(user);
    delete commonUsers;
    return true;
}

bool IRC_Server::killUser(const IRC_User* user, IRC_User* targetUser, const std::string& text)
{
		return this->quitUser(targetUser, "Killed by " + user->getName() + ": " + text);
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

void    IRC_Server::sendMOTDMsg(IRC_User* user)  //esto hay que leerlo de línea en línea e ir imprimiéndolo
{
    std::string MOTD = this->_MOTD;
    std::stringstream ss(MOTD);
    std::string line;
    
    // inicio del MOTD
    line = ":" + this->getServerName() + " " + RPL_MOTDSTART(user->getName(), this->getServerName());
    user->send(line);
    line = "";
    //int i = 0;
    
    while (std::getline(ss, line))
    {
        //user->sendMessage(":" + this->getServerName() + " " + RPL_MOTD(user->getName(), line)); // message 372 per line
        std::string msgline  = ":" + this->getServerName() + " " + RPL_MOTD(user->getName(), line);
        //std::cout << "en la linea : " << i << ": " <<  line << std::endl;
        user->send(msgline);
        //i++;
    }
    // finish MOTD
    line = ":" + this->getServerName() + " " + RPL_ENDOFMOTD(user->getName());
    user->send(line);
}

void    IRC_Server::sendWelcomeMsg(IRC_User* user)
{
    std::string line;
    
    line = ":" + this->getServerName() + " " + RPL_WELCOME(user->getMask());
    user->send(line);
    line = ":" + this->getServerName() + " " + RPL_YOURHOST(this->getServerName(), _version);
    user->send(line);
    line = ":" + this->getServerName() + " " + RPL_CREATED(__TIME__ + " " + __DATE__);
    user->send(line);
    line = ":" + this->getServerName() + " " + RPL_MYINFO(this->getServerName(), _version);
    user->send(line);  
}

IRC_Server::State 	IRC_Server::getState() const
{
	return (ALIVE);
}

bool IRC_Server::changeNameUser(IRC_User* user, const std::string& nickname)
{
	//if (this->findUserByName(nickname))
	//	return (false);
	//TODO: hay que actualizar la clave del mapa
	this->_usersByName.erase(toUpperNickname(user->_name));
	this->_usersByName[toUpperNickname(nickname)] = user;
	user->setName(nickname);
	return (true);
}

bool IRC_Server::addUserToChannel(IRC_User* user, IRC_Channel* channel)
{
	if (user->isInChannel(channel))
		return (false);
	user->addChannel(channel);
	channel->addUser(user);
	return (true);
}

bool IRC_Server::removeUserFromChannel(IRC_User* user, IRC_Channel* channel)
{
	if (!user->isInChannel(channel))
		return (false);

	user->removeChannel(channel);
	channel->removeUser(user);

	if (channel->empty())
		this->deleteChannel(channel);
	return (true);
}

void IRC_Server::_fillCommands() {
    this->_addCommand(new IRC_DieCommand);
    this->_addCommand(new IRC_InviteCommand);
    this->_addCommand(new IRC_JoinCommand);
    this->_addCommand(new IRC_KickCommand);
    this->_addCommand(new IRC_KillCommand);
    this->_addCommand(new IRC_ListCommand);
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

void IRC_Server::_addCommand(IRC_ACommand* command)
{
	this->_commandsByName[command->cmd] = command;
}

void IRC_Server::_runCommand(IRC_Message& message)
{
	IRC_ACommand* command = this->findCommandByName(message.getCmd());
	IRC_User& user = message.getUser();

    //std::cout << "comando" << std::endl;
	if (!command)
  {
			user.send(ERR_UNKNOWNCOMMAND(message.getCmd()));
			//Console::log(user.getName() + ": unknown command '" + message.getCmd() + "'");
			return ;
	}
	if (user.getAccess() < command->access)
  {
      user.send(ERR_NOPRIVILEGES);
			return ;
	}
    // std::cout << command->params << std::endl;
	if (message.size() < command->params)
  {
      std::string sourceEmpty = "*";
      if (user.getName().empty())
          user.send(ERR_NEEDMOREPARAMS(sourceEmpty, message.getCmd()));
      else
          user.send(ERR_NEEDMOREPARAMS(user.getName(), message.getCmd()));
			return ;
	}
	command->execute(message);
}

bool	IRC_Server::_checkClientTime(IRC_User *user)
{
    if (user->getAccess() != 0)
    {
        if (user->getUserTimeOut() && user->_getTime() + PINGTOUT < time(NULL))
        {
            user->setUserTimeout(time(NULL) + GRALTIMEOUT);
            // enviar el ping al usuario con PONG_STR
           
            // necesitamos un iterador para todos los usuarios cuyo tiempo se haya pasado
            // enviar a todos los usuarios un evento ping
            
        }
        else if (user->getUserTimeOut() && (user->getUserTimeOut() < time (NULL)))
        {
            user->send (ERR_PONG(user->getMask(), "[Ping timeout: " + std::to_string(PINGTOUT) + " seconds]"));
            this->quitUser(user, "Ping timeout");
            
            // cerrar usuarios por timeout                                                                                ok
            // reply  "ERROR :Closing link: (" + user->get_username() + "@" + user->get_host() + ") [Ping timeout]\r\n";  ok
            // send_all_user(REPLY);                                                                                      revisar
            // line = ":" + user->get_mask() + " QUIT :Ping timeout\r\n";                                                 ok
            // eliminar el usuario de todos los canales e informar de ello                                                ok
            // eliminar la instancia y fd del usuario                                                                     ok
            return (true);
        }
    }
    else // user is not registered in IRC_Server.
    {
        std::string message;
        
        if ((user->_getRegTime() + UNREGTOUT) <= time(NULL))
        {
            user->send (ERR_PONG(user->getMask(), "[Registration timeout]"));
            this->_deleteUser(user);
            return (true);
            // reply "PONG ERROR [Registration timeout]\r\n"  ok
            // send_all user(REPLY);                          ok
            // eliminar el usuario (no ha entrado en canales) ok
            // eliminar instancia y fd del usuario            ok
        }
    }
    return (false);
}

void    IRC_Server::channelList(IRC_User* user)
{
    std::string line;
    
    for (channelsNameConstIterator it = this->_channelsByName.begin(); it != this->_channelsByName.end(); ++it)
    {
        IRC_Channel *channel = (*it).second;
        //channel->getNumUsers();
        line = ":" + this->getServerName() + " " + RPL_LIST(channel->getName(), "mode", channel->getTopic());
        user->send(line);
    }
    line = ":" + this->getServerName() + " " + RPL_LISTEND;
    user->send(line);
}

void    IRC_Server::channelListByName(IRC_User* user, std::string name)
{
    std::string line;
    IRC_Channel *channel = this->findChannelByName(name);
    
    if (channel)
    {
        line = ":" + this->getServerName() + " " + RPL_LIST(channel->getName(), "mode", channel->getTopic());
        user->send(line);
    }
}

bool   IRC_Server::changeChannelTopic(IRC_User* user, IRC_Channel* channel, const std::string &topic)
{
    if (channel->getTopic() != topic)
    {
     //   channel->setUserTopic(user->getName());
     //   channel->setTimestampTopic(time(NULL));
        channel->setTopic(topic);
        //informar
        //(todos -> :mask TOPIC canal :value)
        channel->send(":" + user->getMask() + " TOPIC " + channel->getName() + " :" + topic);
        return (true);
    }
    return (false);
}

const std::map<std::string, IRC_Channel*> &IRC_Server::getChannels() const
{
    return (this->_channelsByName);
}

std::string	IRC_Server::getTimeStamp()
{
    return (tmToString(this->_myTimeStamp));
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
