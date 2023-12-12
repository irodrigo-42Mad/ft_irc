# include "commands/IRC_ListCommand.hpp"

IRC_ListCommand::IRC_ListCommand()
	: IRC_ACommand("LIST", 0, 2)
{}

void IRC_ListCommand::execute(IRC_Message& /*message*/) {
	std::cout << "LIST command executed" << std::endl;
}
