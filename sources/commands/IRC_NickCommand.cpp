/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_NickCommand.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:14:26 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:15:20 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/IRC_NickCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Utils.hpp"
#include "IRC_Errors.hpp"

IRC_NickCommand::IRC_NickCommand()
	: IRC_ACommand("NICK", 1, UNREGISTERED)
{}

void IRC_NickCommand::execute(IRC_Message& message)
{
	std::string newName = message[0];
	IRC_User& user = message.getUser();
	IRC_Server& server = message.getServer();
	IRC_Response response;

	response = server.changeNameUser(user, newName);
	if (response == ERRONEOUS_NICK)
	{
		user.send(ERR_ERRONEOUSNICKNAME(user.getName(), newName));
	}
	else if (response == NICK_IN_USE)
	{
		user.send(ERR_NICKNAMEINUSE(newName));
	}
	else if (user.getAccess() == UNREGISTERED)
  	{
		server.setPendingUser(user);
	}
}
