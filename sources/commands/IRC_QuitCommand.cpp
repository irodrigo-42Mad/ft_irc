/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_QuitCommand.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:17:29 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:17:31 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/IRC_QuitCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Errors.hpp"

IRC_QuitCommand::IRC_QuitCommand()
	: IRC_ACommand("QUIT", 0, UNREGISTERED)
{}

void IRC_QuitCommand::execute(IRC_Message& message)
{
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();

	if (message.size() == 0)
		server.quitUser(user, "");
	else
		server.quitUser(user, "Quit: " + message[0]);
}
