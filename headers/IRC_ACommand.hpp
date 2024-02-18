/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_ACommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:06:26 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 21:16:57 by pcosta-j         ###   ########.fr       */
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
