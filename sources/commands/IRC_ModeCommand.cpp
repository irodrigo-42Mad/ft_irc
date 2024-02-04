#include "commands/IRC_ModeCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Errors.hpp"

IRC_ModeCommand::IRC_ModeCommand()
	: IRC_ACommand("MODE", 1, REGISTERED)
{}

// mode #canal +nt modo

void IRC_ModeCommand::execute(IRC_Message& message)
{
	IRC_User& user = message.getUser();
	IRC_Server& server = message.getServer();
	IRC_Channel* channel =  server.findChannelByName(message[0]);

	if (!channel)
	{
		user.reply(server, ERR_NOSUCHCHANNEL(user.getName(), message[0]));
		return ;
	}


	std::cout << "mode!!\n";
}
