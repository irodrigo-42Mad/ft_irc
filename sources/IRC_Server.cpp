/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:59:21 by irodrigo          #+#    #+#             */
/*   Updated: 2023/12/14 21:14:17 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRC_Server.hpp"
# include "IRC_ACommand.hpp"
# include "IRC_Message.hpp"
# include "IRC_Utils.hpp"
# include <exception>

IRC_Server::IRC_Server() {}

IRC_Server::IRC_Server(char *port, const std::string &password):
    _port(port), _password(password), _serverName("ircserv"), _host("127.0.0.1"),
    _MOTD(""), _connectedClientsNum(0)
{
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

	createPoll();
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

/*std::string IRC_Server::getMOTD() const
{
    return (this->_MOTD);
}

int IRC_Server::getServerFd() const
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
void IRC_Server::createPoll()
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
    char					remoteIP[INET_ADDRSTRLEN];
	int     newFd;

    // estas variables no se usan por estar incluidas en la struct de usuario
	//int     fdMaxSize = MAX_CLIENTS;
	//char    buf[256];

	// Main loop
    while (42)
    {
        int poll_count = poll(this->_pfds, this->_connectedClientsNum, -1);
        if (poll_count < 0)
        {
            if (poll_count == -1)
                ft_err_msg("fatal server error", ERR_COMPLETELY_SCREWED, 1);
            else if (poll_count == 0)
                ft_err_msg("timeout error", ERR_COMPLETELY_SCREWED, 1);
            exit(1);
        }

        // Run through the existing connections looking for data to read
        for (int i = 0; i < this->_connectedClientsNum; i++)    // Check if someone's ready to read
        {
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
                    {   addToPfds(newFd);
                        //addUser
                        // añadir el usuario a la estructura y mapas de usuario
                        IRC_User *newUser = createUser();
                        std::cout << newUser->getFd() << std::endl;
                        
                        //addToPfds(&this->_clients, newFd, &this->_connectedClientsNum, &fdMaxSize);
                        std::cout << "pollserver: New connection from " << inet_ntop(remoteaddr.ss_family,
                            getInAddr((struct sockaddr *)&remoteaddr),
                            remoteIP, INET_ADDRSTRLEN) << " on socket " << newFd << std::endl;
                        sendMOTDMsg(newFd); //¿qué hacemos si no se manda?
                    }
                }
                else                        // If not the listener, we're just a regular client
                {
                    this->_readFromUser(this->_pfds[i].fd);
                }   // END handle data from client
            }       // END got ready-to-read from poll()
        }           // END looping through file descriptors
    }               // END for(;;)--and you thought it would never end!
}

void IRC_Server::_readFromUser(int fd) {
	char buffer[1024 + 1];
	IRC_User* senderUser = this->findUserByFd(fd);
    
    //std::cout << senderUser->getName() << std::endl;
    //if (!senderUser)
	//  	throw std::runtime_error("User not exists");

	int nbytes = recv(fd, buffer, 1024, 0);

    if (nbytes <= 0)        // Got error or connection closed by client
    {
        if (nbytes == 0)    // Connection closed
            std::cout << "pollserver: Socket " << senderUser->getFd() << " hung up" << std::endl;
        else
            ft_err_msg("can not receive client data", ERR_STILL_SAVED, 2);
        this->deleteUser(senderUser);
    }
    else                    // We got some good data from a client
    {
        buffer[nbytes] = '\0';
  	    senderUser->addReceiveData(buffer);
  	    this->_processUserCommand(senderUser);
    }
}

void IRC_Server::_processUserCommand(IRC_User* user) {
    std::string mydata = user->getBuffer();
    std::cout << user->getBuffer();
    
    // para que pruebes todo el contenido, cambia mydata, por el comando que quieres probar, yo, esta tarde
    // te entregaré un parser básico que deberia ejecutar ya todo
    // descomenta estas primera linea para pruebas y pon tu comando entre "" (te incluyo un ejemplo)
    // deberia de parsearse del todo.
    
        IRC_Message procesed = IRC_Message(user, this, "NICK hola");
        this->_runCommand(procesed);
    
    /*std::cout << mydata.length();

    if (mydata.find("\r\n") != std::string::npos)
    {
        IRC_Message procesed = IRC_Message(user, this, mydata);
        this->_runCommand(procesed);
    }
    else
        std::cout << "incomplete command" << std::endl;*/
}

IRC_User* IRC_Server::findUserByName(const std::string& name) {
	IRC_Server::usersNameIterator it = this->_usersByName.find(name);

	if (it == this->_usersByName.end())
		return (NULL);
	return it->second;
}

IRC_User* IRC_Server::findUserByFd(int fd) {
	IRC_Server::usersFdIterator it = this->_usersByFd.find(fd);

	if (it == this->_usersByFd.end())
		return (NULL);
	return it->second;
}




                            //aqui es donde se envian cosas entre ellos
                            //sendMSG(this->_MOTD, NORMALMSG);
                       /*
                        for (int j = 0; j < this->_connectedClientsNum; j++)        // Send to everyone!
                        {
                            int destFd = this->_clients[j].fd;
                            if (destFd != this->_serverFd && destFd != senderFd)    // Except the listener and ourselves
                            {
                                if (send(destFd, buf, nbytes, 0) == -1)
                                    ft_err_msg("can not send data to destiny", ERR_STILL_SAVED, 2);
                            }
                        }
                      }
                      */

void    IRC_Server::userPolloutByFd(int fd)
{
    this->_pfds[fd].events = POLLOUT;
}

/*int IRC_Server::findPollPosition(IRC_User* user)
{
    for (int i = 0; i < this->_connectedClientsNum; i++)
    {
		if (this->_pfds[i].fd == user->getFd())
			return (i);
    }
	return (-1);
}*/

void    *IRC_Server::getInAddr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in *)sa)->sin_addr);
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void    IRC_Server::addToPfds(int newfd)
{
	int pos = this->_connectedClientsNum;

    if (this->_connectedClientsNum == MAX_CLIENTS)
    {
    	::send(newfd, "Too many users connected", 25, 0);
    	::close(newfd);
    	return ;
    }
    this->_pfds[pos].fd = newfd;
    this->_pfds[pos].events = POLLIN; // Verificar lectura disponible
    ++this->_connectedClientsNum;
}

void    IRC_Server::delFromPfds(struct pollfd* pollPosition)
{
    // Copy the one from the end over this one
    struct pollfd* last = this->_pfds + this->_connectedClientsNum - 1;

	*pollPosition = *last;
	last->fd = -1;
	--this->_connectedClientsNum;
}

IRC_User* IRC_Server::createUser()
{
    struct pollfd* pollPosition = this->_pfds + this->_connectedClientsNum - 1;
	IRC_User* user = new IRC_User(pollPosition);

	this->_usersByFd[pollPosition->fd] = user;
	return (user);
}

void IRC_Server::deleteUser(IRC_User* user)
{
	this->_usersByFd.erase(user->getFd());
	if (user->getAccess() > 0) //registrado en adelante
		this->_usersByName.erase(user->getName());
	this->delFromPfds(user->getPollPosition());
    ::close(user->getFd());
    delete user;
}

void    IRC_Server::fillMOTDMsg(const char *filename)
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
        std::strncat(this->_MOTD, "porque somos los currelas,\ny esto nunca va a morir ...\n\n", sizeof(_MOTD) - std::strlen(_MOTD) - 1);
    }
    else
        std::strncat(this->_MOTD, "Bienvenido al IRC de irodrigo e icastell\n\n", sizeof(_MOTD) - std::strlen(_MOTD) - 1);
        //return (false);
    //return (true);
}

int IRC_Server::sendMOTDMsg(int newClient)  //esto hay que leerlo de línea en línea e ir imprimiéndolo
{
    int totalSend = 0;

    totalSend = send(newClient, this->_MOTD, sizeof(this->_MOTD), 0);
    if (totalSend == -1)
        return (ft_err_msg("Envío MOTD Fallido", ERR_CURA_SANA, totalSend));
    return (totalSend);
}

IRC_Server::State 	IRC_Server::getState() const
{
	return (ALIVE);
}

bool IRC_Server::changeNameUser(IRC_User* user, const std::string& nickname)
{
	if (this->findUserByName(nickname))
		return (false);
	//TODO: hay que actualizar la clave del mapa
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
	return (true);
}

void IRC_Server::_fillCommands() {
    this->_addCommand(new IRC_DieCommand);
    this->_addCommand(new IRC_JoinCommand);
    this->_addCommand(new IRC_KickCommand);
    this->_addCommand(new IRC_KillCommand);
    this->_addCommand(new IRC_ListCommand);
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
}

void IRC_Server::_addCommand(IRC_ACommand* command)
{
	this->_commandsByName[command->cmd] = command;
}

void IRC_Server::_runCommand(IRC_Message& message)
{
	IRC_Server::commandTypeIterator it = this->_commandsByName.find(toUpper(message.getCmd()));
	IRC_ACommand* command = it->second;

	if (it == this->_commandsByName.end())
    {
		std::cout << "comando '" << message.getCmd() << "' no existe\n";
		//error comando no existe
		return ;
	}

	if (message.getSourceUser().getAccess() < command->access)
    {
		std::cout << "privilegios insuficientes\n";
        //error privillegios insuficientes
		return ;
	}
	if (message.getParamSize() <= command->params)
    {
        std::cout << "parámetros insuficientes\n";
		//error // parametros insuficientes
		return ;
	}
	command->execute(message);
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
