# include "commands/IRC_NamesCommand.hpp"

IRC_NamesCommand::IRC_NamesCommand()
	: IRC_ACommand("NAMES", 1, 2)
{}

void IRC_NamesCommand::execute(IRC_Message& /*message*/) {
	std::cout << "NAMES command executed" << std::endl;
}
