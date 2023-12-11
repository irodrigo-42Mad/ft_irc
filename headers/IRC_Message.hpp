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

#ifndef IRC_MESSAGE_HPP
#define IRC_MESSAGE_HPP

# include <string>
# include <vector>

struct IRC_User;
struct IRC_Server;

struct IRC_Message
{
	IRC_Message(IRC_User* sourceUser, IRC_Server* server, const std::string& data);
	const std::string& cmd() const;

	size_t size() const;

	const std::string& operator[](int pos);

	const IRC_User& sourceUser() const;

	IRC_Server& server();

private:
	std::string								_cmd;
	IRC_User&									_sourceUser;
	std::vector<std::string>	_params;
	IRC_Server&								_server;

};

#endif
