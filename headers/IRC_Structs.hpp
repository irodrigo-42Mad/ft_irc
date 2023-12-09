/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Structs.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:34:40 by icastell          #+#    #+#             */
/*   Updated: 2023/12/05 09:25:48 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_STRUCTS_HPP
# define IRC_STRUCTS_HPP

# include <map>
# include <string>

class IRC_Users;
class IRC_Channel;
class IRC_Messages;

typedef std::map<int, IRC_Users*>                           _userMap;
typedef _userMap::iterator                                  _userMapIterator;
typedef std::map<std::string, IRC_Channel*>                 _channel;
typedef std::map<IRC_Users*, int>                           _usersInChannelMap;
typedef std::pair<_usersInChannelMap::iterator, bool>       _channelUserPair;
typedef std::map <std::string, void(*)(IRC_Messages &)>     _cmdMap;

#endif
