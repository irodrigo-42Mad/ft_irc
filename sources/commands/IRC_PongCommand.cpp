# include "commands/IRC_PongCommand.hpp"

IRC_PongCommand::IRC_PongCommand()
	: IRC_ACommand("PONG", 1, 2)
{}

void IRC_PongCommand::execute(IRC_Message& /*message*/) {
	std::cout << "PONG command executed" << std::endl;
}
