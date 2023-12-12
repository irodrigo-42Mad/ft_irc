# include "commands/IRC_UserCommand.hpp"

IRC_UserCommand::IRC_UserCommand()
	: IRC_ACommand("USER", 5, 1)
{}

void IRC_UserCommand::execute(IRC_Message& /*message*/) {
	std::cout << "USER command executed" << std::endl;
}
