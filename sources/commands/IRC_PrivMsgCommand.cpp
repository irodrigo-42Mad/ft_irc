#include "commands/IRC_PrivMsgCommand.hpp"
#include "console.hpp"

IRC_PrivMsgCommand::IRC_PrivMsgCommand()
	: IRC_ACommand("PRIVMSG", 1, REGISTERED)
{}

void IRC_PrivMsgCommand::execute(IRC_Message& /*message*/) {
		debug << "PRIVMSG command executed" << std::endl;
}
