# include "commands/IRC_OperCommand.hpp"

IRC_OperCommand::IRC_OperCommand()
	: IRC_ACommand("OPER", 1, 3)
{}

void IRC_OperCommand::execute(IRC_Message& /*message*/) {
	std::cout << "OPER command executed" << std::endl;
}
