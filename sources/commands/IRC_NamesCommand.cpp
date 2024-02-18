/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_NamesCommand.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:13:15 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:14:18 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "commands/IRC_NamesCommand.hpp"
# include "IRC_Channel.hpp"
# include "IRC_Server.hpp"

static void	nicknamesList(IRC_User& user, IRC_Server& server, IRC_Channel *channel)
{
	std::string names;

	for (IRC_Channel::usersConstIterator it = channel->getUsers().begin(); it != (channel->getUsers()).end(); ++it)
  {
		if (channel->isOperator(**it))
			names += "@";
		if (channel->isVoice(**it))
			names += "+";
		names += (*it)->getName() + " ";
	}
	user.reply(server, RPL_NAMREPLY(user.getName(), channel->getName(), names));
}

IRC_NamesCommand::IRC_NamesCommand()
	: IRC_ACommand("NAMES", 0, REGISTERED)
{}

void IRC_NamesCommand::execute(IRC_Message& message) {
	
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	std::string channelName;

	if (!message.empty())
		channelName = message[0];
	else
		channelName	= "*";

	if (!message.empty())
	{
		IRC_Channel *channel = message.getServer().findChannelByName(channelName);
		if (channel)
			nicknamesList(user, server, channel);
	}
	user.reply(server, RPL_ENDOFNAMES(user.getName(), channelName));
}
