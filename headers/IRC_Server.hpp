/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:07:19 by icastell          #+#    #+#             */
/*   Updated: 2023/10/25 20:04:32 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

# include "IRC_Headers.hpp"
# include "IRC_Structs.hpp"
# include "IRC_Constants.hpp"
# include "IRC_Channel.hpp"
# include "IRC_Users.hpp"

class IRC_Client;

class IRC_Channel;

class IRC_Messages;

class IRC_Server
{
	private:
		// common configuration variables.
		std::string	_port;
		std::string	_password;
		std::string _serverName;
		char		_MOTD[4096];
		int			_serverFd;
		int			_connectedClientsNum;
		std::tm 	_myTimeStamp;
		struct addrinfo			_hints;
		struct addrinfo			*_res;
		struct pollfd			*_clients;
		struct sockaddr_storage _remoteaddr; // client address
    	socklen_t				_addrlen;
		char					_remoteIP[INET6_ADDRSTRLEN];

		IRC_Server();									// cannot be instantiated without a port and password
		IRC_Server(IRC_Server const &cpy);				// cannot be instantiated by copy
		IRC_Server &operator = (IRC_Server const &cpy);	// cannot be copied
		
		int	_myAddrInfo(std::string const &port);
		
		// User		_UserMap;
		// Command		_CommandMap;
		// IRC_Channel	_ChannelMap;
	public:
		// server status notifications.
		enum State
		{
			ALIVE,
			RESTART,
			DIE
		};
		enum MyType
		{
			PING,
			PONG
		};

		IRC_Server(char *port, const std::string &password);
		~IRC_Server();
		
		// getters and setters
		int					getServerFd() const;
		std::string			getPort() const;			
		std::string			getMOTD() const;
		IRC_Server::State 	getState() const;
		void				setServerFd(int serverSocket);
		void				setClients(struct pollfd *clients);
		//void 				setState(enum State myst);
		
		// general irc functions
		bool				initializeSocket();
		struct pollfd		*createPoll(int serverFd);
		void				launch();
		void *				getInAddr(struct sockaddr *sa);
		void 				addToPfds(pollfd *pfds[], int newfd, int *fd_count, int *fd_size);
		void 				delFromPfds(pollfd pfds[], int i, int *fd_count);

		// Server Display
		// void                sendMSG(std::string message, int type);

		bool				fillMOTDMsg(const char *filename);
		int                 sendMOTDMsg(int newClient);
		void				handleMessage(int fd);
		void				displayClient();

		// Server Display
		void				newClient();
		void				eraseClient(int fd);
		void				eraseClientChannel(IRC_Client &client);
		void				clientDisconnect(int fd);

		bool				is_in_channel(IRC_Client &client);
		bool				is_oper_in_channel(IRC_Client &client);

		// Server command implementation
			// IRC Commands
		void				cmdPass(IRC_Messages &message);
		void				cmdNick(IRC_Messages &message);
		void				cmdUser(IRC_Messages &message);
		void				cmdPrivMsg(IRC_Messages &message);
		void				cmdPingPong(IRC_Messages &message, MyType tp);
		void				cmdJoin(IRC_Messages &message);
		void				cmdOper(IRC_Messages &message);
		void				cmdQuit(IRC_Messages &message);
		void				cmdList(IRC_Messages &message);
		void				cmdNames(IRC_Messages &message);
		void				cmdPart(IRC_Messages &message);
		void				cmdKick(IRC_Messages &message);
		void				cmdKill(IRC_Messages &message);
		void				cmdDie(IRC_Messages &message);
		// probably not necesary
		void				cmdTopic(IRC_Messages &message);
		void				cmdNotice (IRC_Messages &message);
		void				cmdMode (IRC_Messages &message);
};
		


		// two functions in one threatment
		//void			cmdPing(Message &message);
		//void			cmd_pong(Message &message);
		// lo mismo no hace falta.
		//void			cmd_names_inChannel(Message &message, std::string channelName);



#endif
