/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_PrivMsgCommand.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:05:22 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:05:23 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_PRIVMSGCOMMAND_HPP
# define IRC_PRIVMSGCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_PrivMsgCommand : IRC_ACommand {
	IRC_PrivMsgCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
