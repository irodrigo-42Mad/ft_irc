# include "commands/IRC_TopicCommand.hpp"

IRC_TopicCommand::IRC_TopicCommand()
	: IRC_ACommand("TOPIC", 2, 1)
{}

void IRC_TopicCommand::execute(IRC_Message& /*message*/) {
	std::cout << "TOPIC command executed" << std::endl;
}
