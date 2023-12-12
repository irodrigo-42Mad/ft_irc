#ifndef IRC_KILLCOMMAND_HPP
# define IRC_KILLCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_KillCommand : IRC_ACommand {
	IRC_KillCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
