#ifndef IRC_TOPICCOMMAND_HPP
# define IRC_TOPICCOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_TopicCommand : IRC_ACommand {
	IRC_TopicCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
