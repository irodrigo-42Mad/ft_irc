#ifndef IRC_INVITECOMMAND_HPP
# define IRC_INVITECOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_InviteCommand : IRC_ACommand {
	IRC_InviteCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
