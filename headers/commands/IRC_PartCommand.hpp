#ifndef IRC_PARTCOMMAND_HPP
# define IRC_PARTCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_PartCommand : IRC_ACommand {
	IRC_PartCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
