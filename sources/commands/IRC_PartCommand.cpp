/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_PartCommand.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:15:48 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:15:50 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/IRC_PartCommand.hpp"
#include "IRC_Server.hpp"

IRC_PartCommand::IRC_PartCommand()
	: IRC_ACommand("PART", 1, REGISTERED)
{}

void IRC_PartCommand::execute(IRC_Message& message)
{
	const std::string& channelName = message[0];

	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	IRC_Channel* channel = server.findChannelByName(channelName);
	IRC_Response response;
	std::string msg;

	if (message.size() > 1)
	{
		msg = message[1];
	}

	if (!channel)
	{
		user.send(ERR_NOSUCHCHANNEL(user.getName(), channelName));
		return ;
	}

	response = server.partUser(user, *channel, msg);

	if (response == NOT_IN_CHANNEL)
	{
		user.send(ERR_NOTONCHANNEL(user.getName(), channelName));
	}
}
