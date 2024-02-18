#include "commands/IRC_DieCommand.hpp"
#include "IRC_Server.hpp" 

IRC_DieCommand::IRC_DieCommand()
	: IRC_ACommand("DIE", 0, OPERATOR)
{}

void IRC_DieCommand::execute(IRC_Message& message) {
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	std::string msg;

	if (message.size() == 1)
		msg = message[0];

	server.shutdown("Server shutdown by " + user.getName() + ": (" + msg + ")");
}
