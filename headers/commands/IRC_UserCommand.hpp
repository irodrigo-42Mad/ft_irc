#ifndef IRC_USERCOMMAND_HPP
# define IRC_USERCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_UserCommand : IRC_ACommand {
	IRC_UserCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
