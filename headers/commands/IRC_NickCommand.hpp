/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_NickCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:04:36 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:04:38 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_NICKCOMMAND_HPP
# define IRC_NICKCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_NickCommand : IRC_ACommand {
	IRC_NickCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
