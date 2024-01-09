# include "commands/IRC_WelcomeCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Errors.hpp"

IRC_WelcomeCommand::IRC_WelcomeCommand()
	: IRC_ACommand("WELCOME", 0, REGISTERED)
{}

void IRC_WelcomeCommand::execute(IRC_Message& message) {
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();

	server.sendWelcomeMsg(user);

}
