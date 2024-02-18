/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_QuitCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:05:27 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:05:28 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_QUITCOMMAND_HPP
# define IRC_QUITCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_QuitCommand : IRC_ACommand {
	IRC_QuitCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
