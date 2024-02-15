/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Channel.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:07:35 by icastell          #+#    #+#             */
/*   Updated: 2024/01/22 12:36:37 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC_Channel.hpp"
#include "IRC_User.hpp"
#include "IRC_Server.hpp"
#include "IRC_Structs.hpp"
#include <iostream>

IRC_Channel::IRC_Channel(std::string const &name, IRC_User& creator)
	: _channelName(name)
	, _creator(creator)
    , _topic("")
    , _key("")
{
    // Inicializar el modo del canal y otras propiedades del canal, según sea necesario.
   // this->_topic = "Bienvenido al canal " + name;
    //this->_key = ""; // Puedes establecer una clave si es necesario.
    this->_limit = 0; // Puedes establecer un límite si es necesario.
    this->_users.insert(&creator); // Agregar el creador como miembro del canal
		Console::debug << "IRC_Channel constructor" << std::endl;

    // También puedes configurar otros modos de canal, como invitaciones, si es necesario.
}

IRC_Channel::~IRC_Channel() // destructor de canal, veremos a ver que debemos hacer aqui.
{
		Console::debug << "IRC_Channel destructor" << std::endl;
}

bool    IRC_Channel::addUser(IRC_User& userToAdd)
{
    return (this->_users.insert(&userToAdd).second);
}

void    IRC_Channel::removeUser(IRC_User& userToDelete)
{
    // Eliminar un usuario del canal
    this->_users.erase(&userToDelete);

  	/** problema, si no queda nadie más en el canal, necesítaríamos avisar al servidor
  	 ** para que borre el canal de su lista. Eso no ocurrirá, por tanto, por el
  	 ** principio de responsabilidad única, quien crea, destruye.
  	 **
  	// Resto del código de eliminación del usuario...
    if (this->_usersSet.empty())  // there are not users in channel
    {
        // erase channel
        //this->_server.getChannelsMap().erase(this->_server.getChannelsMap().find(getName()));
        std::cout << "Channel " << getName() << " deleted" << std::endl;
        delete this;
    }
    */
}

bool IRC_Channel::hasUser(IRC_User& user)
{
	return (this->_users.find(&user) != this->_users.end());
}

bool IRC_Channel::empty() const
{
	return (this->_users.empty());
}

const IRC_User& IRC_Channel::getCreator() const
{
    return (this->_creator);
}

void IRC_Channel::sendExcept(const IRC_User* exceptUser, const std::string &data)
{
		if (exceptUser)
				this->_users.erase(const_cast<IRC_User*>(exceptUser));
		this->send(data);
		if (exceptUser)
				this->_users.insert(const_cast<IRC_User*>(exceptUser));
}

void IRC_Channel::send(const IRC_User& user, const std::string& data, const std::string& lastParameter)
{
		this->sendExcept(NULL, user, data, lastParameter);
}

void IRC_Channel::send(const IRC_Server& server, const std::string& data, const std::string& lastParameter)
{
		this->sendExcept(NULL, server, data, lastParameter);
}

void IRC_Channel::send(const std::string& data)
{
    for (usersConstIterator it = this->_users.begin(); it != this->_users.end(); ++it)
    {
        (*it)->send(data);
    }
}

void IRC_Channel::sendExcept(const IRC_User* exceptUser, const IRC_User& user, const std::string& data, const std::string& lastParameter)
{
		if (lastParameter.empty())
		{
				this->sendExcept(exceptUser, ":" + user.getMask() + " " + data);
		}
		else
		{
				this->sendExcept(exceptUser, ":" + user.getMask() + " " + data + " :" + lastParameter);
		}
}

void IRC_Channel::sendExcept(const IRC_User* exceptUser, const IRC_Server& server, const std::string& data, const std::string& lastParameter)
{
	if (lastParameter.empty())
	{
		this->sendExcept(exceptUser, ":" + server.getServerName() + " " + data);
	}
	else
	{
		this->sendExcept(exceptUser, ":" + server.getServerName() + " " + data + " :" + lastParameter);
	}
}

//FIX: La entidad mínima con la que deberíais trabajar es "IRC_User" ya que ella contiene el fd de cada usuarios.
// void    IRC_Channel::sendMessage(const std::string& str, int userFd)
// {
//     // Enviar un mensaje a todos los usuarios del canal excepto el que lo envió (si se proporciona userFd)
//     for (_usersInChannelIterator it = _usersSet.begin(); it != _usersSet.end(); it++)
//     {
//         if (!userFd || userFd != (*it)->getFd())
//             this->send_all(*it, str.c_str()); // Asegúrate de que esta función esté definida adecuadamente.
//     }
// }

// void IRC_Channel::setTopic(std::string newTopic)
// {
//     // se debe comprobar que el nombre de canal es correcto.
//     // y no existe en la lista de canales.
//     this->_topic = newTopic;
// }

const std::string& IRC_Channel::getTopic() const
{
    return (this->_topic);
}

//FIX: Si queréis evitar tener que pasar por referencia la instancia IRC_Server
//os recomiendo que toda la lógica de comprobación tanto de nicks como de canales
//la realice IRC_Server.
// void IRC_Channel::setName(std::string chName)
// {
//     // se debe comprobar que el nombre de canal es correcto.
//     // y no existe en la lista de canales.
//     this->_channelName = chName;
// }

//FIX: Os he cambiado todo lo que devolvéis a referencia constante. Si no usáis una referencia o un puntero
//estaréis haciendo copias una y otra vez cada vez que devolváis cualquier valor. Esto es importante puesto que no es lo mismo devolver
//8 bytes, que sería la dirección de memoria, que devolver el contenido completo de todo el string, que eso incluye los 3 punteros que definen
//el tamaño de la cadena internamente y la propia cadena de caracteres.
//El motivo de que sea constante es que si devuelves una referencia en lugar de una copia, si esta se modifica, modificaríais también
//this->_channelName e intuyo que eso es algo que sólo debería hacerse a través de los métodos destinados a esa operación.
const std::string& IRC_Channel::getName() const
{
    return (this->_channelName);
}

const IRC_Channel::usersType& IRC_Channel::getUsers() const
{
    return (this->_users);
}

int IRC_Channel::getNumUsers() const
{
    return (this->_users.size());
}

void IRC_Channel::setTopic(const std::string& topic)
{
    this->_topic = topic;
}

/*const IRC_Channel::_usersInChannelType* IRC_Channel::getUsers() const
{
    return (&this->_usersSet);
}*/


