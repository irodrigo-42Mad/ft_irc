# include "commands/IRC_NamesCommand.hpp"
# include "IRC_Channel.hpp"
# include "IRC_Server.hpp"

static void	nicknamesList(IRC_User& user, IRC_Channel *channel)
{
	std::string names;

	for (IRC_Channel::usersConstIterator it = channel->getUsers().begin(); it != (channel->getUsers()).end(); ++it)
    {
		if (channel->getCreator().getName() == (*it)->getName())
			names += "@" + (*it)->getName();
		else
			names += (*it)->getName();
		names += " ";
	}
	user.reply(user, RPL_NAMREPLY(user.getName(), channel->getName(), names));
}

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
			nicknamesList(user, channel);
		// {
			// std::string names;  // User names of channel
// 
			// for (IRC_Channel::usersSetConstIterator it = (channel->getUsers())->begin(); it != (channel->getUsers())->end(); ++it)
    		// {
				// if (channel->getCreator()->getName() == (*it)->getName())
					// names += "@" + (*it)->getName();
				// else
					// names += (*it)->getName();
				// names += " ";
			// }
			// user.reply(&user, RPL_NAMREPLY(message.getUser().getName(), channel->getName(), names));
		// }
	}
	else
	{
		for (IRC_Server::channelsNameConstIterator it = server.getChannels().begin(); it != server.getChannels().end(); ++it)
    	{
        	IRC_Channel *channel = (*it).second;
			
			nicknamesList(user, channel);
			// std::string names;  // User names of channel
// 
			// for (IRC_Channel::usersSetConstIterator it = (channel->getUsers())->begin(); it != (channel->getUsers())->end(); ++it)
    		// {
				// if (channel->getCreator()->getName() == (*it)->getName())
					// names += "@" + (*it)->getName();
				// else
					// names += (*it)->getName();
				// names += " ";
			// }
			// user.reply(&user, RPL_NAMREPLY(message.getUser().getName(), channel->getName(), names));
		}
	}
	user.reply(user, RPL_ENDOFNAMES(user.getName(), channelName));
	//user.reply(&user, RPL_ENDOFNAMES(message.getUser().getName(), channelName));	//ToDo: ojo a cuando channelName es nulo => sin parámetros
}
