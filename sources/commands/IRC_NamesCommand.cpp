# include "commands/IRC_NamesCommand.hpp"
# include "IRC_Channel.hpp"
# include "IRC_Server.hpp"

IRC_NamesCommand::IRC_NamesCommand()
	: IRC_ACommand("NAMES", 0, REGISTERED)
{}

void IRC_NamesCommand::execute(IRC_Message& message) {
	
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	std::string channelName;	//ToDo: ojo porque puede venir sin parámetros.

	if (!message.empty())
		channelName = message[0];
	else
		channelName	= "";

	if (!channelName.empty())
	{
		IRC_Channel *channel = message.getServer().findChannelByName(channelName);
		if (channel)
		{
			std::string names;  // User names of channel

			for (IRC_Channel::usersConstIterator it = channel->getUsers().begin(); it != (channel->getUsers()).end(); ++it)
    		{
				if (channel->getCreator().getName() == (*it)->getName())
					names += "@" + (*it)->getName();
				else
					names += (*it)->getName();
				names += " ";
			}
			user.reply(user, RPL_NAMREPLY(message.getUser().getName(), channel->getName(), names));
		}
	}
	else
	{
		for (IRC_Server::channelsNameConstIterator it = server.getChannels().begin(); it != server.getChannels().end(); ++it)
    	{
        	IRC_Channel *channel = (*it).second;
			std::string names;  // User names of channel

			for (IRC_Channel::usersConstIterator it = channel->getUsers().begin(); it != channel->getUsers().end(); ++it)
    		{
				if (channel->getCreator().getName() == (*it)->getName())
					names += "@" + (*it)->getName();
				else
					names += (*it)->getName();
				names += " ";
			}
			user.reply(user, RPL_NAMREPLY(message.getUser().getName(), channel->getName(), names));
		}
	}
	user.reply(user, RPL_ENDOFNAMES(message.getUser().getName(), channelName));	//ToDo: ojo a cuando channelName es nulo => sin parámetros
}
