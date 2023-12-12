# include "commands/IRC_NoticeCommand.hpp"

IRC_NoticeCommand::IRC_NoticeCommand()
	: IRC_ACommand("NOTICE", 2, 2)
{}

void IRC_NoticeCommand::execute(IRC_Message& /*message*/) {
	std::cout << "NOTICE command executed" << std::endl;
}
