/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_TopicCommand.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:05:32 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:05:34 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_TOPICCOMMAND_HPP
# define IRC_TOPICCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_TopicCommand : IRC_ACommand {
	IRC_TopicCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
