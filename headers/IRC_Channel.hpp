/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Channel.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:04:15 by irodrigo          #+#    #+#             */
/*   Updated: 2023/12/04 16:35:50 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRC_CHANNEL_HPP
#define IRC_CHANNEL_HPP

#include "IRC_Headers.hpp"
#include "IRC_Users.hpp"
#include "IRC_Structs.hpp"

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
		_usersInChannelMap  _userMap;
		
	public:
		IRC_Channel(IRC_Server &server, IRC_Users* creator, std::string const &name);
		~IRC_Channel();
        std::string	getName();
        std::string	getTopic();
		void	setName(std::string name);
        void	setTopic(std::string newTopic);
		bool	addUser(IRC_Users *userToAdd);
        void    deleteUser(IRC_Users *userToDelete);
        bool    isUserInChannel(IRC_Users *actualUser);
        bool    isUserOnline(IRC_Users *actualUser);
        void    sendMessage(std::string const &str, int userFd);
        void    channelBroadcast(std::string const &str, IRC_Users *user);
};
#endif
