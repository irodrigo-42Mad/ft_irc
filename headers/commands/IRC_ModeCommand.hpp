#ifndef IRC_MODECOMMAND_HPP
# define IRC_MODECOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_ModeCommand : IRC_ACommand {
	IRC_ModeCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
