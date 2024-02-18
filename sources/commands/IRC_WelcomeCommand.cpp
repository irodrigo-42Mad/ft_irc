/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_WelcomeCommand.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:18:53 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:18:55 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "commands/IRC_WelcomeCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Errors.hpp"

IRC_WelcomeCommand::IRC_WelcomeCommand()
	: IRC_ACommand("WELCOME", 0, REGISTERED)
{}

void IRC_WelcomeCommand::execute(IRC_Message& message) {
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();

	server.sendWelcomeMsg(user);

}
