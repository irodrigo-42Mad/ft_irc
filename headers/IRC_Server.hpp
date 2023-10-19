/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:07:19 by icastell          #+#    #+#             */
/*   Updated: 2023/10/15 20:12:25 by icastell         ###   ########.fr       */
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
		char 		*_port;
		std::string	_password;
		std::string _serverName;
		int			_serverFd;
		int			_connectedClientsNum;
		char		_MOTD[4096];
		std::tm 	_myTimeStamp;
		//struct datetime _myTimeStamp;
		//int			_clientsConnect;
		
		struct pollfd			*_clients;
		struct sockaddr_storage _remoteaddr; // Client address
    	socklen_t				_addrlen;
		char					_remoteIP[INET6_ADDRSTRLEN];

		// complient class methods not used.
		IRC_Server();

		int				_myAddrinfo(char *serverPort);
		struct pollfd * _createPoll(int serverFd);
		
		
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

		struct addrinfo _hints, *_res;

		IRC_Server(char *port, const std::string &password);
		IRC_Server(IRC_Server const &cpy);
		IRC_Server &operator = (IRC_Server const &cpy);
		~IRC_Server();
		
		//getters y setters
		//enum State 			getState();

		IRC_Server::State 	getState() const;
		std::string			getMOTD() const;
		//void 				setState(enum State myst);
		
		// general irc functions
		void				launch();
		void *				getInAddr(struct sockaddr *sa);
		void 				addToPfds(pollfd *pfds[], int newfd, int *fd_count, int *fd_size);
		void 				delFromPfds(pollfd pfds[], int i, int *fd_count);

		// Server Display
		// void                sendMSG(std::string message, int type);

		bool				fillMOTDMsg(const char *filename);
		int                 sendMOTDMsg(int newClient);
		void				handleMessage(int fd); // de momento no usada
		void				displayClient();

		// Server Display
		void				newClient();
		void				eraseClient(int fd);
		void				eraseClientChannel(IRC_Client &cl);
		void				clientDisconnect(int fd);

		bool				is_in_channel(IRC_Client &cl);
		bool				is_oper_in_channel(IRC_Client &cl);

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
