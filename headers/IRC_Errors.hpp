/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Errors.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:38:07 by icastell          #+#    #+#             */
/*   Updated: 2024/02/18 21:14:13 by pcosta-j         ###   ########.fr       */
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
# define RPL_WELCOME(nickname, network, mask)            			"001 " + nickname + " :Welcome to the " + network + " IRC Network " + mask
# define RPL_YOURHOST(nickname, servername, version)				"002 " + nickname + " :Your host is " + servername + ", running version " + version
# define RPL_CREATED(nickname, date)								"003 " + nickname + " :This server was created " + date
# define RPL_MYINFO(nickname, servername, version)					"004 " + nickname + " :" + servername + " " + version + " itkol"
# define RPL_ISUPPORT(nickname, tokens)								"005 " + nickname + " " + tokens + " :are supported by this server"
# define RPL_LIST(nickname, channel, mode, topic)					"322 " + nickname + " " + channel + " " + mode + " :" + topic
# define RPL_LISTEND(nickname)										"323 " + nickname + " :End of LIST"
# define RPL_CHANNELMODEIS(nickname, channel, mode_data)			"324 " + nickname + " " + channel + " " + mode_data
# define RPL_CREATIONTIME(nickname, channel, creation_time)			"329 " + nickname + " " + channel + " :" + creation_time
# define RPL_NOTOPIC(nickname, channel)								"331 " + nickname + " " + channel + " :No topic is set"
# define RPL_TOPIC(nickname, channel, topic)						"332 " + nickname + " " + channel + " :" + topic
# define RPL_TOPICWHOTIME(nickname, channel, user, time) 			"333 " + nickname + " " + channel + " " + user + " :" + time
# define RPL_INVITING(nickname, channel)							"341 " + nickname + " " + channel + " : Invited"
# define RPL_NAMREPLY(nickname, channel, names)						"353 " + nickname + " = " + channel + " :" + names
# define RPL_ENDOFNAMES(nickname, channel)							"366 " + nickname + " " + channel + " :End of NAMES list"
# define RPL_MOTD(nickmame, text)									"372 " + nickmame + " :" + text
# define RPL_MOTDSTART(nickname, server)							"375 " + nickname + " :- " + server + " Message of the day - "
# define RPL_ENDOFMOTD(nickname)									"376 " + nickname + " :End of MOTD command"
# define RPL_YOUAREOPER(nickname)									"381 " + nickname + " :You are now an IRC operator"

// error replies
# define ERR_NOSUCHNICK(nickname, user)          					"401 " + nickname + " " + user + " :No such nick/channel"
# define ERR_NOSUCHSERVER(nickname, server)							"402 " + nickname + " " + server + " :No such server"
# define ERR_NOSUCHCHANNEL(nickname, channel)						"403 " + nickname + " " + channel + " :No such channel"
# define ERR_CANNOTSENDTOCHAN(nickname, channel, mode)		        "404 " + nickname + " " + channel + " :Cannot send to channel (" + mode + ")"
# define ERR_TOOMANYCHANNELS(nickname, channel)						"405 " + nickname + " " + channel + " :You have joined too many channels"
# define ERR_NORECIPIENT(nickname, command)							"411 " + nickname + " :No recipient given (" + command + ")"
# define ERR_NOTEXTTOSEND(nickname)									"412 " + nickname + " :No text to send"
# define ERR_UNKNOWNCOMMAND(nickname, command)						"421 " + nickname + " " + command + " :Unknown command"
# define ERR_NONICKNAMEGIVEN(nickname)								"431 " + nickname + " :No nickname given"
# define ERR_ERRONEOUSNICKNAME(nickname, err_nickname)				"432 " + nickname + " " + err_nickname + " :Erroneous nickname"
# define ERR_NICKNAMEINUSE(nickname)								"433 " + nickname + " :Nickname is already in use"
# define ERR_USERNOTINCHANNEL(nickname, channel)					"441 " + nickname + " " + channel + " :They aren't on that channel"
# define ERR_NOTONCHANNEL(nickname, channel)						"442 " + nickname + channel + " :You're not on that channel"
# define ERR_USERONCHANNEL(nickname, channel)						"443 " + nickname + channel + " :is already on channel"
# define ERR_NOTREGISTERED(nickname, command)						"451 " + nickname + " " + command + " :You have not registered"
# define ERR_NEEDMOREPARAMS(nickname, command)						"461 " + nickname + " " + command + " :Not enough parameters"
# define ERR_ALREADYREGISTRED(nickname)			        			"462 " + nickname + " :Unauthorized command (already registered)"
# define ERR_PASSWDMISMATCH(nickname)								"464 " + nickname + " :Password incorrect"
# define ERR_CHANNELISFULL(nickname, channel)           			"471 " + nickname + " " + channel + " :Cannot join channel (+l)"
# define ERR_UNKNOWNMODE(nickname, mode, channel)       			"472 " + nickname + " " + mode + " :is unknown mode char to me for " + channel
# define ERR_INVITEONLYCHAN(nickname, channel)						"473 " + nickname + " " + channel + " :Cannot join channel (+i)"
# define ERR_BANNEDFROMCHAN(nickname, channel)   					"474 " + nickname + " " + channel + " :Cannot join channel (+b)"
# define ERR_BADCHANNELKEY(nickname, channel)           			"475 " + nickname + " " + channel + " :Cannot join channel (+k)"
# define ERR_BADCHANMASK(nickname, channel)							"476 " + nickname + " " + channel + " :Bad Channel Mask"
# define ERR_NOPRIVILEGES(nickname)									"481 " + nickname + " :Permission Denied- You're not an IRC operator"
# define ERR_CHANOPRIVSNEEDED(nickname, channel)					"482 " + nickname + " " + channel + " :You're not channel operator"
# define ERR_NOOPERHOST(nickname)									"491 " + nickname + " :No O-lines for your host"
# define ERR_USERSDONTMATH(nickname)				    			"502 " + nickname + " :Cannot change mode for other users"
# define ERR_INVALIDMODEPARAM(nickname, target, mode)				"696 " + nickname + " " + target + " " + mode + " :You must specify a parameter for the mode."
# define ERR_PONG(mask, message)									"ERROR: Closing link: (" + mask + ") " + message 

#endif
