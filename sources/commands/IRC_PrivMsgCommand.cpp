/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_PrivMsgCommand.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:17:12 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:17:14 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "commands/IRC_PrivMsgCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_User.hpp"
# include "IRC_Errors.hpp"
# include "tools.hpp"

IRC_PrivMsgCommand::IRC_PrivMsgCommand()
	: IRC_ACommand("PRIVMSG", 2, REGISTERED)
{}

void IRC_PrivMsgCommand::execute(IRC_Message& message) {
	std::string target = message[0];
	std::string textToBeSent = message[1];
	IRC_User& user = message.getUser();
	IRC_Server& server = message.getServer();

	if (textToBeSent.empty())
	{
		user.reply(server, ERR_NOTEXTTOSEND(user.getName()));
		return ;
	}
	
	// Code for finding channel or user instances 
	if (isChannel(target))
	{
		IRC_Channel *targetChannel = server.findChannelByName(target);

		if (!targetChannel)
		{
			user.reply(server, ERR_NOSUCHCHANNEL(user.getName(), target));
			return ;
		}	
		if (!targetChannel->isOperator(user) && user.getAccess() != OPERATOR)
		{
			if (targetChannel->isBanned(user))
			{
				user.reply(server, ERR_CANNOTSENDTOCHAN(user.getName(), targetChannel->getName(), "+b"));
				return ;
			}
			else if (targetChannel->hasModerate())
			{
				user.reply(server, ERR_CANNOTSENDTOCHAN(user.getName(), targetChannel->getName(), "+m"));
				return ;
			}
		}
		if (!targetChannel->hasUser(user) && targetChannel->hasNoExternalMessages())
		{
			user.reply(server, ERR_CANNOTSENDTOCHAN(user.getName(), targetChannel->getName(), "+n"));
			return ;
		}
		targetChannel->sendExcept(&user, user, "PRIVMSG " + targetChannel->getName(), textToBeSent);
	}
	else
	{
		IRC_User *targetUser = server.findUserByName(target);

		if (!targetUser)
		{
			user.reply(server, ERR_NOSUCHNICK(user.getName(), target));
			return ;
		}
		targetUser->send(user, "PRIVMSG " + targetUser->getName(), textToBeSent);
	}
}
