/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_PingCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:05:10 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:05:12 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_PINGCOMMAND_HPP
# define IRC_PINGCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_PingCommand : IRC_ACommand {
	IRC_PingCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
