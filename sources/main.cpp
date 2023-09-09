/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:47:22 by icastell          #+#    #+#             */
/*   Updated: 2023/09/09 14:59:57 by icastell         ###   ########.fr       */
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
	//InitError srvError;
	//return(0);
}
