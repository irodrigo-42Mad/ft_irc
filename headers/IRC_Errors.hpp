/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Errors.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:38:07 by icastell          #+#    #+#             */
/*   Updated: 2023/12/17 09:37:19 by icastell         ###   ########.fr       */
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
# define RPL_WELCOME(mask)                      "1 " + " Welcome to the Internet Relay Network " + mask
# define RPL_YOUAREOPER							"381" + " You are now an IRC operator"

// error replies
# define ERR_NOSUCHCHANNEL(channel)				"403 " + channel + " :No such channel"
# define ERR_TOOMANYCHANNELS(channel)			"405 " + channel + " :You have joined too many channels"
# define ERR_UNKNOWNCOMMAND(command)			"421 " + command + " :Unknown command"
# define ERR_NONICKNAMEGIVEN(nickname)			"431 " + nickname + " :No nickname given"
# define ERR_ERRONEUSNICKNAME(nickname)			"432 " + nickname + " :Erroneous nickname"
# define ERR_NICKNAMEINUSE(nickname)			"433 " + nickname + " :Nickname is already in use"
# define ERR_NEEDMOREPARAMS(source)				"461 " + source + " :Not enough parameters"
# define ERR_ALREADYREGISTRED(source)           "462 " + source + " :Unauthorized command (already registered)"	//ToDo: repasar esto
# define ERR_PASSWDMISMATCH(source)				"464 " + " :Password incorrect"
# define ERR_CHANNELISFULL(channel)             "471 " + channel + " :Cannot join channel (+l)"	//ToDo: ídem que el siguiente
# define ERR_INVITEONLYCHAN(channel)			"473 " + channel + " :Cannot join channel (+i)"	//ToDo: repasar esto porque creo que tiene modos
# define ERR_BANNEDFROMCHAN(channel)   			"474 " + channel + " :Cannot join channel (+b)"	//ToDo: ídem
# define ERR_BADCHANNELKEY(channel)             "475 " + channel + " :Cannot join channel (+k)"	//ToDo: ídem
# define ERR_BADCHANMASK(channel)				"476 " + channel + " :Bad Channel Mask"			//ToDo: repasar
# define ERR_NOOPERHOST							"491 " + " :No O-lines for your host"





#define ERR_NOTONCHANNEL(source, channel)               "442 " + source + " " + channel + " :You're not on that channel"
#define ERR_FORBIDDEN()              					"403  :Cannot ban an operator"
#define ERR_ALREADYINVITED(source, target, channel)     "472 " + source + " :User " + target + " is already invited to channel " + channel
#define ERR_ALREADYONCHANNEL(source, channel)           "475 " + source + " :You are already on channel " + channel

#define ERR_CANNOTSENDTOCHAN(source, channel)           "404 " + source + " " + channel + " :Cannot send to channel"
#define ERR_CHANOPRIVSNEEDED(source, channel)           "482 " + source + " " + channel + " :You're not channel operator"
#define ERR_NOPRIVILEGES(source, channel)           	"481 " + source + " " + channel + " :Permission Denied: Insufficient privileges"
#define ERR_BANEDFROMCHAN(channel, target)              "473 :User " + target + " is banned from channel " + channel

#define ERR_NOSUCHNICK(source, nickname)                "401 " + source + " " + nickname + " :No such nick/channel"
#define ERR_USERNOTINCHANNEL(source, nickname, channel) "441 " + source + " " + nickname + " " + channel + " :They aren't on that channel"

#define RPL_LIST(source, channel)						"319 " + source + " : " +  channel
#define RPL_INVITELIST(source, channel)                 "332 " + source + " : You are now on the waiting list for " +  channel
#define RPL_INVITE(source, channel, target)             "341 " + source + " " + channel + " : You are invited to channel " +  channel + " by " + target
//#define RPL_WELCOME(source)                             "001 " + source + " :Welcome " + source + " to the ft_irc network"
#define NOTICE(source, channel, target)                 "001 " + source + " :Invitation to " + channel + " sent to " + target
#define RPL_NAMREPLY(source, channel, users)            "353 " + source + " = " + channel + " :" + users
#define RPL_ENDOFNAMES(source, channel)                 "366 " + source + " " + channel + " :End of /NAMES list."


#define RPL_JOIN(source, channel)                       ":" + source + " JOIN :" + channel
#define RPL_PART(source, channel)                       ":" + source + " PART :" + channel
#define RPL_PING(source, token)                         ":" + source + " PONG :" + token
#define RPL_PRIVMSG(source, target, message)            ":" + source + " PRIVMSG " + target + " :" + message
#define RPL_NOTICE(source, target, message)             ":" + source + " NOTICE " + target + " :" + message
#define RPL_QUIT(source, message)                       ":" + source + " QUIT :Quit: " + message
#define RPL_KICK(source, channel, target, reason)       ":" + source + " KICK " + channel + " " + target + " :" + reason





#endif
