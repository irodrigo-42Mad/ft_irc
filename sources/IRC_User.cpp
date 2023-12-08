#include "IRC_User.hpp"
#include "IRC_Channel.hpp"
#include "IRC_Server.hpp"

#include <iostream>

IRC_User::IRC_User(struct pollfd* pollPosition)
	: _pollPosition(pollPosition)
	, _access(0)
{
	std::cout << "User '" << this->_name << "' created" << std::endl;
}

IRC_User::IRC_User(struct pollfd* pollPosition, const std::string& name, const std::string& ident, const std::string& realname, IRC_Server& server)
	: _pollPosition(pollPosition)
	, _name(name)
	, _ident(ident)
	, _realname(realname)
	, _access(0)
	, _server(&server)
{
	std::cout << "User '" << this->_name << "' created" << std::endl;
}

IRC_User::~IRC_User() {
	std::cout << "User '" << this->_name << "' destroyed" << std::endl;
}

int IRC_User::getFd() const {
	return this->_pollPosition->fd;
}

const std::string IRC_User::getMask() const {
	return (this->_name + "!" + this->_ident + "@" + this->_hostname);
}

const std::string& IRC_User::getName() const {
	return this->_name;
}

bool IRC_User::addChannel(IRC_Channel* channel) {
	return this->_channels.insert(channel).second;	
}

bool IRC_User::removeChannel(IRC_Channel* channel) {
	return this->_channels.erase(channel);
}

bool IRC_User::isInChannel(IRC_Channel* channel) {
	return (this->_channels.find(channel) != this->_channels.end());
}

const IRC_User::channelsSetType IRC_User::getChannels() const {
	return this->_channels;
	//return std::set<IRC_Channel*>(this->_channels.begin(), this->_channels.end());
}

const IRC_User::channelsSetType IRC_User::getCommonUsers() const {
	IRC_Channel::usersSetIterator users;
	const IRC_Channel::usersSetIterator channelUsers;

	for (IRC_User::channelsSetConstIterator it = this->_channels.begin(); it != this->_channels.end(); ++it) {
		channelUsers = it->getUsers();
		users.insert(it->getUsers());
	}
}

void IRC_User::addReceiveData(char* buffer) {
	if (this->_inputBuffer.size() > 4096) {
		//desconectar al cliente por exceso de información recibida
	}
	this->_inputBuffer += buffer;
}
