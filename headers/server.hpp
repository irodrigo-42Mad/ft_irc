/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:07:19 by icastell          #+#    #+#             */
/*   Updated: 2023/09/09 14:43:58 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef SERVER_HPP
#define SERVER_HPP

# include "IRC_Headers.hpp"

class server
{
private:
	std::string	_port;
	std::string	_password;
	server();
public:
	server(const std::string &port, const std::string &password);
	server (server const &cpy);
	server &operator = (server const &cpy);
	~server();
	//getters y setters
};



#endif
