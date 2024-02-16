/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:47:08 by irodrigo          #+#    #+#             */
/*   Updated: 2024/02/16 11:50:18 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/IRC_Server.hpp"

int	main(int argc, char *argv[])
{
	//if (std::strcmp(argv[0], "./ircserv") != 0)
    //	return (ft_err_msg("APP's name is not correct; it can not run", ERR_COMPLETELY_SCREWED, 1));   
	if (argc != 3)
		return (ft_err_msg("./ircserv <port> <password>", ERR_COMPLETELY_SCREWED, 2));
	if (!checkPort(argv[1]))
		return (ft_err_msg("invalid port", ERR_COMPLETELY_SCREWED, 3));
	if (!checkPasswordNotEmpty(argv[2]))
		return (ft_err_msg("password is empty!", ERR_COMPLETELY_SCREWED, 3));
	
	IRC_Server irc(argv[1], argv[2]);   // crearemos el servidor
	IRC_Server::State srvState = IRC_Server::ALIVE;

	irc.start();    		 	// lanzaremos el bucle del pool
	srvState = irc.getState();  // comprobamos que no está caido en cada ejecución

	std::cout << "Status: " << srvState << std::endl;
	return(0);
}
