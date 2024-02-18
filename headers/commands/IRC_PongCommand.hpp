/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_PongCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:05:16 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:05:18 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_PONGCOMMAND_HPP
# define IRC_PONGCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_PongCommand : IRC_ACommand {
	IRC_PongCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
