/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Structs.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:34:40 by icastell          #+#    #+#             */
/*   Updated: 2023/10/02 13:07:18 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRC_STRUCTS_HPP
#define IRC_STRUCTS_HPP

# include "IRC_Headers.hpp"

//server data structs and enums
	typedef std::map<int, IRC_Users*>						UserMap;     // ojo hay que ver si correcto
	typedef UserMap::iterator								UserMapIterator;
	typedef std::map<std::string, void (*)(Message &)>		cmdMap;
	typedef	std::map<IRC_Users*, int>						channelUsersMap; // ojo, hay que ver si correcto.


//channel data structs and enums
	typedef std::map<std::string, IRC_Channel*>				channelsMap; // ojo, hay que ver si correcto
	typedef std::pair<channelsMap::iterator, bool>			pairAddChannel;


//client data structs and enums

#endif