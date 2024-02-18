/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Message.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:11:34 by icastell          #+#    #+#             */
/*   Updated: 2024/02/18 19:09:55 by pcosta-j         ###   ########.fr       */
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
	typedef std::vector<std::string>		paramsType;
	typedef paramsType::iterator			paramsIterator;
	typedef paramsType::const_iterator		paramsConstIterator;

	IRC_Message(IRC_User* sourceUser, IRC_Server* server, const std::string& data);

	const std::string& 		operator[](int pos);
	const std::string&		getCmd() const;
	IRC_User& 				getUser();
	const paramsType&		getParams() const;
	IRC_Server& 			getServer();  
	size_t					size() const;
	bool					empty() const;
	
private:
	std::string				_cmd;
	IRC_User&				_user;
	paramsType				_params;
	IRC_Server&				_server;
	
	void					_processCommand(std::string command);
	std::string				_lTrim(std::string data);
};

#endif
