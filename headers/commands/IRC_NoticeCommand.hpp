#ifndef IRC_NOTICECOMMAND_HPP
# define IRC_NOTICECOMMAND_HPP

# include "IRC_ACommand.hpp"
# include <iostream>

struct IRC_NoticeCommand : IRC_ACommand {
	IRC_NoticeCommand();

	void execute(IRC_Message& /*message*/);
};

#endif
