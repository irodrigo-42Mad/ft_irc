#include "commands/IRC_NickCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Utils.hpp"
#include "IRC_Errors.hpp"

IRC_NickCommand::IRC_NickCommand()
	: IRC_ACommand("NICK", 1, UNREGISTERED)
{}

void IRC_NickCommand::execute(IRC_Message& message)
{
	std::string newName = message[0];
	IRC_User& user = message.getUser();
	IRC_Server& server = message.getServer();
	IRC_Response response;

	response = server.changeNameUser(user, newName);
	if (response == ERRONEOUS_NICK)
	{
		user.send(ERR_ERRONEOUSNICKNAME(user.getName(), newName));
	}
	else if (response == NICK_IN_USE)
	{
		user.send(ERR_NICKNAMEINUSE(newName));
	}
	else
  {
		if (server.setRegisteredUser(user))
		{
			//TODO: check password?
			
			//ToDo: Welcome()

			// ToDo: Revisar como calcular el tiempo de Timeout
			server.sendWelcomeMsg(user);
      		server.sendMOTDMsg(user);
		}
	}
}
