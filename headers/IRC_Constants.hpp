/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Constants.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:22:13 by icastell          #+#    #+#             */
/*   Updated: 2024/02/09 13:43:41 by irodrigo         ###   ########.fr       */
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
# define IRC_VERSION	"1.0.0"			//first version of ft42irc server

// special character
# define SPECIALCHAR 	"-_[]\\`^{|}"	//must try to control this characters in structures.

// const to control messages
# define FIRST			1				//used to set first message send to client
# define NORMALMSG		0				//normal messages to clients

# define PINGTOUT		9000				//timeout over ping events
# define REGTOUT		9000				//max timeout for register one user
# define IDLETOUT		9000				//general timeout tick control
//# define PONG_STR		"Numantinos"	//Cadena de texto para pong

# define OPERUSER			"test"
# define OPERPASS			"1234"

# define CHANLIMIT		5
# define CHANNELLEN		15	
# define CHANTYPES		"#"
# define KEYLEN				15
# define NICKLEN			9
# define MAXTARGETS		1
# define NAMELEN			128
# define NETWORK			"ircserv"
# define KICKLEN			128
# define TOPICLEN			200
# define USERLEN			10
# define LINELEN			512
# define MODES				6

#endif
