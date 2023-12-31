/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Errors.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:38:07 by icastell          #+#    #+#             */
/*   Updated: 2024/01/09 13:55:41 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_ERRORS_HPP
# define IRC_ERRORS_HPP

# include "IRC_Headers.hpp"

// system error constants
# define ERR_COMPLETELY_SCREWED 1
# define ERR_STILL_SAVED 2
# define ERR_CURA_SANA 3

// system error definitions
int	ft_err_msg(std::string const &msg, int err_lvl, int err_n);

// replies
# define RPL_YOURHOST(servername, version)				"002 Your host is " + servername + ", running version " + version
# define RPL_CREATED(date)								"003 This server was created " + date
# define RPL_MYINFO(servername, version)				"004 " + servername + " " + version + " itkol"
# define RPL_WELCOME(nickname, mask)            		"001 " + nickname + " :Welcome to the Internet Relay Network " + mask
# define RPL_LIST(nickname, channel, mode, topic)		"322 " + nickname + " " + channel + " " + mode + " :" + topic
# define RPL_LISTEND(nickname)							"323 " + nickname + " :End of LIST"
# define RPL_NOTOPIC(nickname, channel)					"331 " + nickname + " " + channel + " :No topic is set"
# define RPL_TOPIC(nickname, channel, topic)			"332 " + nickname + " " + channel + " :" + topic
# define RPL_NAMREPLY(nickname, channel, names)			"353 " + nickname + " = " + channel + " :" + names
# define RPL_ENDOFNAMES(nickname, channel)				"366 " + nickname + " " + channel + " :End of NAMES list"
# define RPL_MOTD(nickmame, text)						"372 " + nickmame + " :" + text
# define RPL_MOTDSTART(nickname, server)				"375 " + nickname + " :- " + server + " Message of the day - "
# define RPL_ENDOFMOTD(nickname)						"376 " + nickname + " :End of MOTD command"
# define RPL_YOUAREOPER(nickname)						"381 " + nickname + " :You are now an IRC operator"

// error replies
# define ERR_NOSUCHNICK(nickname)                		"401 " + nickname + " :No such nick/channel"
# define ERR_NOSUCHSERVER(nickname, server)				"402 " + nickname + " " + server + " :No such server"
# define ERR_NOSUCHCHANNEL(nickname, channel)			"403 " + nickname + " " + channel + " :No such channel"
# define ERR_CANNOTSENDTOCHAN(nickname, channel)		"404 " + nickname + " " + channel + " :Cannot send to channel"
# define ERR_TOOMANYCHANNELS(nickname, channel)			"405 " + nickname + " " + channel + " :You have joined too many channels"
# define ERR_NORECIPIENT(nickname, command)				"411 " + nickname + " :No recipient given (" + command + ")"
# define ERR_NOTEXTTOSEND(nickname)						"412 " + nickname + " :No text to send"
# define ERR_UNKNOWNCOMMAND(nickname, command)			"421 " + nickname + " " + command + " :Unknown command"
# define ERR_NONICKNAMEGIVEN(nickname)					"431 " + nickname + " :No nickname given"
# define ERR_ERRONEOUSNICKNAME(nickname, err_nickname)	"432 " + nickname + " " + err_nickname + " :Erroneous nickname"
# define ERR_NICKNAMEINUSE(nickname)					"433 " + nickname + " :Nickname is already in use"
# define ERR_USERNOTINCHANNEL(nickname, channel)		"441 " + nickname + " " + channel + " :They aren't on that channel"
# define ERR_NOTONCHANNEL(nickname, channel)			"442 " + nickname + channel + " :You're not on that channel"
# define ERR_NEEDMOREPARAMS(nickname, command)			"461 " + nickname + " " + command + " :Not enough parameters"
# define ERR_ALREADYREGISTRED(nickname)			        "462 " + nickname + " :Unauthorized command (already registered)"	//ToDo: repasar esto
# define ERR_PASSWDMISMATCH(nickname, source)			"464 " + nickname + " :Password incorrect"
# define ERR_CHANNELISFULL(nickname, channel)           "471 " + nickname + " " + channel + " :Cannot join channel (+l)"	//ToDo: ídem que el siguiente
# define ERR_INVITEONLYCHAN(nickname, channel)			"473 " + nickname + " " + channel + " :Cannot join channel (+i)"	//ToDo: repasar esto porque creo que tiene modos
# define ERR_BANNEDFROMCHAN(nickname, channel)   		"474 " + nickname + " " + channel + " :Cannot join channel (+b)"	//ToDo: ídem
# define ERR_BADCHANNELKEY(nickname, channel)           "475 " + nickname + " " + channel + " :Cannot join channel (+k)"	//ToDo: ídem
# define ERR_BADCHANMASK(nickname, channel)				"476 " + nickname + " " + channel + " :Bad Channel Mask"			//ToDo: repasar
# define ERR_NOPRIVILEGES(nickname)						"481 " + nickname + " :Permission Denied- You're not an IRC operator"
# define ERR_CHANOPRIVSNEEDED(nickname, channel)		"482 " + nickname + " " + channel + " :You're not channel operator"
# define ERR_NOOPERHOST(nickname)						"491 " + nickname + " :No O-lines for your host"
# define ERR_PONG(mask, message)						"ERROR: Closing link: (" + mask + ") " + message // unregistered [Registration timeout] o bien registered [Ping timeout: 120 seconds]
// other
# define RPL_PRIVMSG(mask, name, message)				mask + " PRIVMSG " + name + " :" + message
# define RPL_NOTICE(mask, name, message)				mask + " NOTICE " + name + " :" + message


// #define ERR_FORBIDDEN()              					"403  :Cannot ban an operator"
// #define ERR_ALREADYINVITED(source, target, channel)     "472 " + source + " :User " + target + " is already invited to channel " + channel
// #define ERR_ALREADYONCHANNEL(source, channel)           "475 " + source + " :You are already on channel " + channel
// 
// #define ERR_NOPRIVILEGES(source, channel)           	"481 " + source + " " + channel + " :Permission Denied: Insufficient privileges"
// 
// 
// #define RPL_INVITELIST(source, channel)                 "332 " + source + " : You are now on the waiting list for " +  channel
// #define RPL_INVITE(source, channel, target)             "341 " + source + " " + channel + " : You are invited to channel " +  channel + " by " + target
// #define NOTICE(source, channel, target)                 "001 " + source + " :Invitation to " + channel + " sent to " + target
// #define RPL_NAMREPLY(source, channel, users)            "353 " + source + " = " + channel + " :" + users
// #define RPL_ENDOFNAMES(source, channel)                 "366 " + source + " " + channel + " :End of /NAMES list."
// 
// 
// #define RPL_JOIN(source, channel)                       ":" + source + " JOIN :" + channel
// #define RPL_PART(source, channel)                       ":" + source + " PART :" + channel
// #define RPL_PING(source, token)                         ":" + source + " PONG :" + token
// #define RPL_PRIVMSG(source, target, message)            ":" + source + " PRIVMSG " + target + " :" + message
// #define RPL_NOTICE(source, target, message)             ":" + source + " NOTICE " + target + " :" + message
// #define RPL_QUIT(source, message)                       ":" + source + " QUIT :Quit: " + message
// #define RPL_KICK(source, channel, target, reason)       ":" + source + " KICK " + channel + " " + target + " :" + reason





#endif
