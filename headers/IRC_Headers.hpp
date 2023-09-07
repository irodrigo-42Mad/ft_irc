/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Headers.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:15:05 by icastell          #+#    #+#             */
/*   Updated: 2023/09/07 19:35:39 by icastell         ###   ########.fr       */
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
# include <cerrno>
# include <ctime>

// common sockect structures and functions
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <poll.h>

// common STL structures needed
# include <vector>
# include <map>

// private functions, structures and constants by function
# include "IRC_Structs.hpp"
# include "IRC_Constants.hpp"
# include "IRC_Colors.hpp"

#endif