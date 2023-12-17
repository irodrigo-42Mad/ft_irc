# include "commands/IRC_QuitCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Errors.hpp"

IRC_QuitCommand::IRC_QuitCommand()
	: IRC_ACommand("QUIT", 1, 1)
{}

void IRC_QuitCommand::execute(IRC_Message& message)
{
	message.getServer().userQuit(&message.getSourceUser(), message.operator[](0));
}
