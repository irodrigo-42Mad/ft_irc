/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Utils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:49:23 by icastell          #+#    #+#             */
/*   Updated: 2023/10/03 13:05:54 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRC_UTILS_HPP
#define IRC_UTILS_HPP

# include "IRC_Headers.hpp"

// auxiliar functions
bool		checkPort(char *port);
bool		checkPasswordNotEmpty(std::string const &password);


// string functions
std::string	cStr(long num);
void		lTrim(std::string& str);
void		rTrim(std::string& str);
std::string	strReplace(std::string str, std::string strFind, std::string strReplace);



#endif
