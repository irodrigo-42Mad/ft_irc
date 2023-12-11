/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Channel.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:04:15 by irodrigo          #+#    #+#             */
/*   Updated: 2023/10/15 19:13:19 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRC_CHANNEL_HPP
#define IRC_CHANNEL_HPP

#include "IRC_Headers.hpp"
#include "IRC_Users.hpp"

class IRC_Server;

class IRC_Channel
{
	private:
		IRC_Server& _server;
		std::string _channelName;
		IRC_Users*	_creator;
		std::string _topic;
    	std::string _key;
    	int			_limit;
		
	public:
		IRC_Channel(IRC_Server &server, IRC_Users* creator, std::string const &name);
		~IRC_Channel();
		bool	addUser(IRC_Users *newUser);
		void	deleteUser(IRC_Users *user);
		void	sendMessage(std::string const &str, int userFd);
};
#endif
