#include "commands/IRC_NoticeCommand.hpp"
#include "console.hpp"

IRC_NoticeCommand::IRC_NoticeCommand()
	: IRC_ACommand("NOTICE", 1, REGISTERED)
{}

void IRC_NoticeCommand::execute(IRC_Message& /*message*/) {
		debug << "NOTICE command executed" << std::endl;
}
