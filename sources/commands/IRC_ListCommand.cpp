# include "commands/IRC_ListCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Errors.hpp"

IRC_ListCommand::IRC_ListCommand()
	: IRC_ACommand("LIST", 0, 1)
{}

void IRC_ListCommand::execute(IRC_Message& message) {
	// obtiene el listado de canales de un servidor de IRC
	// ToDo: comprobar los parámetros porque es diferente la salida
	
	if (message.getParams().empty() || message.operator[](0).empty())
		message.getServer().channelList(&message.getSourceUser());
	else
	{
		std::cout << message.getParamSize() << std::endl;
		for (size_t i = 0; i < message.getParamSize(); ++i)
			std::cout << message.operator[](1) << std::endl;
		//for (size_t i = 0; i < message.getParamSize(); ++i)
		//	message.getServer().channelListByName(&message.getSourceUser(), message.operator[](i));
		message.reply(RPL_LISTEND);
	}
}
