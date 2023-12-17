/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Message.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:11:34 by icastell          #+#    #+#             */
/*   Updated: 2023/12/17 17:31:00 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC_Message.hpp"
#include "IRC_User.hpp"
#include "IRC_Server.hpp"

#include <iostream>
#include <sstream>

void print_command(IRC_Message* msg) {
    std::vector<std::string> params = msg->getParams();

    std::cout << "cmd = " << msg->getCmd();
    std::cout << "| params_count = " << msg->getParamSize();
    std::cout << "| server_address = " << &msg->getServer();
    std::cout << "| source_address = " << &msg->getSourceUser() << std::endl;
    
    for (size_t i = 0; i < params.size(); ++i)
        std::cout << "param[" << i << "] = " << params[i] << std::endl;
    
    std::cout << std::endl;
}

IRC_Message::IRC_Message(IRC_User* sourceUser, IRC_Server* server, const std::string& data)
		: _sourceUser(*sourceUser)
		, _server(*server)
{
    this->_processCommand(data);
    print_command(this);
	//aquí el parseo del mensaje del cliente
}

void IRC_Message::_processCommand(std::string data)
{
    // extraer mensaje completo si lo hubiera de user, instanciar message, procesar comando
    std::string buffer;
    size_t position;
    // search for prefix and erase
    position = data.find(':');
    // delete prefix from command to correct parse
    if (position != std::string::npos)
        data.erase(0, position + 1);
    //string trimmer for take correct command
    data = this->_lTrim(data);
    // take command
    std::stringstream myss(data);
    std::string element;
    std::getline(myss, element);
    element = this->_lTrim(element);
    this->_cmd = element.substr(0, element.find(" "));
    data = element.substr(this->_cmd.length() + 1, element.length());

    // take params
    std::stringstream line(data);
    std::string myparam;
    while (line >> myparam)
    {
        this->_params.push_back(_lTrim(myparam));
    }
}

/*void IRC_Message::_processCommand(std::string data)
{
	// extraer mensaje completo si lo hubiera de user, instanciar message, procesar comando
	std::string buffer; 
    
    // search for prefix and erase
    size_t position;
    position = data.find(':');
    if (position != std::string::npos)
    {
        buffer = data.substr(0,position + 1);
        data = buffer;
    }
    // get command to message class
    position = data.find(" ");
    if (position != std::string::npos)
    {
		this->_cmd = data.substr(0, position);
        buffer = data.substr(position + 1);
        data = buffer;
    }

    if (data.find(" ") != std::string::npos)
    {
        // take params in message struct from buffer data
        int num = 0;
        position = data.find(" ");
        while  (position != std::string::npos)
        {
            this->_params.push_back(data.substr(0, position));
            buffer = data.substr(position + 1);
            data = buffer;
            ++num;
            position = data.find(" ");
//            std::cout << "'" << buffer << "'" << std::endl;
        }
    }

    if (this->_cmd == "")
        this->_cmd = data;
    else
        this->_params.push_back(data.substr(0));
}*/

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

void IRC_Message::reply(const std::string& reply)
{
    this->_sourceUser.sendMessage(":" + this->_server.getServerName() + " " + reply);
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
