#ifndef IRC_KICKCOMMAND_HPP
# define IRC_KICKCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_KickCommand : IRC_ACommand {
	IRC_KickCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
