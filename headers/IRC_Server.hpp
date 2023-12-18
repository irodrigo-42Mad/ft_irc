/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:07:19 by icastell          #+#    #+#             */
/*   Updated: 2023/12/18 20:35:48 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

# define SOCKET_BUFFER   8192

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
		typedef commandType::iterator					commandTypeIterator;
		typedef commandType::const_iterator				commandTypeConstIterator;

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
		~IRC_Server();

		// getters and setters
		const std::string&	getPort() const;
		const std::string&	getPassword() const;
		const std::string&	getServerName() const;
		struct pollfd		getPollfd();
		//int					getServerFd() const;
		
		IRC_Server::State 	getState() const;
		//void				setServerFd(int serverSocket);
		//void				setClients(struct pollfd* clients); // revisar esta funcion
		//void 				setState(enum State myst);
		std::string			getMOTD() const;
		//int				getConnectedClientsNum() const;

		// General irc functions
		void	createPoll();
		void	start();
		bool	listen(int backlog);
		void*	getInAddr(struct sockaddr* sa);
		void	addToPfds(int newfd);
		void	delFromPfds(struct pollfd* pollPosition);

		// Server Display
		void	fillMOTDMsg(const char* filename);
		void	sendMOTDMsg(IRC_User* user);
		void	handleMessage(int fd);
		void	displayClient();

		// Server Display
		void	newClient();
		void	eraseClient(int fd);

		void	addClientToChannel(IRC_Client* client, IRC_Channel* channel);
		void	removeClientFromChannel(IRC_Client* client, IRC_Channel* channel);
		void	clientDisconnect(int fd);
		//estas dos funciones no deberían estar mejor en client??????
		bool	is_in_channel(IRC_Client& client);
		bool	is_oper_in_channel(IRC_Client& client);

		// Server command implementation

		//user and channel management

		IRC_Channel*	createChannel(const std::string& name, IRC_User* user);
		void			deleteChannel(IRC_Channel* channel);
		IRC_Channel*	findChannelByName(const std::string& name);
		void			channelList(IRC_User* user);
		void			channelListByName(IRC_User* user, std::string name);
		void			changeChannelTopic(IRC_User* user, std::string &name, std::string &topic);

		IRC_User*		createUser();
		void			deleteUser(IRC_User* user);
		void			userQuit(IRC_User* User, const std::string& message);
		
		IRC_User*		findUserByName(const std::string& name);
		IRC_User*		findUserByFd(int fd);
		void			userPolloutByFd(int fd);
		//int				findPollPosition(IRC_User* user);

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
		
		std::tm				_myTimeStamp;
		
		IRC_Server();										// can not be instantiated without a port and password
		IRC_Server(const IRC_Server& copy);					// can not be instantiated by copy
		IRC_Server &operator = (const IRC_Server& copy);	// can not be instantiated using = operator

		bool			_createServerSocket();
		void			_fillCommands(void);
		void  			_addCommand(IRC_ACommand* command);
		void  			_runCommand(IRC_Message& message);
		void			_readFromUser(int fd);
		void 			_sendToUser(int fd);
		void			_processUserCommand(IRC_User* user);
		//IRC_ACommand*	_parseCommand(std::string buffer);
		bool			_checkClientTime(IRC_User *user);

		// User		_UserMap;
		// Command		_CommandMap;
		// IRC_Channel	_ChannelMap;

};

#endif
