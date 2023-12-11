#ifndef IRC_NICKCOMMAND_HPP
# define IRC_NICKCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_NickCommand : IRC_ACommand {
	IRC_NickCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
