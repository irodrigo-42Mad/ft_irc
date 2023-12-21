# include "commands/IRC_PartCommand.hpp"
# include "IRC_Server.hpp"

IRC_PartCommand::IRC_PartCommand()
	: IRC_ACommand("PART", 1, 1)
{}

void IRC_PartCommand::execute(IRC_Message& message)
{
	const std::string& channelName = message[0];

	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	IRC_Channel* channel = server.findChannelByName(channelName);

	if (!channel)
	{
		user.send(ERR_NOSUCHCHANNEL(user.getName(), channelName));
	}
	else if (!channel->hasUser(&user))
	{
		user.send(ERR_NOTONCHANNEL(user.getName(), channelName));
	}
	else
	{
		if (message.size() == 2)
		{
			channel->send(user, "PART " + channel->getName() + " :" + message[1]);	
		}
		else
		{
			channel->send(user, "PART " + channel->getName());
		}
		server.removeUserFromChannel(&user, channel);
	}
}
