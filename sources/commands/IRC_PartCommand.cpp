# include "commands/IRC_PartCommand.hpp"

IRC_PartCommand::IRC_PartCommand()
	: IRC_ACommand("PART", 2, 1)
{}

void IRC_PartCommand::execute(IRC_Message& /*message*/) {
	std::cout << "PART command executed" << std::endl;
}
