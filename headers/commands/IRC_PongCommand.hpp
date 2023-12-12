#ifndef IRC_PONGCOMMAND_HPP
# define IRC_PONGCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_PongCommand : IRC_ACommand {
	IRC_PongCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
