/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Message.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:11:34 by icastell          #+#    #+#             */
/*   Updated: 2023/12/14 11:44:38 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_MESSAGE_HPP
#define IRC_MESSAGE_HPP

# include <string>
# include <vector>

struct IRC_User;
struct IRC_Server;

struct IRC_Message
{
	IRC_Message(IRC_User* sourceUser, IRC_Server* server, const std::string& data);
	const std::string&				getCmd() const;
	const IRC_User& 				getSourceUser() const;
	const std::vector<std::string>&	getParams() const;
	size_t							getParamSize() const;
	IRC_Server& 					getServer();  
	const std::string& operator[](int pos);
private:
	std::string					_cmd;
	IRC_User&					_sourceUser;
	std::vector<std::string>	_params;
	IRC_Server&					_server;
	
	void _processCommand(std::string command);
};

#endif
