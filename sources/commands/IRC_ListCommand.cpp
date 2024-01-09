#include "commands/IRC_ListCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Errors.hpp"

IRC_ListCommand::IRC_ListCommand()
	: IRC_ACommand("LIST", 0, REGISTERED)
{}

void IRC_ListCommand::execute(IRC_Message& message) {
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();

	// obtiene el listado de canales de un servidor de IRC
	// ToDo: comprobar los parámetros porque es diferente la salida

	if (message.empty())
		server.channelList(user);
	else
	{
		std::cout << message.size() << std::endl;
		for (size_t i = 0; i < message.size(); ++i)
		{
			std::cout << message[i] << std::endl;
			server.channelListByName(user, message[i]);
		}
		user.reply(server, RPL_LISTEND(user.getName()));
	}
}
