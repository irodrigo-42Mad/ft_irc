# include "commands/IRC_QuitCommand.hpp"

IRC_QuitCommand::IRC_QuitCommand()
	: IRC_ACommand("QUIT", 1, 1)
{}

void IRC_QuitCommand::execute(IRC_Message& /*message*/) {
	std::cout << "QUIT command executed" << std::endl;
}
