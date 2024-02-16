#include "commands/IRC_KillCommand.hpp"
#include "IRC_Server.hpp"

IRC_KillCommand::IRC_KillCommand()
	: IRC_ACommand("KILL", 2, OPERATOR)
{}

void IRC_KillCommand::execute(IRC_Message& message) {
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	IRC_User* targetUser = server.findUserByName(message[0]);

	if (!targetUser)
	{
		user.reply(server, ERR_NOSUCHNICK(user.getName(), targetUser->getName()));
		return ;
	}

	server.killUser(user, *targetUser, message[1]);
}
