# include "commands/IRC_PingCommand.hpp"

IRC_PingCommand::IRC_PingCommand()
	: IRC_ACommand("PING", 1, 2)
{}

void IRC_PingCommand::execute(IRC_Message& /*message*/) {
	std::cout << "PING command executed" << std::endl;
}
