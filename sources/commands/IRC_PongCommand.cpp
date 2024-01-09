#include "commands/IRC_PongCommand.hpp"
#include "console.hpp"

IRC_PongCommand::IRC_PongCommand()
	: IRC_ACommand("PONG", 1, UNREGISTERED)
{}

void IRC_PongCommand::execute(IRC_Message& /*message*/) {
		debug << "PONG command executed" << std::endl;
}
