/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Errors.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:38:07 by icastell          #+#    #+#             */
/*   Updated: 2024/01/07 18:22:02 by icastell         ###   ########.fr       */
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
# define RPL_WELCOME(mask)                      "001 Welcome to the Internet Relay Network " + mask
# define RPL_LIST(channel, mode, topic)			"322 " + channel + " " + mode + " :" + topic
# define RPL_LISTEND							"323 :End of LIST"
# define RPL_NOTOPIC(nickname, channel)			"331 " + nickname + " " + channel + " :No topic is set"
# define RPL_TOPIC(nickname, channel, topic)	"332 " + nickname + " " + channel + " :" + topic
# define RPL_NAMREPLY(nickname, channel, names)	"353 " + nickname + " = " + channel + " :" + names
# define RPL_ENDOFNAMES(nickname, channel)		"366 " + nickname + " " + channel + " :End of NAMES list"
# define RPL_MOTD(nickmame, text)				"372 " + nickmame + " :" + text
# define RPL_MOTDSTART(nickname, server)		"375 " + nickname + " :- " + server + " Message of the day - "
# define RPL_ENDOFMOTD(nickname)				"376 " + nickname + " :End of MOTD command"
# define RPL_YOUAREOPER							"381 You are now an IRC operator"

// error replies
# define ERR_NOSUCHNICK(nickname)                		"401 " + nickname + " :No such nick/channel"
# define ERR_NOSUCHSERVER(server)						"402 " + server + " :No such server"
# define ERR_NOSUCHCHANNEL(nickname, channel)			"403 " + nickname + " " + channel + " :No such channel"
# define ERR_CANNOTSENDTOCHAN(channel)					"404 " + channel + " :Cannot send to channel"
# define ERR_TOOMANYCHANNELS(channel)					"405 " + channel + " :You have joined too many channels"
# define ERR_NORECIPIENT(command)						"411 :No recipient given (" + command + ")"
# define ERR_NOTEXTTOSEND								"412 :No text to send"
# define ERR_UNKNOWNCOMMAND(command)					"421 " + command + " :Unknown command"
# define ERR_NONICKNAMEGIVEN(nickname)					"431 " + nickname + " :No nickname given"
# define ERR_ERRONEUSNICKNAME(nickname, err_nickname)	"432 " + nickname + " " + err_nickname + " :Erroneous nickname"
# define ERR_NICKNAMEINUSE(nickname)					"433 " + nickname + " :Nickname is already in use"
# define ERR_USERNOTINCHANNEL(nickname, channel)		"441 " + nickname + " " + channel + " :They aren't on that channel"
# define ERR_NOTONCHANNEL(nickname, channel)			"442 " + nickname + channel + " :You're not on that channel"
# define ERR_NEEDMOREPARAMS(nickname, command)			"461 " + nickname + " " + command + " :Not enough parameters"
# define ERR_ALREADYREGISTRED			          		"462 :Unauthorized command (already registered)"	//ToDo: repasar esto
# define ERR_PASSWDMISMATCH(source)						"464 :Password incorrect"
# define ERR_CHANNELISFULL(channel)             		"471 " + channel + " :Cannot join channel (+l)"	//ToDo: ídem que el siguiente
# define ERR_INVITEONLYCHAN(channel)					"473 " + channel + " :Cannot join channel (+i)"	//ToDo: repasar esto porque creo que tiene modos
# define ERR_BANNEDFROMCHAN(channel)   					"474 " + channel + " :Cannot join channel (+b)"	//ToDo: ídem
# define ERR_BADCHANNELKEY(channel)            			"475 " + channel + " :Cannot join channel (+k)"	//ToDo: ídem
# define ERR_BADCHANMASK(channel)						"476 " + channel + " :Bad Channel Mask"			//ToDo: repasar
# define ERR_NOPRIVILEGES								"481 :Permission Denied- You're not an IRC operator"
# define ERR_CHANOPRIVSNEEDED(channel)					"482 " + channel + " :You're not channel operator"
# define ERR_NOOPERHOST									"491 :No O-lines for your host"





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
