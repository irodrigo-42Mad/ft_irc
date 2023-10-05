/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Constants.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:22:13 by icastell          #+#    #+#             */
/*   Updated: 2023/10/05 11:15:16 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRC_CONSTANTS_HPP
#define IRC_CONSTANTS_HPP

// common socket constants
# define SERV_ADDR 		"0.0.0.0"		//Local host
# define SERV_PORT 		"4242"			//Port we are listening on
# define BUF_SIZE 		100				//Socket receive buffer size
# define BACKLOG 		5				//Number of incoming connections that can be queued for acceptance  ¡¡OJO CON ESTO!!!
# define MAX_CLIENTS	10				//Max number of clients accept by server

// version
# define _version 		"1.0.0"			//first version of ft42irc server

// special character
# define SPECIALCHAR 	"-[]\\`^{}"		//must try to control this characters in structures.

# endif
