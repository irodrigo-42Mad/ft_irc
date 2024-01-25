#include "commands/IRC_KickCommand.hpp"
#include "console.hpp"
#include "IRC_Server.hpp"

IRC_KickCommand::IRC_KickCommand()
	: IRC_ACommand("KICK", 3, REGISTERED)
{}

void IRC_KickCommand::execute(IRC_Message& message) 
{
		const std::string& channelName = message[0];

		IRC_Server& server = message.getServer();
		IRC_User& user = message.getUser();
		IRC_Channel* channel = server.findChannelByName(channelName);
		IRC_Response response;
		std::string msg;

		if (message.size() > 1)
			msg = message[1];
		if (!channel)
		{
				user.send(ERR_NOSUCHCHANNEL(user.getName(), channelName));
				return ;
		}
		if (!user.isInChannel(*channel))
		{
			user.send(ERR_USERNOTINCHANNEL(user.getName(), channelName));
			return ;
		}
		
		if (!(user.getAccess() == OPERATOR))
		{
			user.send(ERR_CHANOPRIVSNEEDED(user.getName(), channelName));
			return ;
		}
		response = server.kickUserFromChannel(user, *channel, msg);
		if (response == NOT_IN_CHANNEL)
		{
				user.send(ERR_NOTONCHANNEL(user.getName(), channelName));
				return ;
		}
}
