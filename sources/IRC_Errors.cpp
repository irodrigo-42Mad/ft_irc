/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Errors.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:01:17 by irodrigo          #+#    #+#             */
/*   Updated: 2023/10/26 20:09:39 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/IRC_Headers.hpp"

/* el nivel de error se distribuye de la siguiente forma*/
/* 1 nivel SEJODIODELTO (ERR_COMPLETELY_SCREWED)
   2 nivel ENTOAVIASESALVA (ERR_STILL_SAVED)
   3 nivel CURASANA (ERR_CURA_SANA)*/

int	ft_err_msg(std::string const &msg, int err_lvl, int err_n)
{
	if (err_lvl == ERR_COMPLETELY_SCREWED)
		std::cerr << BOLD_RED << "Error: " << RESET << BOLD_WHITE << msg << "." << RESET << RED << " Sayonara baby!" << RESET << std::endl;
	else if (err_lvl == ERR_STILL_SAVED)
		std::cerr << BOLD_YELLOW << "Error: " << RESET << BOLD_WHITE << msg << "." << RESET << YELLOW << " May the force be with you." << RESET << std::endl;
	else if (err_lvl == ERR_CURA_SANA)
		std::cerr << BOLD_PURPLE << "Error: " << RESET << BOLD_WHITE << msg << "." << RESET << PURPLE << " If it is not repaired today it will be cured tomorrow." << RESET << std::endl;
	return (err_n);
}
