# include "commands/IRC_NickCommand.hpp"

IRC_NickCommand::IRC_NickCommand()
	: IRC_ACommand("NICK", 1, 1)
{}

void IRC_NickCommand::execute(IRC_Message& /*message*/) {
	std::cout << "NICK command executed" << std::endl;
}
