#ifndef TOOLS_HPP
# define TOOLS_HPP

# include "IRC_Constants.hpp"

# include <string>

inline bool isChannel(const std::string& value)
{
	const std::string chanTypes = CHANTYPES;

	return (chanTypes.find(value[0]) != std::string::npos);
}

#endif
