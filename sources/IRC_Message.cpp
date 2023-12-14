/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Message.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:11:34 by icastell          #+#    #+#             */
/*   Updated: 2023/12/14 13:01:22 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC_Message.hpp"

#include <iostream>
#include <sstream>

IRC_Message::IRC_Message(IRC_User* sourceUser, IRC_Server* server, const std::string& data)
		: _sourceUser(*sourceUser)
		, _server(*server)
{
	(void)data;
	size_t position = data.find(" ");

	if (position != std::string::npos)
		this->_cmd = data.substr(0, position);

	//aquí el parseo del mensaje del cliente
}

void IRC_Message::_processCommand(std::string data)
{
	// extraer mensaje completo si lo hubiera de user, instanciar message, procesar comando
	std::string buffer; 
    //buffer = user->getBuffer();

    // search for prefix and erase
    size_t position = data.find(':');
    std::string micadena = buffer.substr(position);
    std::istringstream bufferStream(micadena);
    bufferStream >> this->_cmd;
    // take params in command line
    const int MAX_PARAMETROS = 15;
    std::string parametros[MAX_PARAMETROS];
    int i = 0;
    while (bufferStream >> this->_params[i] 
			&& i < MAX_PARAMETROS) {
        ++i;
    }

    if (this->_cmd.empty()) {
        std::cerr << "Error: El comando no puede estar vacío." << std::endl;
        return ; // Código de error
    }
}

const std::vector<std::string>&	IRC_Message::getParams() const
{
    return (this->_params);
}

const std::string& IRC_Message::getCmd() const
{
	return (this->_cmd);
}

size_t IRC_Message::getParamSize() const
{
	return (this->_params.size());
}

IRC_User& IRC_Message::getSourceUser()
{
	return (this->_sourceUser);
}

IRC_Server& IRC_Message::getServer()
{
	return (this->_server);
}

const std::string& IRC_Message::operator[](int pos)
{
	return (this->_params[pos]);
}
