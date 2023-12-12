/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_User.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:05:44 by irodrigo          #+#    #+#             */
/*   Updated: 2023/12/12 11:37:41 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_USER_HPP
# define IRC_USER_HPP

# include "IRC_Channel.hpp"
# include "IRC_Message.hpp"

# include <set>
# include <vector>
# include <string>

struct IRC_Server;

struct IRC_User{
	typedef std::vector<IRC_Channel*>					channelsVectorType;
	typedef std::set<IRC_Channel*>						channelsSetType;
	typedef channelsSetType::iterator					channelsSetIterator;
	typedef channelsSetType::const_iterator		channelsSetConstIterator;

	IRC_User(struct pollfd* pollPosition);

	IRC_User(struct pollfd* pollPosition, const std::string& nick, const std::string& ident, const std::string& realname, IRC_Server&);
	~IRC_User();

	bool isInChannel(IRC_Channel*);
	bool addChannel(IRC_Channel*);
	bool removeChannel(IRC_Channel*);

	void addReceiveData(char* buffer);

	const channelsSetType getChannels() const;
	const IRC_Channel::usersSetType getCommonUsersArray() const;
	const IRC_User::channelsSetType getCommonUsers() const;


	int getFd() const;
	struct pollfd* getPollPosition();
	const std::string& getName() const;
	const std::string getBuffer() const;
	const std::string getMask() const;
	const std::string getUsers() const;  // habrá que crearlas

	void setFd(int);
	void setName(const std::string&);
	int getAccess() const;

	void send(IRC_Message& message);

private:
	struct pollfd*		_pollPosition;
	std::string				_name;
	std::string				_ident;
	std::string				_realname;
	std::string				_hostname;
	int								_access;
	IRC_Server*				_server;
	channelsSetType		_channels;
	std::string				_inputBuffer;

	IRC_User(const IRC_User&);
	IRC_User& operator=(const IRC_User&);
};

#endif
