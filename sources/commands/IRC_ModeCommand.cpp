/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_ModeCommand.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:12:45 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 21:14:02 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/IRC_ModeCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Errors.hpp"
#include "tools.hpp"

#include <string>

IRC_ModeCommand::IRC_ModeCommand()
	: IRC_ACommand("MODE", 1, REGISTERED)
{}

void IRC_ModeCommand::execute(IRC_Message& message)
{
	const std::string& target = message[0];

	if (isChannel(target))
	{
		this->_executeChannel(message);
	}
}

void IRC_ModeCommand::_executeChannel(IRC_Message& message)
{
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	IRC_Channel* targetChannel = server.findChannelByName(message[0]);
	std::stringstream creationTime;

	if (!targetChannel)
	{
		user.reply(server, ERR_NOSUCHCHANNEL(user.getName(), message[0]));
		return ;
	}
	if (message.size() == 1) //empty modelist parameter
	{
		creationTime << targetChannel->getCreationTime();
		user.reply(server, RPL_CHANNELMODEIS(user.getName(), targetChannel->getName(), targetChannel->getModes(user)));
		user.reply(server, RPL_CREATIONTIME(user.getName(), targetChannel->getName(), creationTime.str()));
	}
	else //modifying chan modes
	{
	  std::vector<std::string> modes(message.getParams().begin() + 1, message.getParams().end());
		std::string response;

		response = targetChannel->setModes(user, server, modes);
		if (!response.empty())
			targetChannel->send(user, "MODE " + targetChannel->getName() + " " + response);
	}
}
