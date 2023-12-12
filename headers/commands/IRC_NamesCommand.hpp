#ifndef IRC_NAMESCOMMAND_HPP
# define IRC_NAMESCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_NamesCommand : IRC_ACommand {
	IRC_NamesCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
