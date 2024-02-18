/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_KickCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:03:54 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:03:56 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_KICKCOMMAND_HPP
# define IRC_KICKCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_KickCommand : IRC_ACommand {
	IRC_KickCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
