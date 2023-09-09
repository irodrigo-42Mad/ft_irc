/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:47:22 by icastell          #+#    #+#             */
/*   Updated: 2023/09/09 12:22:20 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/IRC_Headers.hpp"


int	main(int argc, char *argv[])
{
	if (std::strcmp(argv[0], "./ircserv") != 0)
    	return (ft_err_msg("APP's name is not correct; it can not run", ERR_COMPLETELY_SCREWED, 1));   
	if (argc != 3)
		return (ft_err_msg("./ircserv <port> <password>", ERR_COMPLETELY_SCREWED, 2));
	
	
	std::cout << "número de argumentos: " << argc << std::endl;
	for (int i = 0; i < argc; ++i)
	{
		std::cout << "arg[" << i << "]: " << argv[i] << std::endl;
	}
	
	//InitError srvError;
	//return(0);
}
