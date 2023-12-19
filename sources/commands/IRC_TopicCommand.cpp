# include "commands/IRC_TopicCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Errors.hpp"

IRC_TopicCommand::IRC_TopicCommand()
	: IRC_ACommand("TOPIC", 1, 1)
{}

void IRC_TopicCommand::execute(IRC_Message& message) {
	const std::string& name = message[0];
    IRC_Channel *channel = message.getServer().findChannelByName(name);
	IRC_User& user = message.getSourceUser();
	
	if (!channel)
	{
        message.reply(ERR_NOSUCHCHANNEL(user.getName(), name));
		return ;
	}
	if (message.getParamSize() == 1)
	{
		if (channel->getTopic().empty())
		{
			message.reply(RPL_NOTOPIC(user.getName(), channel->getName()));
		}
		else
		{
			message.reply(RPL_TOPIC(user.getName(), channel->getName(), channel->getTopic()));
		}
		return ;
	}
    if (!user.isInChannel(channel))
	{
	    message.reply(ERR_NOTONCHANNEL(user.getName(), name));
		return ;
	}
	if (channel->getCreator() != &user)
	{
		message.reply(ERR_CHANOPRIVSNEEDED(channel->getName()));
		return ;
	}
	const std::string& topic = message[1];
	message.getServer().changeChannelTopic(&user, channel, topic);
	//advertir a todos los del canal incluido a mi.
		//message.reply(RPL_TOPIC(user.getName(), channel->getName(), channel->getTopic()));
}
