/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Utils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:49:23 by icastell          #+#    #+#             */
/*   Updated: 2023/09/09 14:57:07 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRC_UTILS_HPP
#define IRC_UTILS_HPP

# include "IRC_Headers.hpp"

// auxiliar functions
bool	checkPort(std::string const &port);
bool	checkPasswordNotEmpty(std::string const &password);

#endif
