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

void IRC_User::setName(const std::string& value) {
	this->_name = value;
}

const std::string& IRC_User::getName() const {
	return this->_name;
}

int IRC_User::getAccess() const {
	return this->_access;
}

struct pollfd* IRC_User::getPollPosition() {
	return this->_pollPosition;
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

/*const IRC_User::channelsSetType IRC_User::getCommonUsers() const {

	//IRC_Channel::usersSetType allUsers;
	IRC_Channel::usersSetIterator users;
	const IRC_Channel::usersSetIterator channelUsers;

	for (IRC_User::channelsSetConstIterator it = this->_channels.begin(); it != this->_channels.end(); ++it) {
		// Convertir el puntero a un conjunto constante
		//allUsers = *(*it)->getUsers();

		(*channelUsers)-> = (*it)->;
		(*users).insert
		insert((*it)->getUsers());
		//users.insert(it->getUsers());  //<-pregunta
	}
	// que tipo de contenido set tiene que generar channel, un * o un []
}*/

void IRC_User::addReceiveData(char* buffer) {
	// std::cout << this->_inputBuffer.size() << std::endl;
	// std::cout << buffer << std::endl;
	this->_inputBuffer += buffer;
	if (this->_inputBuffer.size() > 4096) {
		//desconectar al cliente por exceso de información recibida
		std::cout << "desconexion necesaria" << std::endl;
	}
	// std::cout << this->_inputBuffer << std::endl;
}

const std::string IRC_User::getBuffer() const{
	return (this->_inputBuffer);
}

