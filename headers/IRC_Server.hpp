/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:07:19 by icastell          #+#    #+#             */
/*   Updated: 2023/12/05 07:56:33 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

# include "IRC_Headers.hpp"
# include "IRC_Structs.hpp"
# include "IRC_Constants.hpp"

# include <map>

struct IRC_Client;
struct IRC_Channel;
struct IRC_Messages;
struct IRC_User;

struct IRC_Server
{
		typedef std::map<std::string, IRC_User*>		usersNameType;
		typedef usersNameType::iterator						usersNameIterator;
		typedef usersNameType::const_iterator			usersNameConstIterator;

		typedef std::map<int, IRC_User*>						usersFdType;
		typedef usersFdType::iterator							usersFdIterator;
		typedef usersFdType::const_iterator				usersFdConstIterator;

		typedef std::map<std::string, IRC_Channel*>	channelsNameType;
		typedef channelsNameType::iterator				channelsNameIterator;
		typedef channelsNameType::const_iterator	channelsNameConstIterator;

		// common configuration variables.
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

		IRC_Server(char* port, const std::string& password);
		//IRC_Server(IRC_Server const &copy);
		//IRC_Server &operator = (IRC_Server const &copy);
		~IRC_Server();

		// getters and setters
		const std::string&	getPort() const;
		const std::string&	getPassword() const;
		const std::string&	getServerName() const;
		std::string					getMOTD() const;
		int									getServerFd() const;
		int									getConnectedClientsNum() const;
		IRC_Server::State 	getState() const;
		void								setServerFd(int serverSocket);
		void								setClients(struct pollfd* clients); // revisar esta funcion
		//void 				setState(enum State myst);

		// general irc functions
		bool								initializeSocket();
		struct pollfd*			createPoll(int serverFd);
		void								launch();
		void*								getInAddr(struct sockaddr* sa);
		void								addToPfds(int newfd);
		void								delFromPfds(struct pollfd* pollPosition);

		// Server Display
		// void                sendMSG(std::string message, int type);

		void				fillMOTDMsg(const char* filename);
		int                 sendMOTDMsg(int newClient);
		void				handleMessage(int fd);
		void				displayClient();

		// Server Display
		void				newClient();
		void				eraseClient(int fd);

		void				addClientToChannel(IRC_Client* client, IRC_Channel* channel);
		void				removeClientFromChannel(IRC_Client* client, IRC_Channel* channel);
		void				clientDisconnect(int fd);
		//estas dos funciones no deberían estar mejor en client??????
		bool				is_in_channel(IRC_Client& client);
		bool				is_oper_in_channel(IRC_Client& client);

		// Server command implementation

		//user and channel management

		IRC_Channel*	newChannel(const std::string& name, IRC_User* user);
		void					deleteChannel(IRC_Channel* channel);
		IRC_Channel*	findChannelByName(const std::string& name);

		IRC_User*			newUser(struct pollfd* pollPosition);
		void					deleteUser(IRC_User* user);

		IRC_User*			findUserByName(const std::string& name);
		IRC_User*			findUserByFd(int fd);

		bool changeNameUser(IRC_User* user, const std::string& name);
		void addUsertoChannel(IRC_User* user, IRC_Channel* channel);
		void removeUserFromChannel(IRC_User* user, IRC_Channel* channel);

	private:
		std::string				_port;
		std::string				_password;
		std::string				_serverName;
		char							_MOTD[4096];
		int								_serverFd;
		int								_connectedClientsNum;
		std::tm						_myTimeStamp;
		struct addrinfo		_hints;
		struct addrinfo*	_res;
		struct pollfd			_clients[MAX_CLIENTS];
		struct sockaddr_storage _remoteaddr; // client address
		socklen_t					_addrlen;
		char							_remoteIP[INET_ADDRSTRLEN];

		usersNameType		_usersByName;
		usersFdType			_usersByFd;
		channelsNameType _channelsByName;

		IRC_Server();										// can not be instantiated without a port and password
		IRC_Server(const IRC_Server& copy);					// can not be instantiated by copy
		IRC_Server &operator = (const IRC_Server& copy);	// can not be instantiated using = operator

		int	_myAddrInfo(const std::string& port);
		void _readFromUser(int fd);
		void _processUserCommand(IRC_User* user);

		// User		_UserMap;
		// Command		_CommandMap;
		// IRC_Channel	_ChannelMap;

};



		// two functions in one threatment
		//void			cmdPing(Message &message);
		//void			cmd_pong(Message &message);
		// lo mismo no hace falta.
		//void			cmd_names_inChannel(Message &message, std::string channelName);



#endif
