#include "commands/IRC_DieCommand.hpp"
#include "IRC_Server.hpp" 

IRC_DieCommand::IRC_DieCommand()
	: IRC_ACommand("DIE", 0, OPERATOR)
{}

void IRC_DieCommand::execute(IRC_Message& message) {
	IRC_Server& server = message.getServer();
	//IRC_User& user = message.getUser();
	
	server.shutdown("DIE");
}
