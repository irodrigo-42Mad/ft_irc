#include "commands/IRC_NamesCommand.hpp"
#include "console.hpp"

IRC_NamesCommand::IRC_NamesCommand()
	: IRC_ACommand("NAMES", 1, REGISTERED)
{}

void IRC_NamesCommand::execute(IRC_Message& /*message*/) {
		debug << "NAMES command executed" << std::endl;
}
