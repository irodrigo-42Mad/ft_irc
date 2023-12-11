/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Utils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:51:12 by icastell          #+#    #+#             */
/*   Updated: 2023/10/04 12:56:42 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/IRC_Utils.hpp"

// general utils
bool	checkPort(char *port)
{
	int aux_port = std::atoi(port);
	
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

// string threatment utils
std::string	convertStr(long num)
{
	std::ostringstream	ss;

	ss << num;
	return ss.str();
}

void	leftTrim(std::string& str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	str.erase(0, i);
}

void	rightTrim(std::string & str)
{
	size_t	i;
	int 	elNum;

	i = str.size() - 1;
	elNum = 0;

	while (str[i] && str[i] == ' ')
	{
		i--;
		elNum++;
	}
	str.erase(i, elNum);
}

std::string	strReplace(std::string str, std::string strFind, std::string strReplace) // posible & pendiente
{
	return str.replace(str.find(strFind), strFind.size(), strReplace);
}

std::string	strXtractWord(std::string& str)
{
	std::size_t	i;
	std::string	newStr;

	i = str.find(' ');
	if (i != std::string::npos)
	{
		if (str.substr(0, 1) == "\0")
			str.substr(0, 1);
		else
			str.substr(0, i);
		
		if (i == 0)
			str.erase(0, 1);
		else
			str.erase(0, i);
		return newStr;
	}
	newStr = str;
	str.clear();
	return newStr;
}

std::string	maxBufferTrim(std::string &rawLine, int maxSize)
{
	std::string	srtLine;
	std::string nxWord;
	std::string	tmpLine = rawLine;

	for (; !tmpLine.empty(); )
	{
		nxWord = strXtractWord(tmpLine);
		if ((int)(srtLine.size() + nxWord.size()) < maxSize)
		{
			strXtractWord(rawLine);
			srtLine += nxWord;
		}
		else
			return srtLine;
	}
	rawLine.clear();
	return srtLine;
}
