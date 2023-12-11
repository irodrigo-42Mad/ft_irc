/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Channel.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:07:35 by icastell          #+#    #+#             */
/*   Updated: 2023/10/15 19:19:12 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/IRC_Channel.hpp"

IRC_Channel::IRC_Channel(IRC_Server &server, IRC_Users* creator, std::string const &name):
    _server(server), _creator(creator), _channelName(name)
{
    // Inicializar el modo del canal y otras propiedades del canal, según sea necesario.
    _topic = "Bienvenido al canal " + name;
    _key = ""; // Puedes establecer una clave si es necesario.
    _limit = 0; // Puedes establecer un límite si es necesario.

    // Agregar el creador como miembro del canal
    _usersMap[creator] = 2;

    // También puedes configurar otros modos de canal, como invitaciones, si es necesario.
}

bool    IRC_Channel::addUser(IRC_Users *newUser)
{
    // Agregar un nuevo usuario al canal
    return (_usersMap.insert(std::make_pair(newUser, 0)).second);
}

void    IRC_Channel::deleteUser(IRC_Users *user)
{
    // Eliminar un usuario del canal
    _usersMap.erase(user);
    
    // Resto del código de eliminación del usuario...

    if (_usersMap.empty())
    {
        // Eliminar el canal si no hay usuarios
        _server.getChannelsMap().erase(_server.getChannelsMap().find(get_name()));
        std::cout << "Channel " << get_name() << " deleted" << std::endl;
        delete this;
    }
}

void    IRC_Channel::sendMessage(std::string const &str, int userFd)
{
    // Enviar un mensaje a todos los usuarios del canal excepto el que lo envió (si se proporciona userFd)
    for (channelUsersMap::iterator it = _usersMap.begin(); it != _usersMap.end(); it++)
    {
        if (!userFd || userFd != it->first->get_fd())
            send_all(it->first, str.c_str()); // Asegúrate de que esta función esté definida adecuadamente.
    }
}
