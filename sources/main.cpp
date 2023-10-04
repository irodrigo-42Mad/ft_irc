/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:47:08 by irodrigo          #+#    #+#             */
/*   Updated: 2023/10/03 13:13:06 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/IRC_Headers.hpp"

int	main(int argc, char *argv[])
{
	if (std::strcmp(argv[0], "./ircserv") != 0)
    	return (ft_err_msg("APP's name is not correct; it can not run", ERR_COMPLETELY_SCREWED, 1));   
	if (argc != 3)
		return (ft_err_msg("./ircserv <port> <password>", ERR_COMPLETELY_SCREWED, 2));
	if (!checkPort(argv[1]))
		return (ft_err_msg("invalid port", ERR_COMPLETELY_SCREWED, 3));
	if (!checkPasswordNotEmpty(argv[2]))
		return (ft_err_msg("password is empty!", ERR_COMPLETELY_SCREWED, 3));
	
	IRC_Server irc(argv[1], argv[2]);   // crearemos el servidor
	IRC_Server::State state = IRC_Server::ALIVE;

	while (state != IRC_Server::DIE)
	{
		try {
			//irc.loadConfig(configFile.c_str());
			irc.launch();    		 // lanzaremos el bucle del pool
			state = irc.getState();  // comprobamos que no está caido en cada ejecución
		}
		catch (std::exception &e) {
			std::string rtdo;
			return(ft_err_msg (e.what(), ERR_COMPLETELY_SCREWED, 5));
			//irc.log() << e.what() << std::endl;
			//return (1);
		}
		// catch (config4cpp::ConfigurationException &e) {
		// 	return (ft_err_msg(e.c_str(),ERR_COMPLETELY_SCREWED, 3));
			
		// 	// irc.log() << e.c_str() << std::endl;
		// 	// return (1);
		// }
	}
	return(0);
}
