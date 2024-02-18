/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Exception.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:08:36 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:08:37 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_EXCEPTION_HPP
# define IRC_EXCEPTION_HPP

# include <exception>

struct IRC_Exception : public std::exception
{
	IRC_Exception(const char* message)
		: _message(message)
	{}

	virtual const char* what() const throw()
	{
		return this->_message;
	}

private:
	const char* _message;

};

#endif
