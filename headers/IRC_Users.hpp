/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Users.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:05:44 by irodrigo          #+#    #+#             */
/*   Updated: 2023/10/05 10:34:38 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRC_USERS_HPP
#define IRC_USERS_HPP

#include "IRC_Headers.hpp"

class IRC_Server;

class IRC_Users{
	private:

	public:
		IRC_Users(int fd, IRC_Server& server);
		~IRC_Users();

};

#endif
