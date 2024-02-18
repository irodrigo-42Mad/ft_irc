/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_DieCommand.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:03:08 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:03:12 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_DIECOMMAND_HPP
# define IRC_DIECOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_DieCommand : IRC_ACommand {
	IRC_DieCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
