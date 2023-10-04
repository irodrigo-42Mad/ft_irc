/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:59:21 by irodrigo          #+#    #+#             */
/*   Updated: 2023/10/03 13:00:06 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/IRC_Server.hpp"

// common constructor and destructor of class Server
IRC_Server::IRC_Server(const std::string &port, const std::string &password) : _port(port), _servName("ircserv")
{
	//debemos asignar el puerto y el pass para poder funcionar con el resto de elementos.
	this->_password = password;

	
}



IRC_Server::~IRC_Server()
{}

// Public functions in server
void IRC_Server::launch()
{

}

enum State	IRC_Server::getState()
{

}

void 	IRC_Server::setState(State myst)
{


}