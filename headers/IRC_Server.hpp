/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:07:19 by icastell          #+#    #+#             */
/*   Updated: 2023/12/13 12:31:39 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

# include "IRC_Headers.hpp"
# include "IRC_Structs.hpp"
# include "IRC_Constants.hpp"
# include "IRC_User.hpp"
# include "IRC_Channel.hpp"
# include "commands.hpp"

# include <map>

struct IRC_Client;
struct IRC_Channel;
struct IRC_Message;
struct IRC_User;

struct IRC_Server
{
		typedef std::map<std::string, IRC_User*>	usersNameType;			//map<nick, user*>
		typedef usersNameType::iterator				usersNameIterator;
		typedef usersNameType::const_iterator		usersNameConstIterator;

		typedef std::map<int, IRC_User*>			usersFdType;			//map<fd, user*>
		typedef usersFdType::iterator				usersFdIterator;
		typedef usersFdType::const_iterator			usersFdConstIterator;

		typedef std::map<std::string, IRC_Channel*>	channelsNameType;		//map<channelName, channel*>
		typedef channelsNameType::iterator			channelsNameIterator;
		typedef channelsNameType::const_iterator	channelsNameConstIterator;

		typedef std::map<std::string, IRC_ACommand*>	commandType;
		typedef commandType::iterator							commandTypeIterator;
		typedef commandType::const_iterator						commandTypeConstIterator;

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
		//const std::string&	getServerName() const;
		//int					getServerFd() const;
		
		IRC_Server::State 	getState() const;
		//void				setServerFd(int serverSocket);
		//void				setClients(struct pollfd* clients); // revisar esta funcion
		//void 				setState(enum State myst);
		//std::string		getMOTD() const;
		//int				getConnectedClientsNum() const;

		// general irc functions
		void			createPoll();
		//struct pollfd*			createPoll();
		void								start();
		bool								listen(int backlog);
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

		IRC_Channel*	createChannel(const std::string& name, IRC_User* user);
		void			deleteChannel(IRC_Channel* channel);
		IRC_Channel*	findChannelByName(const std::string& name);

		IRC_User*		createUser();
		void			deleteUser(IRC_User* user);
		IRC_User*		findUserByName(const std::string& name);
		IRC_User*		findUserByFd(int fd);

		bool changeNameUser(IRC_User* user, const std::string& name);
		bool addUserToChannel(IRC_User* user, IRC_Channel* channel);
		bool removeUserFromChannel(IRC_User* user, IRC_Channel* channel);

	private:
		int					_serverFd;
		std::string			_port;
		std::string			_password;
		std::string			_serverName;
		std::string			_host;
		usersNameType		_usersByName;
		usersFdType			_usersByFd;
		channelsNameType	_channelsByName;
		commandType			_commandsByName;
		
		struct pollfd		_pfds[MAX_CLIENTS];
		
		char				_MOTD[4096];
		int					_connectedClientsNum;
		
		std::tm			_myTimeStamp;
		//struct addrinfo		_hints;
		//struct addrinfo*	_res;
		//struct sockaddr_storage _remoteaddr; // client address
		//socklen_t				_addrlen;
		//char					_remoteIP[INET_ADDRSTRLEN];


		IRC_Server();										// can not be instantiated without a port and password
		IRC_Server(const IRC_Server& copy);					// can not be instantiated by copy
		IRC_Server &operator = (const IRC_Server& copy);	// can not be instantiated using = operator

		bool	createServerSocket();
		void	_fillCommands(void);
		void  _addCommand(IRC_ACommand* command);
		void  _run_command(IRC_Message& message);
		//int	_myAddrInfo(const std::string& port);
		void _readFromUser(int fd);
		void _processUserCommand(IRC_User* user);
		IRC_ACommand* _parseCommand(std::string buffer);

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
