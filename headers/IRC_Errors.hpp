/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Errors.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:38:07 by icastell          #+#    #+#             */
/*   Updated: 2023/09/09 12:20:39 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRC_ERRORS_HPP
#define IRC_ERRORS_HPP

# include "IRC_Headers.hpp"

// system error constants
#define ERR_COMPLETELY_SCREWED 1
#define ERR_STILL_SAVED 2
#define ERR_CURA_SANA 3


// system error definitions
int	ft_err_msg(std::string const &msg, int err_lvl, int err_n);

#endif
