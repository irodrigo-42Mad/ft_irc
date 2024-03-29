/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_User.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:05:44 by irodrigo          #+#    #+#             */
/*   Updated: 2024/02/18 14:50:23 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_USER_HPP
# define IRC_USER_HPP

# include "IRC_Channel.hpp"
# include "IRC_Message.hpp"

# include <set>
# include <vector>
# include <string>
# include <ctime>

struct IRC_Server;

struct IRC_User
{
	typedef std::vector<IRC_Channel*>					channelsVectorType;

	typedef std::set<IRC_Channel*>						channelsType;
	typedef channelsType::iterator						channelsIterator;
	typedef channelsType::const_iterator			channelsConstIterator;

	typedef IRC_Channel::usersType						usersType;
	typedef IRC_Channel::usersIterator				usersIterator;
	typedef IRC_Channel::usersConstIterator		usersConstIterator;

	IRC_User(struct pollfd* pollPosition);
	IRC_User(struct pollfd* pollPosition, const std::string& nick, const std::string& ident, const std::string& realname);
	~IRC_User();

	bool isInChannel(IRC_Channel& channel);
	bool addChannel(IRC_Channel& channel);
	bool removeChannel(IRC_Channel& channel);

	void addReceiveData(char* buffer);

	const channelsType		getChannels() const;
	usersType*	getCommonUsersExcept(const IRC_User& exceptUser);
	usersType*	getCommonUsers();

	int getFd() const;
	int	getAccess() const;
	struct pollfd*		getPollPosition();
	void 				setPollPosition(struct pollfd* value);
	const std::string&	getName() const;
	const std::string	getMask() const;
	const std::string&  getHost() const;
	//const std::string	getUsers() const;  // habrá que crearlas
	const std::string&	getIdent() const;
	const std::string&	getRealName() const;
	const std::string&	getPass() const;
	time_t				getPingTimeout();
	time_t				getIdleTime();
	time_t 				getLoginTime();
	const std::string&	getPingText() const;


	void setFd(int);
	void setName(const std::string& value);
	void setUserTimeout(time_t myTimeOut);
	void setIdent(const std::string& value);
	void setRealName(const std::string& value);
	void setHost(const std::string& value);
	void setAccess(int access);
	void setPass(const std::string& value);
	void setPingTimeout(time_t value);
	void setIdleTime(time_t value);

	void send(const std::string& data);
	void send(const IRC_Server& server, const std::string& data);
	void send(const IRC_User& user, const std::string& data);
	void send(const IRC_Server& server, const std::string& data, const std::string& lastParam);
	void send(const IRC_User& user, const std::string& data, const std::string& lastParam);
	void sendCommonUsers(const std::string& data);
	void sendCommonUsersExceptMe(const IRC_User& user, const std::string& data);
	void sendCommonUsersExceptMe(const IRC_User& user, const std::string& data, const std::string& lastParam);
	//void reply(const IRC_User& user, const std::string& data);
	void 	reply(const IRC_Server& server, const std::string& data);
	void	sendLimitedMessage(const std::string& data);

	void resetIdle(void);
	void disablePingTimeout(void);
	void markForDelete();
	bool deleteMarked() const;
//	void	errorReply(const std::string& reply);
	//void	send(IRC_Message& message);

private:
	struct pollfd*		_pollPosition;
	std::string			_name;
	std::string			_ident;
	std::string			_realname;
	std::string			_hostname;
	std::string			_pass;
	int					_access;
	channelsType		_channels;
	std::string			_inputBuffer;
	std::string			_outputBuffer;
	time_t				_pingTimeout;					// calculate timeout
	time_t				_idleTime;						// check last command time
	time_t				_loginTime;				// moment that user has registered in server
	bool				_deleteMarked;
	std::string			_pingText;
	
	IRC_User(const IRC_User& copy);
	IRC_User& operator=(const IRC_User& rhs);

	time_t 	_getTime(void);
	time_t	_getRegTime(void);

	friend struct IRC_Server;
};

#endif
