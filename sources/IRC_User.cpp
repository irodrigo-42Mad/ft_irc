#include "IRC_User.hpp"
#include "IRC_Channel.hpp"
#include "IRC_Server.hpp"

#include <iostream>


// _name = nickname;
// _ident = user;
// _realname = realname;

IRC_User::IRC_User(struct pollfd* pollPosition)
	: _pollPosition(pollPosition)
	, _name("*")
	, _realname("*")
	, _ident("*")
	, _access(0)
	, _timeout(0)
	, _registratedT(0)

{
	std::cout << "User '" << this->_name << "' created" << std::endl;
}

IRC_User::IRC_User(struct pollfd* pollPosition, const std::string& name, const std::string& ident, const std::string& realname)
	: _pollPosition(pollPosition)
	, _name(name)
	, _ident(ident)
	, _realname(realname)
	, _access(0)
	, _timeout(0)
	, _registratedT(0)
{
	std::cout << "User '" << this->_name << "' created" << std::endl;
}

IRC_User::~IRC_User()
{
	std::cout << "User '" << this->_name << "' destroyed" << std::endl;
}

int	IRC_User::getFd() const
{
	return (this->_pollPosition->fd);
}

const std::string	IRC_User::getMask() const {
	return (this->_name + "!" + this->_ident + "@" + this->_hostname);
}

void	IRC_User::setName(const std::string& value) {
	this->_name = value;
}

const std::string&	IRC_User::getName() const {
	return (this->_name);
}

int	IRC_User::getAccess() const {
	return (this->_access);
}

struct pollfd*	IRC_User::getPollPosition() {
	return (this->_pollPosition);
}

bool	IRC_User::addChannel(IRC_Channel* channel) {
	return (this->_channels.insert(channel).second);
}

bool	IRC_User::removeChannel(IRC_Channel* channel) {
	return (this->_channels.erase(channel));
}

bool	IRC_User::isInChannel(IRC_Channel* channel) {
	return (this->_channels.find(channel) != this->_channels.end());
}

const IRC_User::channelsSetType IRC_User::getChannels() const {
	return (this->_channels);
	//return std::set<IRC_Channel*>(this->_channels.begin(), this->_channels.end());
}

void	IRC_User::sendMessage(const std::string& message)
{
	this->_outputBuffer += message + "\r\n";
	this->_pollPosition->events |= POLLOUT;
/*
	std::string bufferToSend = message + "\r\n";
	int bufferLength = bufferToSend.length();
	int	numBytes;
	
	numBytes = send(this->getFd(), bufferToSend.c_str(), bufferLength, 0);
	while (bufferLength > 0)
	{
		if (numBytes < 0)
		{
    	    throw std::runtime_error("Error while sending a message to the user!");
			return ;
		}
		else if (numBytes < bufferLength)
		{
			this->_server->userPolloutByFd(this->_pollPosition->fd);
			break ;
		}
		bufferToSend += numBytes;
		bufferLength -= numBytes;
	}
	return ;
*/
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

time_t IRC_User::getUserTimeOut()
{
	return (this->_timeout);
}

void IRC_User::setUserTimeout(time_t myTimeOut)
{
	this->_timeout = myTimeOut;
}

// reseting time of user commands for server controls
void IRC_User::_resetTime(void)
{
	this->_time = time(NULL);
}

time_t IRC_User::_getTime(void)
{
	return (this->_time);
}

time_t IRC_User::_getRegTime(void)
{
	return (this->_registratedT);
}

const std::string&	IRC_User::getIdent() const
{
	return (this->_ident);
}

const std::string&	IRC_User::getRealName() const
{
	return (this->_realname);
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