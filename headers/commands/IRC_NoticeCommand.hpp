/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_NoticeCommand.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:04:43 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:04:45 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_NOTICECOMMAND_HPP
# define IRC_NOTICECOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_NoticeCommand : IRC_ACommand {
	IRC_NoticeCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
