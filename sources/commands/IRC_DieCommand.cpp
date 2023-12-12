# include "commands/IRC_DieCommand.hpp"

IRC_DieCommand::IRC_DieCommand()
	: IRC_ACommand("DIE", 1, 3)
{}

void IRC_DieCommand::execute(IRC_Message& /*message*/) {
	std::cout << "DIE command executed" << std::endl;
}
