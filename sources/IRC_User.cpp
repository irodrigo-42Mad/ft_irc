/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_User.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:15:01 by irodrigo          #+#    #+#             */
/*   Updated: 2024/02/18 21:25:51 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC_User.hpp"
#include "IRC_Channel.hpp"
#include "IRC_Server.hpp"
#include "IRC_Utils.hpp"

#include <iostream>

// _name = nickname;
// _ident = user;
// _realname = realname;

IRC_User::IRC_User(struct pollfd* pollPosition)
	: _pollPosition(pollPosition)
	, _name("*")
	, _ident("")
	, _realname("")
	, _hostname("")
	, _pass("")
	, _access(0)
	, _pingTimeout(time(NULL) + REGTOUT)
	, _idleTime(time(NULL) + IDLETOUT)
	, _loginTime(time(NULL))
	, _deleteMarked(false)
{
}

IRC_User::IRC_User(struct pollfd* pollPosition, const std::string& name, const std::string& ident, const std::string& realname)
	: _pollPosition(pollPosition)
	, _name(name)
	, _ident(ident)
	, _realname(realname)
	, _access(0)
	, _pingTimeout(time(NULL) + REGTOUT)
	, _idleTime(time(NULL) + IDLETOUT)
	, _loginTime(time(NULL))
	, _deleteMarked(false)
{
}

IRC_User::~IRC_User()
{}

int	IRC_User::getFd() const
{
	return (this->_pollPosition->fd);
}

const std::string	IRC_User::getMask() const
{
	return (this->_name + "!" + this->_ident + "@" + this->_hostname);
}

void IRC_User::setHost(const std::string& value)
{
	this->_hostname = value;
}

const std::string& IRC_User::getHost() const
{
	return (this->_hostname);
}

void	IRC_User::setName(const std::string& value)
{
	this->_name = value;
}

const std::string&	IRC_User::getName() const
{
	return (this->_name);
}

int	IRC_User::getAccess() const
{
	return (this->_access);
}

struct pollfd*	IRC_User::getPollPosition()
{
	return (this->_pollPosition);
}

void	IRC_User::setPollPosition(struct pollfd* value)
{
	this->_pollPosition = value;
}

bool	IRC_User::addChannel(IRC_Channel& channel)
{
	return (this->_channels.insert(&channel).second);
}

bool	IRC_User::removeChannel(IRC_Channel& channel)
{
	return (this->_channels.erase(&channel));
}

bool	IRC_User::isInChannel(IRC_Channel& channel)
{
	return (this->_channels.find(&channel) != this->_channels.end());
}

const IRC_User::channelsType IRC_User::getChannels() const
{
	return (this->_channels);
}

void IRC_User::markForDelete()
{
	this->_deleteMarked = true;
}


bool IRC_User::deleteMarked() const
{
	return (this->_deleteMarked);
}

void	IRC_User::send(const std::string& data)
{
	if (this->_deleteMarked)
	{
		return ;
	}
	if (data.size() > LINELEN - 2)
	{
		this->_outputBuffer += data.substr(0, LINELEN - 2) + "\r\n";
	}
	else
	{
		this->_outputBuffer += data + "\r\n";
	}
	this->_pollPosition->events |= POLLOUT;
}

void	IRC_User::reply(const IRC_Server& server, const std::string& data)
{
	std::string preparedMsg = ":" + server.getServerName() + " " + data;
	
	this->sendLimitedMessage(preparedMsg);
}

IRC_User::usersType* IRC_User::getCommonUsers()
{
	usersType* commonUsers = new IRC_Channel::usersType();

	for (channelsIterator it = this->_channels.begin(); it != this->_channels.end(); ++it)
	{
		const usersType& users = (*it)->getUsers();

		commonUsers->insert(users.begin(), users.end());
	}
	if (commonUsers->empty())
	{
		commonUsers->insert(this);
	}

	return (commonUsers);
}

IRC_User::usersType* IRC_User::getCommonUsersExcept(const IRC_User& user)
{
	usersType* commonUsers = this->getCommonUsers();

	commonUsers->erase(const_cast<IRC_User*>(&user));
	return (commonUsers);
}

void IRC_User::sendCommonUsers(const std::string& data)
{
	usersType* commonUsers = this->getCommonUsers();

	for (usersIterator it = commonUsers->begin(); it != commonUsers->end(); ++it)
	{
		(*it)->send(data);
	}

	delete commonUsers;
}

void IRC_User::sendCommonUsersExceptMe(const IRC_User& user, const std::string& data)
{
	usersType* commonUsers = this->getCommonUsersExcept(*this);

	for (usersIterator it = commonUsers->begin(); it != commonUsers->end(); ++it)
	{
		(*it)->send(user, data);
	}
	delete commonUsers;
}

void IRC_User::sendCommonUsersExceptMe(const IRC_User& user, const std::string& data, const std::string& lastParam)
{
	usersType* commonUsers = this->getCommonUsersExcept(*this);

	for (usersIterator it = commonUsers->begin(); it != commonUsers->end(); ++it)
	{
		(*it)->send(user, data, lastParam);
	}
	delete commonUsers;
}

void IRC_User::send(const IRC_Server& server, const std::string& data)
{
	this->send(":" + server.getServerName() + " " + data);
}

void IRC_User::send(const IRC_Server& server, const std::string& data, const std::string& lastParam)
{
	if (lastParam.empty())
		this->send(":" + server.getServerName() + " " + data);
	else
		this->send(":" + server.getServerName() + " " + data + " :" + lastParam);
}

void IRC_User::send(const IRC_User& user, const std::string& data)
{
	this->send(":" + user.getMask() + " " + data);
}

void IRC_User::send(const IRC_User& user, const std::string& data, const std::string& lastParam)
{
	if (lastParam.empty())
		this->send(":" + user.getMask() + " " + data);
	else
		this->send(":" + user.getMask() + " " + data + " :" + lastParam);
}

void IRC_User::addReceiveData(char* buffer)
{
	this->_inputBuffer += buffer;
	if (this->_inputBuffer.size() > 4096)
	{
		std::cout << "desconexion necesaria" << std::endl;
	}
}

time_t IRC_User::getPingTimeout()
{
	return (this->_pingTimeout);
}

void IRC_User::setPingTimeout(time_t myTimeOut)
{
	this->_pingTimeout = time(NULL) + myTimeOut;
}

void IRC_User::resetIdle(void)
{
	this->_idleTime = time(NULL) + IDLETOUT;
}

void IRC_User::disablePingTimeout(void)
{
	this->_pingTimeout = 0;
}

void IRC_User::setIdleTime(time_t value)
{
	this->_idleTime = value;
}

time_t IRC_User::getIdleTime(void)
{
	return (this->_idleTime);
}

time_t IRC_User::getLoginTime(void)
{
	return (this->_loginTime);
}

const std::string&	IRC_User::getIdent() const
{
	return (this->_ident);
}

const std::string&	IRC_User::getRealName() const
{
	return (this->_realname);
}

const std::string& 	IRC_User::getPingText() const
{
	return (this->_pingText);
}

void	IRC_User::setIdent(const std::string& ident)
{
	this->_ident = ident;
}

void	IRC_User::setRealName(const std::string& realname)
{
	this->_realname = realname;
}

void	IRC_User::setAccess(int access)
{
	this->_access = access;
}

const std::string&	IRC_User::getPass() const
{
	return (this->_pass);
}

void	IRC_User::setPass(const std::string& pass)
{
	this->_pass = pass;
}

void    IRC_User::sendLimitedMessage(const std::string& data)
{
	std::string message;
	std::size_t dataLength = data.size();

    if (dataLength <= MSGLENGTH)
	{
        this->send(data);
    }
	else
	{
		std::size_t secondColonIndex = secondColonPosition(data);
        std::string header = data.substr(0, secondColonIndex + 1);
        size_t		headerLength = header.size();

        std::size_t initIndex = header.size();
        while (initIndex < dataLength)
		{
            message = "";
			std::size_t endIndex = std::min(initIndex + MSGLENGTH - headerLength, dataLength);
            while (endIndex < dataLength && endIndex > initIndex && data[endIndex] != ' ') {
                --endIndex;
            }

            std::size_t blockLength = endIndex - initIndex;
            message = header + data.substr(initIndex, blockLength);
            this->send(message);

            initIndex = endIndex + 1;
        }
    }
}
