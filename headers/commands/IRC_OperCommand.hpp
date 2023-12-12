#ifndef IRC_OPERCOMMAND_HPP
# define IRC_OPERCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_OperCommand : IRC_ACommand {
	IRC_OperCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
