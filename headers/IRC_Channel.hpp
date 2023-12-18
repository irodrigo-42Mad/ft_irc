/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Channel.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:04:15 by irodrigo          #+#    #+#             */
/*   Updated: 2023/12/18 13:41:15 by icastell         ###   ########.fr       */
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
	typedef std::set<IRC_User*>						usersSetType;
	typedef usersSetType::iterator				usersSetIterator;
	typedef usersSetType::const_iterator	usersSetConstIterator;

	IRC_Channel(IRC_Server&, IRC_User*, const std::string&);
	~IRC_Channel();

  const std::string& getName() const;
  const std::string& getTopic() const;
  const IRC_User* getCreator() const;
  const usersSetType *getUsers() const;
  int getNumUsers() const;

  void setTopic(const std::string&);

  bool addUser(IRC_User*);
  bool hasUser(IRC_User*);
  void removeUser(IRC_User*);

  void sendExcept(const std::string&, IRC_User*);
  void send(const std::string&);

private:
	IRC_Server&			_server;
	std::string			_channelName;
	IRC_User*			_creator;
	std::string			_topic;
	std::string			_key;
	int					_limit;
	usersSetType		_usersSet;
};

#endif
