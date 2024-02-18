/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_InviteCommand.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:03:33 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:03:36 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_INVITECOMMAND_HPP
# define IRC_INVITECOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_InviteCommand : IRC_ACommand {
	IRC_InviteCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
