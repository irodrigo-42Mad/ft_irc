/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_PingCommand.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:16:06 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 21:11:49 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/IRC_PingCommand.hpp"
#include "IRC_Server.hpp"

IRC_PingCommand::IRC_PingCommand()
	: IRC_ACommand("PING", 1, UNREGISTERED)
{}

void IRC_PingCommand::execute(IRC_Message& message)
{
		IRC_Server &server = message.getServer();
		IRC_User &user = message.getUser();
		std::string data = message[0];

		server.pong(&user, data);
}
