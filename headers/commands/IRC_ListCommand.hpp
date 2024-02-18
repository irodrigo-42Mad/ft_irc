/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_ListCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:04:09 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:04:10 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_LISTCOMMAND_HPP
# define IRC_LISTCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_ListCommand : IRC_ACommand {
	IRC_ListCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
