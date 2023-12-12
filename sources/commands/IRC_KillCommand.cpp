# include "commands/IRC_KillCommand.hpp"

IRC_KillCommand::IRC_KillCommand()
	: IRC_ACommand("KILL", 2, 3)
{}

void IRC_KillCommand::execute(IRC_Message& /*message*/) {
	std::cout << "KILL command executed" << std::endl;
}
