/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_OperCommand.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:15:38 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:15:40 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/IRC_OperCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_User.hpp"

IRC_OperCommand::IRC_OperCommand()
	: IRC_ACommand("OPER", 2, REGISTERED)
{}

void IRC_OperCommand::execute(IRC_Message& message)
{
	IRC_User& user = message.getUser();
	IRC_Server& server = message.getServer();
	const std::string& username = message[0];
	const std::string& password = message[1];

	if (username == OPERUSER && password == OPERPASS && user.getAccess() != OPERATOR)
	{
		user.reply(server, RPL_YOUAREOPER(user.getName()));
		user.setAccess(OPERATOR);
	}
}
