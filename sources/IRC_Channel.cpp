/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Channel.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:07:35 by icastell          #+#    #+#             */
/*   Updated: 2023/12/04 16:48:07 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/IRC_Channel.hpp"
#include "../headers/IRC_Structs.hpp"

IRC_Channel::IRC_Channel(IRC_Server &server, IRC_Users* creator, std::string const &name):
    _server(server), _creator(creator), _channelName(name)
{
    // Inicializar el modo del canal y otras propiedades del canal, según sea necesario.
    this->_topic = "Bienvenido al canal " + name;
    this->_key = ""; // Puedes establecer una clave si es necesario.
    this->_limit = 0; // Puedes establecer un límite si es necesario.
    this->_userMap[this->_creator] = 2; // Agregar el creador como miembro del canal

    // También puedes configurar otros modos de canal, como invitaciones, si es necesario.
}

IRC_Channel::~IRC_Channel() // destructor de canal, veremos a ver que debemos hacer aqui.
{
}

bool    IRC_Channel::addUser(IRC_Users *userToAdd)
{
    return (this->_userMap.insert(std::make_pair(userToAdd, 0)).second);
}

void    IRC_Channel::deleteUser(IRC_Users *userToDelete)
{
    // Eliminar un usuario del canal
    this->_userMap.erase(userToDelete);
    
    // Resto del código de eliminación del usuario...
    if (this->_userMap.empty())  // there are not users in channel
    {
        // erase channel
        //this->_server.getChannelsMap().erase(this->_server.getChannelsMap().find(getName()));
        std::cout << "Channel " << getName() << " deleted" << std::endl;
        delete this;
    }
}

void    IRC_Channel::sendMessage(std::string const &str, int userFd)
{
    // Enviar un mensaje a todos los usuarios del canal excepto el que lo envió (si se proporciona userFd)
    for (_usersInChannelMap::iterator it = _userMap.begin(); it != _userMap.end(); it++)
    {
        if (!userFd || userFd != it->first->getUserFd())
            send_all(it->first, str.c_str()); // Asegúrate de que esta función esté definida adecuadamente.
    }
}

void IRC_Channel::setTopic(std::string newTopic)
{
    // se debe comprobar que el nombre de canal es correcto.
    // y no existe en la lista de canales.
    this->_topic = newTopic;
}
std::string IRC_Channel::getTopic()
{
    return (this->_topic);
}
void IRC_Channel::setName(std::string chName)
{
    // se debe comprobar que el nombre de canal es correcto.
    // y no existe en la lista de canales.
    this->_channelName = chName;
}
std::string IRC_Channel::getName()
{
    return (this->_channelName);
}
userMap & IRC_Channel::getUsers()
{
    return (this->_userMap);
}