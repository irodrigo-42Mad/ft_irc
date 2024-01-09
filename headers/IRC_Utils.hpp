/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Utils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:49:23 by icastell          #+#    #+#             */
/*   Updated: 2024/01/09 12:56:04 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_UTILS_HPP
# define IRC_UTILS_HPP

# include "IRC_Headers.hpp"

// auxiliar functions
bool		checkPort(char *port);
bool		checkPasswordNotEmpty(std::string const &password);
std::string	channelName(std::string const &name);
bool		checkChannelName(std::string const &name);
void		deleteUnwantedChars(std::string &name);
bool		checkHostName(std::string &name);
bool		checkNickname(const std::string &name);


// string functions
std::string	convertStr(long num);
std::string	tmToString(const std::tm& datetime);
void		leftTrim(std::string& str);
void		rightTrim(std::string& str);
std::string	strReplace(std::string str, std::string strFind, std::string strReplace);

std::string strXtractWord(std::string &str);
std::string	maxBufferTrim(std::string &rawLine, int maxSize);
std::string	toUpper(const std::string &str);
std::string toUpperNickname(const std::string &str);

#endif
