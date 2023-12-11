/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Messages.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:11:34 by icastell          #+#    #+#             */
/*   Updated: 2023/10/03 13:52:37 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC_Message.hpp"

#include <iostream>

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

const std::string& IRC_Message::cmd() const {
	return this->_cmd;
}

size_t IRC_Message::size() const {
	return this->_params.size();
}

const std::string& IRC_Message::operator[](int pos) {
	return this->_params[pos];
}

const IRC_User& IRC_Message::sourceUser() const {
	return this->_sourceUser;
}

IRC_Server& IRC_Message::server() {
	return this->_server;
}
