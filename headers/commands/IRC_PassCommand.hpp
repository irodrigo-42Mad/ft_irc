/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_PassCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:05:02 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:05:03 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_PASSCOMMAND_HPP
# define IRC_PASSCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_PassCommand : IRC_ACommand {
	IRC_PassCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
