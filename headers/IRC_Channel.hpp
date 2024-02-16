/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Channel.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:04:15 by irodrigo          #+#    #+#             */
/*   Updated: 2024/02/16 14:20:39 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_CHANNEL_HPP
# define IRC_CHANNEL_HPP

# include <string>
# include <set>

struct IRC_Server;
struct IRC_User;

struct IRC_Channel
{
	typedef std::set<IRC_User*>			usersType;
	typedef usersType::iterator			usersIterator;
	typedef usersType::const_iterator	usersConstIterator;

	IRC_Channel(const std::string& name, IRC_User& user);
	~IRC_Channel();

  	const std::string&	getName() const;
  	const std::string&	getTopic() const;
  	const IRC_User&		getCreator() const;
  	const usersType&	getUsers() const;
  	int 				getNumUsers() const;
	
  	void 				setTopic(const std::string& newTopic);
	
  	bool 				addUser(IRC_User& user);
  	bool 				hasUser(IRC_User& user);
  	void 				removeUser(IRC_User& user);

  	bool 				empty() const;
	
  	void 				sendExcept(const IRC_User* exceptUser, const std::string& data);
  	void 				send(const std::string&);
  	void 				send(const IRC_User& user, const std::string& data, const std::string& lastParameter = "");
  	void 				send(const IRC_Server& server, const std::string& data, const std::string& lastParameter = "");
  	void 				sendExcept(const IRC_User* exceptUser, const IRC_User& user, const std::string& data, const std::string& lastParameter = "");
  	void 				sendExcept(const IRC_User* exceptUser, const IRC_Server& server, const std::string& data, const std::string& lastParameter = "");

private:
	std::string			_channelName;
	IRC_User&			_creator;
	std::string			_topic;
	std::string			_key;
	int					_limit;
	usersType			_users;
};

#endif
