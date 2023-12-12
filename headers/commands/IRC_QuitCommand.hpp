#ifndef IRC_QUITCOMMAND_HPP
# define IRC_QUITCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_QuitCommand : IRC_ACommand {
	IRC_QuitCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
