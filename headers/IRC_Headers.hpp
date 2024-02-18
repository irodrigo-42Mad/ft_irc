/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Headers.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:47:03 by irodrigo          #+#    #+#             */
/*   Updated: 2024/02/18 19:09:12 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <utility>

// private functions, structures and constants by function
# include "IRC_Colors.hpp"
# include "IRC_Errors.hpp"
# include "IRC_Utils.hpp"

#endif
