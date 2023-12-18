# include "commands/IRC_TopicCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Errors.hpp"

IRC_TopicCommand::IRC_TopicCommand()
	: IRC_ACommand("TOPIC", 1, 1)
{}

void IRC_TopicCommand::execute(IRC_Message& message) {
	if (message.getParamSize() == 1)
	
		if (message.operator[](0))
	message.getServer().changeChannelTopic(message.getSourceUser(), message.operator[](0));
	
	std::cout << "TOPIC command executed" << std::endl;
}
