#ifndef IRC_JOINCOMMAND_HPP
# define IRC_JOINCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_JoinCommand : IRC_ACommand {
	IRC_JoinCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
