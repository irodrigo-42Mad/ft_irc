#ifndef IRC_PRIVMSGCOMMAND_HPP
# define IRC_PRIVMSGCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_PrivMsgCommand : IRC_ACommand {
	IRC_PrivMsgCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
