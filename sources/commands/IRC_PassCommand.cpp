# include "commands/IRC_PassCommand.hpp"

IRC_PassCommand::IRC_PassCommand()
	: IRC_ACommand("PASS", 1, 1)
{}

void IRC_PassCommand::execute(IRC_Message& /*message*/) {
	std::cout << "PASS command executed" << std::endl;
}
