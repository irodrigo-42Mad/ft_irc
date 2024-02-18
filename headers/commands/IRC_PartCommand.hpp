/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_PartCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:04:57 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:04:58 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_PARTCOMMAND_HPP
# define IRC_PARTCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_PartCommand : IRC_ACommand {
	IRC_PartCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
