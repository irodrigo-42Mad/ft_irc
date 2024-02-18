/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Channel.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:07:35 by icastell          #+#    #+#             */
/*   Updated: 2024/02/18 21:21:42 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC_Channel.hpp"
#include "IRC_User.hpp"
#include "IRC_Server.hpp"
#include "IRC_Structs.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

IRC_Channel::IRC_Channel(std::string const &name, IRC_User& creator)
  : _creationTime(time(NULL))
	, _channelName(name)
  , _topic("")
  , _key("")
  , _limit(0)
  , _private(false)
  , _secret(false)
  , _moderate(false)
  , _noExternalMessages(false)
  , _invite(false)
  , _topicProtection(false)
{
    this->addUser(creator);
    this->addOperator(creator);
}

IRC_Channel::~IRC_Channel()
{
}

bool    IRC_Channel::addUser(IRC_User& userToAdd)
{
    return (this->_users.insert(&userToAdd).second);
}

void    IRC_Channel::removeUser(IRC_User& userToDelete)
{	
    this->_users.erase(&userToDelete);
}

bool IRC_Channel::hasUser(const IRC_User& user) const
{
	return (this->_users.find(const_cast<IRC_User*>(&user)) != this->_users.end());
}

bool IRC_Channel::empty() const
{
	return (this->_users.empty());
}

void IRC_Channel::sendExcept(const IRC_User* exceptUser, const std::string &data)
{
	if (exceptUser)
	{
		this->_users.erase(const_cast<IRC_User*>(exceptUser));
	}
	this->send(data);
	if (exceptUser)
	{
		this->_users.insert(const_cast<IRC_User*>(exceptUser));
	}
}

void IRC_Channel::send(const IRC_User& user, const std::string& data)
{
	this->sendExcept(NULL, user, data);
}

void IRC_Channel::send(const IRC_Server& server, const std::string& data)
{
	this->sendExcept(NULL, server, data);
}

void IRC_Channel::send(const IRC_User& user, const std::string& data, const std::string& lastParameter)
{
	if (lastParameter.empty())
		this->sendExcept(NULL, user, data);
	else
		this->sendExcept(NULL, user, data, lastParameter);
}

void IRC_Channel::send(const IRC_Server& server, const std::string& data, const std::string& lastParameter)
{
	if (lastParameter.empty())
		this->sendExcept(NULL, server, data);
	else
		this->sendExcept(NULL, server, data, lastParameter);
}

void IRC_Channel::send(const std::string& data)
{
	for (usersConstIterator it = this->_users.begin(); it != this->_users.end(); ++it)
	{
		(*it)->send(data);
	}
}

void IRC_Channel::sendExcept(const IRC_User* exceptUser, const IRC_User& user, const std::string& data)
{
	this->sendExcept(exceptUser, ":" + user.getMask() + " " + data);
}

void IRC_Channel::sendExcept(const IRC_User* exceptUser, const IRC_User& user, const std::string& data, const std::string& lastParameter)
{
	this->sendExcept(exceptUser, ":" + user.getMask() + " " + data + " :" + lastParameter);
}

void IRC_Channel::sendExcept(const IRC_User* exceptUser, const IRC_Server& server, const std::string& data)
{
	this->sendExcept(exceptUser, ":" + server.getServerName() + " " + data);
}

void IRC_Channel::sendExcept(const IRC_User* exceptUser, const IRC_Server& server, const std::string& data, const std::string& lastParameter)
{
	this->sendExcept(exceptUser, ":" + server.getServerName() + " " + data + " :" + lastParameter);
}

time_t	IRC_Channel::getCreationTime() const
{
	return (this->_creationTime);
}

const std::string& IRC_Channel::getTopic() const
{
	return (this->_topic);
}

const std::string& IRC_Channel::getTopicUser() const
{
	return (this->_topicUser);
}

time_t IRC_Channel::getTopicTime() const
{
	return (this->_topicTime);
}

const std::string& IRC_Channel::getName() const
{
    return (this->_channelName);
}

const IRC_Channel::usersType& IRC_Channel::getUsers() const
{
    return (this->_users);
}

int IRC_Channel::getNumUsers() const
{
    return (this->_users.size());
}

void IRC_Channel::setTopic(const IRC_User& user, const std::string& topic)
{
	this->_topic = topic;
	this->_topicUser = user.getName();
	this->_topicTime = time(NULL);
}

static bool matchWildcard(const std::string& mask, const std::string& nick) {
    size_t maskIndex = 0, nickIndex = 0;
    size_t maskLength = mask.length(), nickLength = nick.length();
    
    while (maskIndex < maskLength && nickIndex < nickLength) {
        if (mask[maskIndex] == '*') {
            while (maskIndex < maskLength && mask[maskIndex] == '*') {
                ++maskIndex;
            }
            if (maskIndex == maskLength) {
                return true;
            }
            
            while (nickIndex < nickLength && nick[nickIndex] != mask[maskIndex]) {
                ++nickIndex;
            }
        } else if (mask[maskIndex] == '?' || mask[maskIndex] == nick[nickIndex]) {
            ++maskIndex;
            ++nickIndex;
        } else {
            return false;
        }
    }
    
    return maskIndex == maskLength && nickIndex == nickLength;
}

std::string IRC_Channel::setModes(IRC_User& user, IRC_Server& server, const std::vector<std::string>& modeList)
{
	std::string result_mode;
	std::vector<std::string> result_param;
	const std::string& modes = modeList[0];
	bool plus = true;
	size_t paramIndex = 1;
	int modeCount = 0;

	if (modes[0] != '+' && modes[0] != '-')
		result_mode += '+';

	for (std::string::const_iterator it = modes.begin(); it != modes.end() && modeCount < MODES; ++it)
	{
		if (!this->isOperator(user) && user.getAccess() != OPERATOR)
		{
			user.reply(server, ERR_CHANOPRIVSNEEDED(user.getName(), this->getName()));
			break ;
		}
		if (*it == '+')
		{
			plus = true;
			if (!result_mode.empty() && (*result_mode.rbegin() == '+' || *result_mode.rbegin() == '-'))
			{
				result_mode.erase(result_mode.size() - 1);
			}
			result_mode += '+';
		}
		else if (*it == '-')
		{
			plus = false;
			if (!result_mode.empty() && (*result_mode.rbegin() == '+' || *result_mode.rbegin() == '-'))
			{
				result_mode.erase(result_mode.size() - 1);
			}
			result_mode += '-';
		}
		else if (*it == 'i')
		{
			if (plus && this->setInvite())
			{
				++modeCount;
				result_mode += "i";
			}
			else if (!plus && this->unsetInvite())
			{
				++modeCount;
				result_mode += "i";
			}
		}
		else if (*it == 'k')
		{
			if (paramIndex == modeList.size())
				user.reply(server, ERR_INVALIDMODEPARAM(user.getName(), this->getName(), "k"));
			else
			{
				const std::string& key = modeList[paramIndex];

				if (plus && this->setKey(key))
				{
					++modeCount;
					result_mode += "k";
					result_param.push_back(key);
				}
				else if (!plus && this->unsetKey(key))
				{
					++modeCount;
					result_mode += "k";
					result_param.push_back(key);
				}
				++paramIndex;
			}
		}
		else if (*it == 'l')
		{
			if (paramIndex == modeList.size())
				user.reply(server, ERR_INVALIDMODEPARAM(user.getName(), this->getName(), "l"));
			else
			{
				const std::string& limit = modeList[paramIndex];

				if (plus && this->setLimit(atoi(limit.c_str())))
				{
					++modeCount;
					result_mode += "l";
					result_param.push_back(limit);
					++paramIndex;
				}
				else if (!plus && this->unsetLimit())
				{
					++modeCount;
					result_mode += "l";
				}
			}
		}
		else if (*it == 'm')
		{
			if (plus && this->setModerate())
			{
				++modeCount;
				result_mode += "m";
			}
			else if (!plus && this->unsetModerate())
			{
				++modeCount;
				result_mode += "m";
			}
		}
		else if (*it == 'n')
		{
			if (plus && this->setNoExternalMessages())
			{
				++modeCount;
				result_mode += "n";
			}
			else if (!plus && this->unsetNoExternalMessages())
			{
				++modeCount;
				result_mode += "n";
			}
		}
		else if (*it == 'p')
		{
			if (plus && this->setPrivate())
			{
				++modeCount;
				result_mode += "p";
			}
			else if (!plus && this->unsetPrivate())
			{
				++modeCount;
				result_mode += "p";
			}
		}
		else if (*it == 's')
		{
			if (plus && this->setSecret())
			{
				++modeCount;
				result_mode += "s";
			}
			else if (!plus && this->unsetSecret())
			{
				++modeCount;
				result_mode += "s";
			}
		}
		else if (*it == 't')
		{
			if (plus && this->setTopicProtection())
			{
				++modeCount;
				result_mode += "t";
			}
			else if (!plus && this->unsetTopicProtection())
			{
				++modeCount;
				result_mode += "t";
			}
		}
		else if (*it == 'b')
		{
			if (paramIndex == modeList.size())
				user.reply(server, ERR_INVALIDMODEPARAM(user.getName(), this->getName(), "b"));
			else
			{
				const std::string& mask = modeList[paramIndex]; 

				if (plus && this->addBan(mask))
				{
					++modeCount;
					result_mode += "b";
					result_param.push_back(mask);
				}
				else if (!plus && this->removeBan(mask))
				{
					++modeCount;
					result_mode += "b";
					result_param.push_back(mask);
				}
				++paramIndex;
			}
		}
		else if (*it == 'o')
		{
			if (paramIndex == modeList.size())
				user.reply(server, ERR_INVALIDMODEPARAM(user.getName(), this->getName(), "o"));
			else
			{
				IRC_User* targetUser = server.findUserByName(modeList[paramIndex]);
			
				if (targetUser)
				{
					if (plus && !this->isOperator(*targetUser))
					{
						++modeCount;
						result_mode += "o";
						this->addOperator(*targetUser);
						result_param.push_back(targetUser->getName());
					}
					else if (!plus && this->isOperator(*targetUser))
					{
						++modeCount;
						result_mode += "o";
						this->removeOperator(*targetUser);
						result_param.push_back(targetUser->getName());
					}
				}
				else
				{
					user.reply(server, ERR_NOSUCHNICK(user.getName(), modeList[paramIndex]));
				}
				++paramIndex;
			}
		}	
		else if (*it == 'v')
		{
			if (paramIndex == modeList.size())
				user.reply(server, ERR_INVALIDMODEPARAM(user.getName(), this->getName(), "v"));
			else
			{
				IRC_User* targetUser = server.findUserByName(modeList[paramIndex]);
			
				if (targetUser)
				{
					if (plus && !this->isVoice(*targetUser))
					{
						++modeCount;
						result_mode += "v";
						this->addVoice(*targetUser);
						result_param.push_back(targetUser->getName());
					}
					else if (!plus && this->isVoice(*targetUser))
					{
						++modeCount;
						result_mode += "v";
						this->removeVoice(*targetUser);
						result_param.push_back(targetUser->getName());
					}
				}
				else
				{
					user.reply(server, ERR_NOSUCHNICK(user.getName(), modeList[paramIndex]));
				}
				++paramIndex;
			}
		}	
		else
			user.reply(server, ERR_UNKNOWNMODE(user.getName(), *it, this->getName()));
	}
	
	for (std::vector<std::string>::iterator it = result_param.begin(); it != result_param.end(); ++it)
	{
		result_mode += " " + *it;
	}

	if (result_mode.size() > 1)
		return (result_mode);
	else
		return ("");
}

std::string IRC_Channel::getModes(const IRC_User& user) const
{
	std::string modes;
	std::string params;

	if (this->_invite)
		modes += 'i';
	if (!this->_key.empty())
	{
		modes += 'k';
		if (this->hasUser(user))
			params += " " + this->_key;
		else
			params += " <key>";
	}
	if (this->_limit)
	{
		std::stringstream ss;
		
		ss << this->_limit;
		modes += 'l';
		params += " " + ss.str();
	}
	if (this->_moderate)
		modes += 'm';
	if (this->_noExternalMessages)
		modes += 'n';
	if (this->_private)
		modes += 'p';
	if (this->_secret)
		modes += 's';
	if (this->_topicProtection)
		modes += 't';
	if (modes.empty())
		return "";
	return "+" + modes + params;
}

bool IRC_Channel::addBan(const std::string& value)
{
	return (this->_bans.insert(value).second);
}

bool IRC_Channel::isBanned(const IRC_User& user) const
{
	for (bansConstIterator it = this->_bans.begin(); it != this->_bans.end(); ++it)
	{
		if (matchWildcard(*it, user.getMask()))
			return (true);
	}
	return (false);
}

bool IRC_Channel::removeBan(const std::string& value)
{
	return (this->_bans.erase(value));
}

bool IRC_Channel::addOperator(IRC_User& user)
{
	return (this->_operUsers.insert(&user).second);
}

bool IRC_Channel::isOperator(const IRC_User& user) const
{
	return (this->_operUsers.find(const_cast<IRC_User*>(&user)) != this->_operUsers.end());
}

bool IRC_Channel::removeOperator(IRC_User& user)
{
	return (this->_operUsers.erase(&user));
}

bool IRC_Channel::addVoice(IRC_User& user)
{
	return (this->_voiceUsers.insert(&user).second);
}

bool IRC_Channel::isVoice(const IRC_User& user) const
{
	return (this->_voiceUsers.find(const_cast<IRC_User*>(&user)) != this->_voiceUsers.end());
}

bool IRC_Channel::removeVoice(IRC_User& user)
{
	return (this->_voiceUsers.erase(&user));
}

bool IRC_Channel::setInvite()
{
	if (!this->_invite)
	{
		this->_invite = true;
		return (true);
	}
	return (false);
}

bool IRC_Channel::hasInvite() const
{
	return (this->_invite);
}

bool IRC_Channel::unsetInvite()
{
	if (this->_invite)
	{
		this->_invite = false;
		return (true);
	}
	return (false);
}

bool IRC_Channel::setKey(const std::string& value)
{
	if (this->_key.empty())
	{
		this->_key = value;
		return (true);
	}
	return (false);
}

bool IRC_Channel::hasKey() const
{
	return (!this->_key.empty());
}

bool IRC_Channel::unsetKey(const std::string& value)
{
	if (this->_key == value)
	{
		this->_key.clear();
		return (true);
	}
	return (false);
}

bool IRC_Channel::isSameKey(const std::string& value) const
{
	return (this->_key.empty() || this->_key == value);
}

bool IRC_Channel::setPrivate()
{
	if (!this->_private)
	{
		this->_private = true;
		return (true);
	}
	return (false);
}

bool IRC_Channel::hasPrivate() const
{
	return (this->_private);
}

bool IRC_Channel::unsetPrivate()
{
	if (this->_private)
	{
		this->_private = false;
		return (true);
	}
	return (false);
}

bool IRC_Channel::setLimit(size_t value)
{
	if (this->_limit != value)
	{
		this->_limit = value;
		return (true);
	}
	return (false);
}

bool IRC_Channel::hasLimit() const
{
	return (this->_limit > 0);
}

bool IRC_Channel::unsetLimit()
{
	if (this->_limit)
	{
		this->_limit = 0;
		return (true);
	}
	return (false);
}

bool IRC_Channel::isFull() const
{
	return (this->_limit && this->_users.size() >= this->_limit);
}

bool IRC_Channel::setNoExternalMessages()
{
	if (!this->_noExternalMessages)
	{
		this->_noExternalMessages = true;
		return (true);
	}
	return (false);
}

bool IRC_Channel::hasNoExternalMessages() const
{
	return (this->_noExternalMessages);
}

bool IRC_Channel::unsetNoExternalMessages()
{
	if (this->_noExternalMessages)
	{
		this->_noExternalMessages = false;
		return (true);
	}
	return (false);
}

bool IRC_Channel::setTopicProtection()
{
	if (!this->_topicProtection)
	{
		this->_topicProtection = true;
		return (true);
	}
	return (false);
}

bool IRC_Channel::hasTopicProtection() const
{
	return (this->_topicProtection);
}


bool IRC_Channel::unsetTopicProtection()
{
	if (this->_topicProtection)
	{
		this->_topicProtection = false;
		return (true);
	}
	return (false);
}

bool IRC_Channel::setModerate()
{
	if (!this->_moderate)
	{
		this->_moderate = true;
		return (true);
	}
	return (false);
}

bool IRC_Channel::hasModerate() const
{
	return (this->_moderate);
}

bool IRC_Channel::unsetModerate()
{
	if (this->_moderate)
	{
		this->_moderate = false;
		return (true);
	}
	return (false);
}

bool IRC_Channel::setSecret()
{
	if (!this->_secret)
	{
		this->_secret = true;
		return (true);
	}
	return (false);
}

bool IRC_Channel::hasSecret() const
{
	return (this->_secret);
}

bool IRC_Channel::unsetSecret()
{
	if (this->_secret)
	{
		this->_secret = false;
		return (true);
	}
	return (false);
}


