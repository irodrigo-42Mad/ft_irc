/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:18:45 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 21:18:47 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_HPP
# define TOOLS_HPP

# include "IRC_Constants.hpp"

# include <string>

inline bool isChannel(const std::string& value)
{
	const std::string chanTypes = CHANTYPES;

	return (chanTypes.find(value[0]) != std::string::npos);
}

#endif
