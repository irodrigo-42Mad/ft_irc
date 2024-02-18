/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_ACommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:06:26 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:06:28 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_ACOMMAND_HPP
# define IRC_ACOMMAND_HPP

# include "IRC_Message.hpp"

enum IRC_AccessLevel {
	UNREGISTERED,
	PENDING,
	REGISTERED,
	OPERATOR
};

// IRC Commands

// USER LEVEL FLAG: 0 UNREGISTERED, 1 PENDING 2 REGISTERED, 3 OPERATOR

// HAY QUE MODIFICAR LOS VALORES DE ESTO
//void				cmdPass(IRC_Message& message); // 1 UNREGISTERED
//void				cmdNick(IRC_Message& message); // 1 UNREGISTERED
//void				cmdUser(IRC_Message& message); // 5 UNREGISTERED
//void				cmdQuit(IRC_Message& message); // 1 UNREGISTERED
			
//void				cmdPing(IRC_Message& message); // 1 REGISTERED
//void				cmdPong(IRC_Message& message); // 1 REGISTERED
																									
//void				cmdPrivMsg(IRC_Message& message); // 2 REGISTERED
//void				cmdNotice(IRC_Message& message);  // 2 REGISTERED

//void				cmdOper(IRC_Message& message); // 2 OPERATOR (user)
//void				cmdKill(IRC_Message& message); // 2 OPERATOR
//void				cmdDie(IRC_Message& message);  // 1 OPERATOR

//void				cmdJoin(IRC_Message& message);
//void				cmdList(IRC_Message& message);  // 0 REGISTERED
//void				cmdNames(IRC_Message& message); // 1 REGISTERED
//void				cmdPart(IRC_Message& message);  // 2 REGISTERED
//void				cmdKick(IRC_Message& message);  // 3 REGISTERED
//void				cmdTopic(IRC_Message& message); // 2 REGISTERED

//struct IRC_Server;

struct IRC_ACommand
{
		std::string	cmd;
		size_t		params;
		int			access;

		IRC_ACommand(const std::string& cmd, int params, IRC_AccessLevel access)
			: cmd(cmd)
		  	, params(params)
			, access(access)
		{}

		virtual ~IRC_ACommand() {}
		virtual void execute(IRC_Message& message) = 0;

	private:
		IRC_ACommand();
		IRC_ACommand(const IRC_ACommand& src);
		IRC_ACommand& operator=(const IRC_ACommand& rhs);
};

#endif
