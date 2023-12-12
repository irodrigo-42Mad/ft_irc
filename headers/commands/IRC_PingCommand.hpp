#ifndef IRC_PINGCOMMAND_HPP
# define IRC_PINGCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_PingCommand : IRC_ACommand {
	IRC_PingCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
