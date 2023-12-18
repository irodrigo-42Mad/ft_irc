# include "commands/IRC_JoinCommand.hpp"

IRC_JoinCommand::IRC_JoinCommand()
	: IRC_ACommand("JOIN", 1, 1)
{}

void IRC_JoinCommand::execute(IRC_Message& /*message*/) {
	std::cout << "JOIN command executed" << std::endl;
}
