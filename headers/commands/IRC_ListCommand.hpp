#ifndef IRC_LISTCOMMAND_HPP
# define IRC_LISTCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_ListCommand : IRC_ACommand {
	IRC_ListCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
