/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_TopicCommand.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:17:47 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:18:24 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/IRC_TopicCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Errors.hpp"

IRC_TopicCommand::IRC_TopicCommand()
	: IRC_ACommand("TOPIC", 1, REGISTERED)
{}

void IRC_TopicCommand::execute(IRC_Message& message)
{
	const std::string& name = message[0];
	IRC_Channel *channel = message.getServer().findChannelByName(name);
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	
	if (!channel)
	{
		user.reply(server, ERR_NOSUCHCHANNEL(user.getName(), name));
		return ;
	}
	if (message.size() == 1)
	{
		if (channel->getTopic().empty())
		{
			user.reply(server, RPL_NOTOPIC(user.getName(), channel->getName()));
		}
		else
		{
			std::stringstream ss;

			ss << channel->getTopicTime();
			user.reply(server, RPL_TOPIC(user.getName(), channel->getName(), channel->getTopic()));
			user.reply(server, RPL_TOPICWHOTIME(user.getName(), channel->getName(), channel->getTopicUser(), ss.str()));
		}
		return ;
	}
	if (!user.isInChannel(*channel))
	{
		user.reply(server, ERR_NOTONCHANNEL(user.getName(), name));
		return ;
	}
	if (channel->hasTopicProtection() && !channel->isOperator(user)) 
	{
		user.reply(server, ERR_CHANOPRIVSNEEDED(user.getName(), channel->getName()));
		return ;
	}
	const std::string& newTopic = message[1];
	
	server.changeChannelTopic(user, *channel, newTopic);
}
