/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Headers.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:47:03 by irodrigo          #+#    #+#             */
/*   Updated: 2023/12/03 19:38:59 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRC_HEADERS_HPP
#define IRC_HEADERS_HPP

// common system headers
# include <cstring>
# include <cstdlib>
# include <iostream>
# include <unistd.h>
# include <sstream>
# include <string>
# include <ctime>
# include <fstream>

// common sockect structures and functions
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/poll.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>

// common STL structures needed
# include <vector>
# include <map>

// private functions, structures and constants by function
# include "IRC_Colors.hpp"
// # include "IRC_Messages.hpp"
# include "IRC_Errors.hpp"
// # include "IRC_Constants.hpp"
// # include "IRC_Structs.hpp"
# include "IRC_Utils.hpp"
// # include "IRC_Users.hpp"
// # include "IRC_Channel.hpp"
//# include "IRC_Server.hpp"

#endif
