/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_WelcomeCommand.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:05:44 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:05:45 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_WELCOMECOMMAND_HPP
# define IRC_WELCOMECOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_WelcomeCommand : IRC_ACommand {
	IRC_WelcomeCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
