/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:07:19 by icastell          #+#    #+#             */
/*   Updated: 2023/10/03 13:55:15 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

# include "IRC_Headers.hpp"

class IRC_Client;

class IRC_Channel;

class IRC_Messages;

class IRC_Server
{
private:
	std::string	_port;
	std::string	_password;
	std::string _servName;

	
	
	IRC_Server();

	
	
	
	User		_UserMap;
	Command		_CommandMap;
	IRC_Channel	_ChannelMap;


public:
	enum State
	{
		ALIVE,
		RESTART,
		DIE
	};
	
	enum MyType
	{
		PING,
		PONG
	};

	IRC_Server(const std::string &port, const std::string &password);
	IRC_Server (IRC_Server const &cpy);
	IRC_Server &operator = (IRC_Server const &cpy);
	~IRC_Server();
	
	//getters y setters
	enum State 			getState();
	void 				setState(enum State myst);
	
	// general irc functions
	void				launch();

	// Server Display
	void				handleMessage(int fd);
	void				displayClient();

	// Server Display
	void				newClient();
	void				eraseClient(int fd);
	void				eraseClientChannel(IRC_Client &cl);
	void				clientDisconnect(int fd);

	bool				is_in_channel(IRC_Client &cl);
	bool				is_oper_in_channel(IRC_Client &cl);

	// Server command implementation
		// IRC Commands
	void				cmdPass(IRC_Messages &message);
	void				cmdNick(IRC_Messages &message);
	void				cmdUser(IRC_Messages &message);
	void				cmdPrivMsg(IRC_Messages &message);
	void				cmdPingPong(IRC_Messages &message, MyType tp);
	void				cmdJoin(IRC_Messages &message);
	void				cmdOper(IRC_Messages &message);
	void				cmdQuit(IRC_Messages &message);
	void				cmdList(IRC_Messages &message);
	void				cmdNames(IRC_Messages &message);
	void				cmdPart(IRC_Messages &message);
	void				cmdKick(IRC_Messages &message);
	void				cmdKill(IRC_Messages &message);
	void				cmdDie(IRC_Messages &message);
	// probably not necesary
	void				cmdTopic(IRC_Messages &message);
	void				cmdNotice (IRC_Messages &message);
	void				cmdMode (IRC_Messages &message);

};
		


		// two functions in one threatment
		//void			cmdPing(Message &message);
		//void			cmd_pong(Message &message);
		// lo mismo no hace falta.
		//void			cmd_names_inChannel(Message &message, std::string channelName);



#endif
