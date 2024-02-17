/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:07:19 by icastell          #+#    #+#             */
/*   Updated: 2024/02/17 18:37:10 by irodrigo         ###   ########.fr       */
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
# include "IRC_Response.hpp"
# include "commands.hpp"
# include "console.hpp"

# include <map>
# include <ctime>

struct IRC_Message;

struct IRC_Server : public Console::Console::IDisplayManager
{
		typedef std::map<std::string, IRC_User*>			usersNameType;			//map<nick, user*>
		typedef usersNameType::iterator						usersNameIterator;
		typedef usersNameType::const_iterator				usersNameConstIterator;

		typedef std::map<int, IRC_User*>					usersFdType;			//map<fd, user*>
		typedef usersFdType::iterator						usersFdIterator;
		typedef usersFdType::const_iterator					usersFdConstIterator;

		typedef std::map<std::string, IRC_Channel*>			channelsNameType;		//map<channelName, channel*>
		typedef channelsNameType::iterator					channelsNameIterator;
		typedef channelsNameType::const_iterator			channelsNameConstIterator;

		typedef std::multimap<std::string, IRC_Channel*>	invitedChannelsNameType;		//multimap<nickname, channel*>
		typedef invitedChannelsNameType::iterator			invitedChannelsNameIterator;
		typedef invitedChannelsNameType::const_iterator		invitedChannelsNameConstIterator;

		typedef std::map<std::string, IRC_ACommand*>		commandsNameType;
		typedef commandsNameType::iterator					commandsNameIterator;
		typedef commandsNameType::const_iterator			commandsNameConstIterator;

		typedef IRC_User::channelsType						channelsType;
		typedef IRC_User::channelsIterator					channelsIterator;
		typedef IRC_User::channelsConstIterator				channelsConstIterator;

		typedef IRC_Channel::usersType						usersType;
		typedef IRC_Channel::usersIterator					usersIterator;
		typedef IRC_Channel::usersConstIterator				usersConstIterator;

	public:

		// Server status notifications.
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
		const std::string&							getPort() const;
		const std::string&							getPassword() const;
		const std::string&							getServerName() const;
		const std::string							getMOTD() const;
		const std::map<std::string, IRC_Channel*> 	&getChannels() const;
		IRC_Server::State 							getState() const;
	
		// General irc functions
		void					start();
		bool					listen(int backlog);
		void*					getInAddr(struct sockaddr* sa);

		// Server Display
		void					fillMOTDMsg(const char* filename);
		void					sendMOTDMsg(IRC_User& user);
		void					sendWelcomeMsg(IRC_User& user);
		void					handleMessage(int fd);
		void					displayClient();

		// Server messages management
		void					send(const std::string& data);
		void					send(const IRC_Server& server, const std::string& data);
		void					send(const IRC_User& user, const std::string& data);

		// Command management
		IRC_ACommand*			findCommandByName(const std::string& name);

		// User and channel management
		IRC_Channel*			findChannelByName(const std::string& name);
		void					channelList(IRC_User& user);
		void					channelListByName(IRC_User& user, std::string name);
		
		IRC_Channel*			createChannel(const std::string& name, IRC_User& user);
		void					deleteChannel(IRC_Channel& channel);
		bool					changeChannelTopic(IRC_User& user, IRC_Channel& channel, const std::string &topic);
		IRC_Response 			addUserToChannel(IRC_User& user, IRC_Channel& channel);
		IRC_Response 			removeUserFromChannel(IRC_User& user, IRC_Channel& channel);
		void 					removeUserFromChannels(IRC_User& user);
	
		IRC_User*				findUserByName(const std::string& name);
		IRC_User*				findUserByFd(int fd);
		void					userPolloutByFd(int fd);
		bool 					setPendingUser(IRC_User& user);
		IRC_Response 			changeNameUser(IRC_User& user, const std::string& name);
		
		// Common IRC commands
		IRC_Response 			kickUser(IRC_User& user, IRC_Channel& channel, const std::string& message);
		IRC_Response 			joinUser(IRC_User& user, IRC_Channel& channel, const std::string& key);
		IRC_Response 			partUser(IRC_User& user, IRC_Channel& channel, const std::string& message);
		bool 					killUser(const IRC_User& User, IRC_User& targetUser, const std::string& message);
		bool 					quitUser(IRC_User& User, const std::string& message);
		void 					shutdown(const std::string& msg);
		void 					ping(IRC_User *sender, std::string const &ping);
		void 					pong(IRC_User *sender, std::string const &message);
		
		// Invited user management
		bool    				findInvitedUserToAChannel(const std::string& nickname, const std::string& channelName);
		void					insertInvitedUser(std::string& nickname, IRC_Channel& channel);
		void					deleteInvitedUser(const std::string& nickname, const std::string& channelName);
		
	private:
		int						_serverFd;
		std::string				_port;
		std::string				_password;
		std::string				_serverName;
		std::string				_host;
		usersNameType			_usersByName;
		usersFdType				_usersByFd;
		usersType				_opers;
		channelsNameType		_channelsByName;
		commandsNameType		_commandsByName;
		invitedChannelsNameType	_invitedByName;
		struct pollfd			_pfds[MAX_CLIENTS];
		char					_MOTD[4096];
		int						_connectedClientsNum;
		std::time_t				_startTime;
		bool					_die;
		static bool				_forceDie;
		
		IRC_Server();										// can not be instantiated without a port and password
		IRC_Server(const IRC_Server& copy);					// can not be instantiated by copy
		IRC_Server &operator = (const IRC_Server& copy);	// can not be instantiated using = operator

		void					_createPoll();
		struct pollfd*			_addToPfds(int newfd);
		void					_delFromPfds(struct pollfd* pollPosition);
		struct pollfd			_getPollfd();

		bool					_createServerSocket();
		void					_fillCommands(void);
		void 					_clearCommands();
		void					_addCommand(IRC_ACommand* command);
		void					_runCommand(IRC_Message& message);
		void					_readFromUser(IRC_User* user);
		void					_sendToUser(IRC_User* user);
		void					_processUserCommand(IRC_User* user);
		bool					_checkClientTime(IRC_User *user);
		void  					_handleDeletionAndDisconnect(IRC_User* user);

		IRC_User*				_createUser(int fd, struct sockaddr_storage* addrStorage);
		void					_deleteUser(IRC_User* user);

		void 					displayBottom(std::stringstream& ss, int width);

		void 					_setSignals();
		static void 			_sigintHandler(int);
};

#endif
