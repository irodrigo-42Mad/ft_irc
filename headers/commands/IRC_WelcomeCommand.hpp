#ifndef IRC_WELCOMECOMMAND_HPP
# define IRC_WELCOMECOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_WelcomeCommand : IRC_ACommand {
	IRC_WelcomeCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
