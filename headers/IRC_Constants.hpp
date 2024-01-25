/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Constants.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:22:13 by icastell          #+#    #+#             */
/*   Updated: 2024/01/25 14:08:13 by irodrigo         ###   ########.fr       */
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
# define SPECIALCHAR 	"-_[]\\`^{|}"	//must try to control this characters in structures.

# define MAXNICKLENGTH	9

// const to control messages
# define FIRST			1				//used to set first message send to client
# define NORMALMSG		0				//normal messages to clients

# define PINGTOUT		9				//timeout over ping events
# define REGTOUT		20				//max timeout for register one user
# define IDLETOUT		15				//general timeout tick control
# define PONG_STR		"Numantinos"	//Cadena de texto para pong

# endif
