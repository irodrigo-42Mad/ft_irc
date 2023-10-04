/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Utils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:51:12 by icastell          #+#    #+#             */
/*   Updated: 2023/10/03 13:05:52 by irodrigo         ###   ########.fr       */
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
std::string	cStr(long num)
{
	std::ostringstream	ss;

	ss << num;
	return ss.str();
}

void	lTrim(std::string& str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	str.erase(0, i);
}

void	rTrim(std::string & str)
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

std::string	strReplace(std::string str, std::string strFind, std::string strReplace)
{
	return str.replace(str.find(strFind), strFind.size(), strReplace);
}

std::string strTrunc(std::string str, int strSize)
{


}



std::string	extractWord(std::string& data)
{
	std::size_t	pos;
	std::string	newStr;

	pos = data.find(' ');
	if (pos != std::string::npos)
	{
		newStr = pos == 0 ? data.substr(0, 1) : data.substr(0, pos);
		pos == 0 ? data.erase(0, 1) : data.erase(0, pos);
		return newStr;
	}
	newStr = data;
	data.clear();
	return newStr;
}

std::string	maxLengthTrim(std::string& data, int maxlength)
{
	std::size_t	pos;
	std::string	newStr;





	pos = data.find(' ');
	if (pos != std::string::npos)
	{
		newStr = pos == 0 ? data.substr(0, 1) : data.substr(0, pos);
		pos == 0 ? data.erase(0, 1) : data.erase(0, pos);
		return newStr;
	}
	newStr = data;
	data.clear();
	return newStr;
}



std::string	maxBuffer_trim(std::string &line, int maxBuffer)
{
	std::string	sortedLine;
	std::string nextWord;
	std::string	tmpLine = line;

	for (; !tmpLine.empty(); )
	{
		nextWord = extractWord(tmpLine);
		if ((int)(sortedLine.size() + nextWord.size()) < maxBuffer)
		{
			extractWord(line);
			sortedLine += nextWord;
		}
		else
			return sortedLine;
	}
	line.clear();
	return sortedLine;
}

std::string	strReplace(std::string str, std::string strFind, std::string strReplace)
{
	return str.replace(str.find(strFind), strFind.size(), strReplace);
}



