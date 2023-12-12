#ifndef IRC_DIECOMMAND_HPP
# define IRC_DIECOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_DieCommand : IRC_ACommand {
	IRC_DieCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
