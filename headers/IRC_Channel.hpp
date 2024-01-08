/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Channel.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:04:15 by irodrigo          #+#    #+#             */
/*   Updated: 2024/01/08 17:14:47 by icastell         ###   ########.fr       */
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
	typedef std::set<IRC_User*>				usersSetType;
	typedef usersSetType::iterator			usersSetIterator;
	typedef usersSetType::const_iterator	usersSetConstIterator;

	IRC_Channel(IRC_User*, const std::string&);
	~IRC_Channel();

  	const std::string&	getName() const;
  	const std::string&	getTopic() const;
  	const IRC_User*		getCreator() const;
  	const usersSetType*	getUsers() const;
  	int getNumUsers() const;
	
  	void setTopic(const std::string& newTopic);
	
  	bool addUser(IRC_User* user);
  	bool hasUser(IRC_User* user);
  	void removeUser(IRC_User* user);

  	bool empty() const;
	
  	void sendExcept(IRC_User* user, const std::string& data);
  	void send(const std::string&);
  	void send(const IRC_User& user, const std::string& data);
  	void send(const IRC_Server& server, const std::string& data);

private:
	std::string			_channelName;
	IRC_User*			_creator;
	std::string			_topic;
	std::string			_key;
	int					_limit;
	usersSetType		_usersSet;
};

#endif
