#ifndef IRC_MOTDCOMMAND_HPP
# define IRC_MOTDCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_MOTDCommand : IRC_ACommand {
	IRC_MOTDCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
