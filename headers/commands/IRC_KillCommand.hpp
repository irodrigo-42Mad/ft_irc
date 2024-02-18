/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_KillCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:04:01 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:04:03 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_KILLCOMMAND_HPP
# define IRC_KILLCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_KillCommand : IRC_ACommand {
	IRC_KillCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
