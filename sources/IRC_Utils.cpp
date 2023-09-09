/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Utils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:51:12 by icastell          #+#    #+#             */
/*   Updated: 2023/09/09 15:00:11 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/IRC_Utils.hpp"

bool	checkPort(std::string const &port)
{
	int aux_port = std::stoi(port);	//Ojo, esta función es de C11. Buscar solución a esto
	
	if ((aux_port <= 0) || (aux_port > 65536))
		return (false);
	return (true);
}

bool	checkPasswordNotEmpty(std::string const &password)
{
	if (password.length() == 0)
		return (false);
	return (true);
}
