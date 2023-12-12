#ifndef IRC_PASSCOMMAND_HPP
# define IRC_PASSCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_PassCommand : IRC_ACommand {
	IRC_PassCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
