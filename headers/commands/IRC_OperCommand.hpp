/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_OperCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:04:52 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:04:53 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_OPERCOMMAND_HPP
# define IRC_OPERCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_OperCommand : IRC_ACommand {
	IRC_OperCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
