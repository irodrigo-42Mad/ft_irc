/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:59:21 by irodrigo          #+#    #+#             */
/*   Updated: 2023/10/15 20:18:59 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/IRC_Server.hpp"

// common constructor and destructor of class Server
IRC_Server::IRC_Server(char *port, const std::string &password):
    _port(port), _serverName("ircserv")//, _MOTD("Aúpa Osasuna\n\n")
{
    //debemos asignar el puerto y el pass para poder funcionar con el resto de elementos.
	this->_serverFd = this->_myAddrinfo(this->_port);
	if (this->_serverFd <= 0)
	{
		std::cout << "estamos jodidos" << std::endl;
		return ;
	}
	std::time_t now = std::time(nullptr);
    std::tm     *localTime = std::localtime(&now);
    if (!fillMOTDMsg("./images/ascii-art.txt"))
    {
        std::cout << "fallo con la carga de MOTD" << std::endl;
        return ;
    }
    else
        std::cout << "ha ido todo bien en la carga" << std::endl;
        std::cout << this->_MOTD << std::endl;
        
	
    // solo de momento
    std::cout << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec
              << std::endl;
    
	// crear los pollFDs para los clientes conectados. 
	this->_clients = this->_createPoll(this->_serverFd);
	std::cout << "hola, este es el FD del servidor: " << this->_serverFd << std::endl;
	this->_password = password;
    //aquí llamamos a rellenador de MOTD
}

IRC_Server::~IRC_Server()
{}

// private funtions used to initialization

int IRC_Server::_myAddrinfo(char *serverPort)
{
	int rv;									// Control error output messages
	int listener;							// Listening socket descriptor
	int yes = 1;							// For setsockopt() SO_REUSEADDR, below
	struct addrinfo *p;						// auxiliar variable for check listener lists
	
	std::memset(&_hints, 0, sizeof this->_hints);
    this->_hints.ai_flags = AI_PASSIVE;       		// Fill in my IP for me
    this->_hints.ai_family = AF_UNSPEC;       		// Don't care IPv4 or IPv6
    this->_hints.ai_socktype = SOCK_STREAM;   		// TCP stream sockets
	
	if ((rv = getaddrinfo(NULL, serverPort, &this->_hints, &this->_res)) != 0)
    {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        return(-1);	//exit no está permitida. Hay que cambiar esto.
    }
	for (p = this->_res; p != NULL; p = p->ai_next)
    {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0)
            continue;
    
        // Lose the pesky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(listener);
            continue;
        }
        break;
    }

    // If we got here, it means we didn't get bound
    if (p == NULL)
    	return (-1);
    freeaddrinfo(this->_res); // All done with this
    if (listen(listener, 10) == -1)
        return (-1);
    return (listener);
}

struct pollfd * IRC_Server::_createPoll(int serverListener)
{
	struct pollfd *pfds = new pollfd[MAX_CLIENTS];
	
	// Add the server listener to set
    pfds[0].fd = serverListener;
    pfds[0].events = POLLIN; // Ready to read on incoming connection

    this->_connectedClientsNum = 1; // For the listener
	return (pfds);
}

// Public functions in server
void IRC_Server::launch()
{
	int     newFd;
	int     fdMaxSize = MAX_CLIENTS;
	char    buf[256];
	
	// Main loop
    while (42)
    {
        int poll_count = poll(this->_clients, this->_connectedClientsNum, -1);
        if (poll_count == -1)
        {
            perror("poll");
            exit(1);
        }

        // Run through the existing connections looking for data to read
        for (int i = 0; i < this->_connectedClientsNum; i++)
        {
            // Check if someone's ready to read
            if (this->_clients[i].revents & POLLIN) // We got one!!
            {
                if (this->_clients[i].fd == this->_serverFd)
                {
                    // If listener is ready to read, handle new connection

                    this->_addrlen = sizeof this->_remoteaddr;
                    newFd = accept(this->_serverFd, (struct sockaddr *)&this->_remoteaddr, &this->_addrlen);
                    if (newFd == -1)
                        perror("accept");
                    else
                    {
                        //std::cout << "antes: " << this->_connectedClientsNum << std::endl;
                        addToPfds(&this->_clients, newFd, &this->_connectedClientsNum, &fdMaxSize);
                        //std::cout << "después: " << this->_connectedClientsNum << std::endl;
                        std::cout << "pollserver: New connection from " << inet_ntop(this->_remoteaddr.ss_family,
                            getInAddr((struct sockaddr *)&this->_remoteaddr),
                            this->_remoteIP, INET6_ADDRSTRLEN) << " on socket " << newFd << std::endl;
                        //sendMSG(this->_MOTD, FIRST);

                        
                        
                        
                        //// __________ ///////
                        // int senderFd = this->_clients[0].fd;
                        
                        // int nbytes = recv(senderFd, this->_MOTD, sizeof (this->_MOTD), 0);
                        // for (int j = 1; j < this->_connectedClientsNum; j++)
                        // {
                            // Send to everyone!
                            //int destFd = this->_clients[j].fd;

                            // Except the listener and ourselves
                            if (sendMOTDMsg(newFd) < 0)
                                return ;
                            
                            // if (send(newFd, this->_MOTD, sizeof(this->_MOTD), 0) == -1)
                            //     perror("send");
                     //   }



                        //// __________ //////

                        
















                        
                    }
                }
                else
                {
                    //int nbytes = recv(this->_clients[i].fd, buf, sizeof buf, 0);
                    
                    // If not the listener, we're just a regular client
                    int senderFd = this->_clients[i].fd;
                    int nbytes = recv(senderFd, buf, sizeof buf, 0);
                    if (nbytes <= 0)
                    {
                        // Got error or connection closed by client
                        if (nbytes == 0)
                            // Connection closed
                            std::cout << "pollserver: Socket " << senderFd << " hung up" << std::endl;
                        else
                            perror("recv");
                        //close(this->_clients[i].fd); // Bye!
                        close(senderFd);
                        delFromPfds(this->_clients, i, &this->_connectedClientsNum);
                    }
                    else
                    {
                            //aqui es donde se envian cosas entre ellos
                            //sendMSG(this->_MOTD, NORMALMSG);
                        

                        
                        // We got some good data from a client
                        for (int j = 0; j < this->_connectedClientsNum; j++)
                        {
                            // Send to everyone!
                            int destFd = this->_clients[j].fd;

                            // Except the listener and ourselves
                            if (destFd != this->_serverFd && destFd != senderFd)
                            {
                                if (send(destFd, buf, nbytes, 0) == -1)
                                    perror("send");
                            }
                        }
                    }
                } // END handle data from client
            }     // END got ready-to-read from poll()
        }         // END looping through file descriptors
    }             // END for(;;)--and you thought it would never end!
}

void    *IRC_Server::getInAddr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in *)sa)->sin_addr);
		
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void    IRC_Server::addToPfds(pollfd *pfds[], int newfd, int *fd_count, int *fd_size)
{
    if (*fd_count == *fd_size)
    {
        *fd_size *= 2;
        pollfd* new_pfds = new pollfd[*fd_size];
        for (int i = 0; i < *fd_count; i++) {
            new_pfds[i] = (*pfds)[i];
        }
        delete[] *pfds;     // Libera la memoria del array original
        *pfds = new_pfds;   // Asigna el nuevo array a pfds
    }

        (*pfds)[*fd_count].fd = newfd;
        (*pfds)[*fd_count].events = POLLIN; // Verificar lectura disponible
        (*fd_count)++;
}

void    IRC_Server::delFromPfds(pollfd pfds[], int i, int *fd_count)
{
    // Copy the one from the end over this one
    pfds[i] = pfds[*fd_count - 1];
    (*fd_count)--;
}

IRC_Server::State 	IRC_Server::getState() const
{
	return (ALIVE);
}

std::string IRC_Server::getMOTD() const
{
    return (this->_MOTD);
}


int IRC_Server::sendMOTDMsg(int newClient)
{
    int totalSend = 0;

    totalSend = send(newClient, this->_MOTD, sizeof(this->_MOTD), 0);
    if (totalSend == -1)
        return (ft_err_msg("Envio MOTD Fallido", ERR_CURA_SANA, totalSend));
    return (totalSend);
}

bool    IRC_Server::fillMOTDMsg(const char *filename)
{
    //std::ifstream file(filename);
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if (file.is_open())
    {
        //file.getline(this->_MOTD, 16383); //leer el contenido del archivo hasta una máximo de 255 caracteres
        file.read(this->_MOTD, sizeof(this->_MOTD));
        this->_MOTD[file.gcount()] = '\0';
        file.close();
    }
    else
        return (false);
    return (true);
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
