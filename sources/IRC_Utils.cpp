/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Utils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:51:12 by icastell          #+#    #+#             */
/*   Updated: 2023/12/14 11:39:10 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/IRC_Utils.hpp"
# include "../headers/IRC_Constants.hpp"

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

bool	checkChannelName(std::string const &name)
{
	for (std::size_t i = 0; i < name.length(); ++i)
	{
        // Comprobar si hay espacio, coma o ASCII 7 en el string
        if (name[i] == ' ' || name[i] == ',' || name[i] == 7)
            return (false);  // El string no cumple con los requisitos
    }
    return (true);  // El string cumple con los requisitos
}

void	deleteUnwantedChars(std::string &name)
{
	for (std::size_t i = 0; i < name.length(); ++i) {
				//std::cout << tempName[i] << std::endl;
        if (name[i] == ' ' || name[i] == ',' || name[i] == 7)
		{
			//std::cout << tempName[i] << std::endl;
            name.erase(i, 1);
            --i;  // Ajustar el índice después de eliminar el carácter
        }
    }
}

std::string	channelName(std::string const &name)
{
	std::string	tempName = name;
	bool		modifiedName = false;
	//tempName += 7; //para probar a insertar un carácter 7 ASCII
	
	if (!checkChannelName(tempName))
	{
		deleteUnwantedChars(tempName);
		modifiedName = true;
    }
	if (!tempName.empty() && tempName[0] != '#')
        tempName = '#' + tempName;
	if (tempName.length() > 50)
	{
		tempName.erase(tempName.begin()+50, tempName.end());
		modifiedName = true;
	}
	if (modifiedName)
		std::cout << "the channel name has been modified; the new channel name is " << tempName << std::endl;
	return (tempName);
}

bool	checkHostName(std::string &name)
{
	//std::cout << "el hostname es: " << name << std::endl;
	if (name.length() > 63)
		name.erase(name.begin()+63, name.end());
	//std::cout << "el nuevo hostname es: " << name << std::endl;
    for (std::size_t i = 0; i < name.length(); ++i)	// Verificar los letteres permitidos
	{
        char currentChar = name[i];
        // Permitir a-z, A-Z, 0-9, y '-' (excepto en la primera y última posición)
        if (!((currentChar >= 'a' && currentChar <= 'z') ||
              (currentChar >= 'A' && currentChar <= 'Z') ||
              (currentChar >= '0' && currentChar <= '9') ||
              (currentChar == '-' && i > 0 && i < name.length() - 1))) {
            return (false);  // letter no permitido
        }
    }
    return (true);  // El string cumple con los requisitos
}

bool	checkNickname(const std::string &name)
{
    if (name.length() > 9)
        return (false);
	std::string allowedChar = SPECIALCHAR;
    for (std::size_t i = 0; i < name.length(); ++i) {
        char currentChar = name[i];
        // Permitir letras (mayúsculas y minúsculas), dígitos y letteres definidos en SPECIALCHAR
        if (!((currentChar >= 'a' && currentChar <= 'z') ||
              (currentChar >= 'A' && currentChar <= 'Z') ||
              (currentChar >= '0' && currentChar <= '9') ||
              (allowedChar.find(currentChar) != std::string::npos))) {
            return (false);  // letter no permitido
        }
    }
    return (true);  // El string cumple con los requisitos
}

std::string toUpperInIRC(std::string &str)
{
	std::string toUpperStr;

    for (std::size_t i = 0; i < str.length(); ++i)
	{
        char currentChar = str[i];
		if ((currentChar >= 'a' && currentChar <= 'z') ||
              (currentChar == '{' || currentChar == '}' ||
			  currentChar == '|' || currentChar == '^'))
			currentChar -= 32;
		toUpperStr += currentChar;
    }
    return (toUpperStr);
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
	return (str.replace(str.find(strFind), strFind.size(), strReplace));
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
		return (newStr);
	}
	newStr = str;
	str.clear();
	return (newStr);
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
			return (srtLine);
	}
	rawLine.clear();
	return (srtLine);
}
