#include "commands/IRC_QuitCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Errors.hpp"

IRC_QuitCommand::IRC_QuitCommand()
	: IRC_ACommand("QUIT", 0, UNREGISTERED)
{}

void IRC_QuitCommand::execute(IRC_Message& message)
{
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();

	if (message.size() == 0)
		server.quitUser(user, "");
	else
		server.quitUser(user, message[0]);
}
