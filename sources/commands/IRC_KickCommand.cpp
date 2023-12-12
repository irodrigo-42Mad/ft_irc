# include "commands/IRC_KickCommand.hpp"

IRC_KickCommand::IRC_KickCommand()
	: IRC_ACommand("KICK", 3, 1)
{}

void IRC_KickCommand::execute(IRC_Message& /*message*/) {
	std::cout << "KICK command executed" << std::endl;
}
