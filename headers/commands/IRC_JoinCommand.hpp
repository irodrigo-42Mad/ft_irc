/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_JoinCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:03:42 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:03:44 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_JOINCOMMAND_HPP
# define IRC_JOINCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_JoinCommand : IRC_ACommand {
	IRC_JoinCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
