/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_ListCommand.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:12:04 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:12:05 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/IRC_ListCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Errors.hpp"

IRC_ListCommand::IRC_ListCommand()
	: IRC_ACommand("LIST", 0, REGISTERED)
{}

void IRC_ListCommand::execute(IRC_Message& message) {
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();

	if (message.empty())
		server.channelList(user);
	else
	{
		std::cout << message.size() << std::endl;
		for (size_t i = 0; i < message.size(); ++i)
		{
			std::cout << message[i] << std::endl;
			server.channelListByName(user, message[i]);
		}
		user.reply(server, RPL_LISTEND(user.getName()));
	}
}
