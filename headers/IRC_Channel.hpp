/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Channel.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:04:15 by irodrigo          #+#    #+#             */
/*   Updated: 2023/10/03 11:12:46 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRC_CHANNEL_HPP
#define IRC_CHANNEL_HPP

#include "IRC_Headers.hpp"

class IRC_Channel{
	private:
		IRC_Server& _Server;
		std::string _ChannelName;

		
	public:
		IRC_Channel(IRC_Server& server, IRC_Users* creator, std::string name);
		~IRC_Channel();
};
#endif
