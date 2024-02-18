/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_KillCommand.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:11:38 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:11:39 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/IRC_KillCommand.hpp"
#include "IRC_Server.hpp"

IRC_KillCommand::IRC_KillCommand()
	: IRC_ACommand("KILL", 2, OPERATOR)
{}

void IRC_KillCommand::execute(IRC_Message& message) {
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	IRC_User* targetUser = server.findUserByName(message[0]);

	if (!targetUser)
	{
		user.reply(server, ERR_NOSUCHNICK(user.getName(), targetUser->getName()));
		return ;
	}

	server.killUser(user, *targetUser, "Killed by " + user.getName() + ": (" + message[1] + ")");
}
