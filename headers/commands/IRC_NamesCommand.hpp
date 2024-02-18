/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_NamesCommand.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:04:29 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:04:31 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_NAMESCOMMAND_HPP
# define IRC_NAMESCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_NamesCommand : IRC_ACommand {
	IRC_NamesCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
