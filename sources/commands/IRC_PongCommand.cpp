/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_PongCommand.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:17:00 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:17:01 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/IRC_PongCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_User.hpp"

IRC_PongCommand::IRC_PongCommand()
	: IRC_ACommand("PONG", 1, UNREGISTERED)
{}

void IRC_PongCommand::execute(IRC_Message &message)
{
	IRC_User &user = message.getUser();
	IRC_Server &server = message.getServer();
	const std::string &pingText = message[0];

	if (user.getAccess() == PENDING)
	{
		if (pingText == user.getPingText())
		{
			user.setAccess(REGISTERED);
			user.disablePingTimeout();
			server.sendWelcomeMsg(user);
			server.sendMOTDMsg(user);
		}
		else
		{
			server.quitUser(user, "Incorrect ping reply for registration");
		}
	}
	user.disablePingTimeout();
}
