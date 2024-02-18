/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_ModeCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:04:17 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 21:19:35 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_MODECOMMAND_HPP
# define IRC_MODECOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_ModeCommand : IRC_ACommand {
	IRC_ModeCommand();

	void execute(IRC_Message& /*message*/);

private:
	void _executeChannel(IRC_Message& );
};

#endif
