/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:47:08 by irodrigo          #+#    #+#             */
/*   Updated: 2024/02/18 21:27:43 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC_Server.hpp"
#include "IRC_Exception.hpp"

int	main(int argc, char *argv[])
{
	if (argc != 3)
		return (ft_err_msg("./ircserv <port> <password>", ERR_COMPLETELY_SCREWED, 2));
	if (!checkPort(argv[1]))
		return (ft_err_msg("invalid port", ERR_COMPLETELY_SCREWED, 3));
	if (!checkPasswordNotEmpty(argv[2]))
		return (ft_err_msg("password is empty!", ERR_COMPLETELY_SCREWED, 3));

	try
	{
		IRC_Server irc(argv[1], argv[2]);
		irc.start();
	}
	catch (const IRC_Exception& ie)
	{
		std::cerr << "IRC_Exception: " << ie.what() << std::endl;
		return (1);
	}
	return (0);
}
