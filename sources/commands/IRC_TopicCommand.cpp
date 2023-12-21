# include "commands/IRC_TopicCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Errors.hpp"

IRC_TopicCommand::IRC_TopicCommand()
	: IRC_ACommand("TOPIC", 1, 1)
{}

void IRC_TopicCommand::execute(IRC_Message& message) {
		const std::string& name = message[0];
    IRC_Channel *channel = message.getServer().findChannelByName(name);
    IRC_Server& server = message.getServer();
		IRC_User& user = message.getUser();
	
		if (!channel)
		{
				user.send(ERR_NOSUCHCHANNEL(user.getName(), name));
				return ;
		}
		if (message.size() == 1)
		{
				if (channel->getTopic().empty())
				{
						user.send(RPL_NOTOPIC(user.getName(), channel->getName()));
				}
				else
				{
						user.send(RPL_TOPIC(user.getName(), channel->getName(), channel->getTopic()));
				}
				return ;
		}
    if (!user.isInChannel(channel))
		{
			  user.send(ERR_NOTONCHANNEL(user.getName(), name));
				return ;
		}
		if (channel->getCreator() != &user)
		{
				user.send(ERR_CHANOPRIVSNEEDED(channel->getName()));
				return ;
		}
		const std::string& newTopic = message[1];
		server.changeChannelTopic(&user, channel, newTopic);
		//advertir a todos los del canal incluido a mi.
		//message.reply(RPL_TOPIC(user.getName(), channel->getName(), channel->getTopic()));
}
