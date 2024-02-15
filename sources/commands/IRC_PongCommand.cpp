#include "commands/IRC_PongCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_User.hpp"
#include "console.hpp"

IRC_PongCommand::IRC_PongCommand()
	: IRC_ACommand("PONG", 1, UNREGISTERED)
{}

void IRC_PongCommand::execute(IRC_Message &message)
{
	IRC_User &user = message.getUser();
	IRC_Server &server = message.getServer();
	const std::string &pingText = message[0];

	Console::debug << "pingText = '" << pingText << "'" << std::endl;
	if (user.getAccess() == PENDING)
	{
		if (pingText == user.getPingText())
		{
			user.setAccess(REGISTERED);
			user.disablePingTimeout();
			server.sendWelcomeMsg(user);
			server.sendMOTDMsg(user);
		}
		else
		{
			server.quitUser(user, "Incorrect ping reply for registration");
		}
	}
	user.disablePingTimeout();
}
