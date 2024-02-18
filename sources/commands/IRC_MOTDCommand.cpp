/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_MOTDCommand.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:13:02 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:13:03 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/IRC_MOTDCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Errors.hpp"

IRC_MOTDCommand::IRC_MOTDCommand()
    : IRC_ACommand("MOTD", 0, REGISTERED)
{}

void IRC_MOTDCommand::execute(IRC_Message& message)
{
		IRC_Server& server = message.getServer();
		IRC_User& user = message.getUser();

    server.sendMOTDMsg(user);
}
