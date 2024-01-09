#include "commands/IRC_KickCommand.hpp"
#include "console.hpp"

IRC_KickCommand::IRC_KickCommand()
	: IRC_ACommand("KICK", 3, REGISTERED)
{}

void IRC_KickCommand::execute(IRC_Message& /*message*/) {
		debug << "KICK command executed" << std::endl;
}
