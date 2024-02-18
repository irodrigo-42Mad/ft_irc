/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_UserCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:05:37 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 21:19:49 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_USERCOMMAND_HPP
# define IRC_USERCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_UserCommand : IRC_ACommand {
	IRC_UserCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
