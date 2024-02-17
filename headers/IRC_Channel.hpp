/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Channel.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:04:15 by irodrigo          #+#    #+#             */
/*   Updated: 2024/02/17 15:47:36 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_CHANNEL_HPP
# define IRC_CHANNEL_HPP

# include <ctime>
# include <string>
# include <vector>
# include <set>

struct IRC_Server;
struct IRC_User;

struct IRC_Channel
{
	typedef std::set<std::string>			bansType;
	typedef bansType::iterator				bansIterator;
	typedef bansType::const_iterator		bansConstIterator;

	typedef std::set<IRC_User*>				usersType;
	typedef usersType::iterator			  	usersIterator;
	typedef usersType::const_iterator		usersConstIterator;


	IRC_Channel(const std::string& name, IRC_User& user);
	~IRC_Channel();

  	const std::string&	getName() const;
  	const std::string&	getTopic() const;
	const std::string& 	getTopicUser() const;
	time_t				getTopicTime() const;
  	const usersType&	getUsers() const;
  	int 				getNumUsers() const;
	
	time_t 				getCreationTime() const;

  	void				setTopic(const IRC_User& user, const std::string& newTopic);
	
  	bool				addUser(IRC_User& user);
  	bool				hasUser(const IRC_User& user);
  	void				removeUser(IRC_User& user);

  	bool	 			addOperator(IRC_User& user);
  	bool 				isOperator(const IRC_User& user);
  	bool 				removeOperator(IRC_User& user);

  	bool 				addVoice(IRC_User& user);
  	bool 				isVoice(const IRC_User& user);
  	bool 				removeVoice(IRC_User& user);

  	bool 				setInvite();
  	bool 				hasInvite();
  	bool 				unsetInvite();

  	bool	 			setKey(const std::string& value);
  	bool 				hasKey();
  	bool 				unsetKey(const std::string& value);
  	bool 				isSameKey(const std::string& value);

  	bool	 			setNoExternalMessages();
	bool 				hasNoExternalMessages();
  	bool 				unsetNoExternalMessages();

	bool	 			addBan(const std::string& mask);
	bool 				isBanned(const IRC_User& user);
	bool 				removeBan(const std::string& mask);

	bool	 			setTopicProtection();
	bool 				hasTopicProtection();
	bool 				unsetTopicProtection();

	bool	 			setLimit(size_t value);
	bool 				hasLimit();
	bool 				unsetLimit();
	bool 				isFull();

	bool	 			setModerate();
	bool 				hasModerate();
	bool 				unsetModerate();

	bool	 			setSecret();
	bool 				hasSecret();
	bool 				unsetSecret();

	bool	 			setPrivate();
	bool 				hasPrivate();
	bool 				unsetPrivate();

	std::string			getModes() const;
	std::string			setModes(IRC_User& user, IRC_Server& server, const std::vector<std::string>& modes);

  	bool 				empty() const;
	
  	void 				sendExcept(const IRC_User* exceptUser, const std::string& data);
  	void 				send(const std::string&);
  	void 				send(const IRC_User& user, const std::string& data);
  	void 				send(const IRC_Server& server, const std::string& data);
  	void 				sendExcept(const IRC_User* exceptUser, const IRC_User& user, const std::string& data);
  	void 				sendExcept(const IRC_User* exceptUser, const IRC_Server& server, const std::string& data);
  	void 				send(const IRC_User& user, const std::string& data, const std::string& lastParameter);
  	void 				send(const IRC_Server& server, const std::string& data, const std::string& lastParameter);
  	void	 			sendExcept(const IRC_User* exceptUser, const IRC_User& user, const std::string& data, const std::string& lastParameter);
  	void 				sendExcept(const IRC_User* exceptUser, const IRC_Server& server, const std::string& data, const std::string& lastParameter);

private:
	usersType			_users;
	usersType			_operUsers;
	usersType			_voiceUsers;
	bansType			_bans;

	time_t				_creationTime;
	std::string			_channelName;
	std::string			_topic;
	std::string			_topicUser;
	time_t 				_topicTime;
	std::string			_key;
	size_t				_limit;
	bool				_private;
	bool				_secret;
	bool				_moderate;
	bool				_noExternalMessages;
	bool				_invite;
	bool				_topicProtection;
};

#endif
