/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Errors.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:38:07 by icastell          #+#    #+#             */
/*   Updated: 2023/12/14 18:22:45 by icastell         ###   ########.fr       */
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

// error replies

// nickname error replies
# define ERR_NONICKNAMEGIVEN(source)	"431 " + source + " :No nickname given"
# define ERR_ERRONEUSNICKNAME(source)	"432 " + source + " :Erroneous nickname"
# define ERR_NICKNAMEINUSE(source)		"433 " + source + " " + source  + " :Nickname is already in use"

#endif
