# include "commands/IRC_PrivMsgCommand.hpp"

IRC_PrivMsgCommand::IRC_PrivMsgCommand()
	: IRC_ACommand("PRIVMSG", 2, 2)
{}

void IRC_PrivMsgCommand::execute(IRC_Message& /*message*/) {
	std::cout << "PRIVMSG command executed" << std::endl;
}
