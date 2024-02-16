/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Message.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:11:34 by icastell          #+#    #+#             */
/*   Updated: 2024/02/16 14:14:13 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC_Message.hpp"
#include "IRC_User.hpp"
#include "IRC_Server.hpp"

#include <iostream>
#include <sstream>

void print_command(IRC_Message* msg)
{
	IRC_Message::paramsType params = msg->getParams();

	std::cout << "cmd = " << msg->getCmd() << std::endl;
	std::cout << "| params_count = " << msg->size();
	std::cout << "| server_address = " << &msg->getServer();
	std::cout << "| source_address = " << &msg->getUser() << std::endl;
    
	for (size_t i = 0; i < params.size(); ++i)
		std::cout << "param[" << i << "] = " << params[i] << std::endl;
    
	std::cout << std::endl;
}

IRC_Message::IRC_Message(IRC_User* user, IRC_Server* server, const std::string& data)
	: _user(*user)
	, _server(*server)
{
	this->_processCommand(data);
	//print_command(this);
	//aquí el parseo del mensaje del cliente
}

void IRC_Message::_processCommand(std::string buffer)
{
	size_t position;

    /*
        :prefix comando parámetros -> FORMATO MENSAJE IRC
        
        :prefix       comando         parámetros -> FORMATO ERRONEO MENSAJE IRC: solo un espacio entre
                                                    partes del comando según estándar 2812 (pag. 5)
    */
   
    // search for prefix
    position = buffer.find(':');
    // delete prefix from command to correct parse
    if (position == 0)
    {
        position = buffer.find(" ");
        if (position == std::string::npos)
            return ;  //error de comando
        position = buffer.find_first_not_of(' ', position);
        buffer.erase(0, position);
    }
    // take command
    
    if ((position = buffer.find_first_not_of(' ', 0)) > 0)
        buffer.erase(0, position);
    position = buffer.find(" ");
    if (position != std::string::npos)
    {
        this->_cmd = buffer.substr(0, position);
        position = buffer.find_first_not_of(' ', position);
        buffer.erase(0, position);
        // get params
        std::stringstream line(buffer);
        std::string myparam;
        while (line >> myparam && this->_params.size() < 15)
        {
            position = myparam.find(":");
            if (position != std::string::npos)
            {
                buffer.erase(0, 1);
                this->_params.push_back(buffer.erase(buffer.length(), 2));
                break ;
            }
            this->_params.push_back(myparam);
            position = buffer.find(" ");
            position = buffer.find_first_not_of(' ', position);
            buffer.erase(0, position);
        }
        //std::cout << "num params: " << this->_params.size() << std::endl;
    }
    else
        this->_cmd = buffer.erase(buffer.length(), 2);
}

const IRC_Message::paramsType&	IRC_Message::getParams() const
{
    return (this->_params);
}

const std::string& IRC_Message::getCmd() const
{
		return (this->_cmd);
}

size_t IRC_Message::size() const
{
		return (this->_params.size());
}

IRC_User& IRC_Message::getUser()
{
		return (this->_user);
}

IRC_Server& IRC_Message::getServer()
{
	return (this->_server);
}

const std::string& IRC_Message::operator[](int pos)
{
	return (this->_params[pos]);
}

bool IRC_Message::empty() const
{
	return (this->_params.empty());
}

std::string IRC_Message::_lTrim(std::string data)
{
    std::string SPACE = "\t\f\v";
    size_t position;
    std::string buffer;
    
    position = data.find_first_not_of(SPACE);
    if (position > 0 && position != std::string::npos)
        data.erase(0,position);
    position = data.find_last_not_of(SPACE);
    //int cmdlen = data.length();
    if (position != std::string::npos)
    {
        buffer = data.substr(0, position + 1);
        data = buffer;
    }
    return data;
}
