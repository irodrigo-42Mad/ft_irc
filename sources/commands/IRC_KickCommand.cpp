#include "commands/IRC_KickCommand.hpp"
#include "console.hpp"
#include "IRC_Server.hpp"

IRC_KickCommand::IRC_KickCommand()
	: IRC_ACommand("KICK", 2, REGISTERED)
{}

void IRC_KickCommand::execute(IRC_Message& message) 
{
	const std::string& channelName = message[0];
	const std::string& kickName = message[1];

	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	IRC_User* kickUser = server.findUserByName(kickName);
	IRC_Channel* channel = server.findChannelByName(channelName);
	IRC_Response response;
	std::string msg;

	if (message.size() > 2)
		msg = message[2];
	if (!channel)
	{
		user.reply(server, ERR_NOSUCHCHANNEL(user.getName(), channelName));
		return ;
	}

	if (!kickUser)
	{
		user.reply(server, ERR_NOSUCHNICK(user.getName(), kickName));
		return ;
	}

	if (!user.isInChannel(*channel))
	{
		user.reply(server, ERR_USERNOTINCHANNEL(user.getName(), channelName));
		return ;
	}
		
	if (!channel->isOperator(user))
	{
		user.reply(server, ERR_CHANOPRIVSNEEDED(user.getName(), channelName));
		return ;
	}
	response = server.kickUser(*kickUser, *channel, msg);
	if (response == NOT_IN_CHANNEL)
	{
		user.reply(server, ERR_NOTONCHANNEL(user.getName(), channelName));
		return ;
	}
}
