/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_MOTDCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:04:23 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:04:24 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_MOTDCOMMAND_HPP
# define IRC_MOTDCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_MOTDCommand : IRC_ACommand {
	IRC_MOTDCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
