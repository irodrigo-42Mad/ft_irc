/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Errors.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:41:49 by icastell          #+#    #+#             */
/*   Updated: 2023/09/09 12:22:02 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/IRC_Errors.hpp"

/* el nivel de error se distribuye de la siguiente forma*/
/* 1 nivel SEJODIODELTO (ERR_COMPLETELY_SCREWED)
   2 nivel ENTOAVIASESALVA (ERR_STILL_SAVED)
   3 nivel CURASANA (ERR_CURA_SANA)*/

int	ft_err_msg(std::string const &msg, int err_lvl, int err_n)
{
	if (err_lvl == ERR_COMPLETELY_SCREWED)
		std::cerr << BOLD_RED << "Error: " << RESET << BOLD_WHITE << msg << "." << RESET << RED << " ¡Impossible continue!" << RESET << std::endl;
	else if (err_lvl == ERR_STILL_SAVED)
		std::cerr << BOLD_YELLOW << "Error: " << RESET << BOLD_WHITE << msg << "." << RESET << YELLOW << " Will try to close and continue." << RESET << std::endl;
	else if (err_lvl == ERR_CURA_SANA)
		std::cerr << BOLD_PURPLE << "Error: " << RESET << BOLD_WHITE << msg << "." << RESET << PURPLE << " If not be repaired today will be repaired tomorrow." << RESET << std::endl;
	return (err_n);
}
