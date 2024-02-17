#include "commands/IRC_JoinCommand.hpp"
#include "IRC_Channel.hpp"
#include "IRC_Server.hpp"

IRC_JoinCommand::IRC_JoinCommand()
	: IRC_ACommand("JOIN", 1, REGISTERED)
{}

void IRC_JoinCommand::execute(IRC_Message& message){

	const std::string& channelName = message[0];
	IRC_Channel *channel = message.getServer().findChannelByName(message[0]);
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	IRC_Response response;
	const std::string chanTypes(CHANTYPES);

	if (chanTypes.find(channelName[0]) == std::string::npos)
	{
		user.reply(server, ERR_BADCHANMASK(user.getName(), channelName));		
		return ;
	}

	if (!channel) // channel doesn't exist
	{
		channel = server.createChannel(channelName, user);
	}

	if (message.size() > 1)
		response = server.joinUser(user, *channel, message[1]);
	else
		response = server.joinUser(user, *channel, "");
	
	if (response == CHANNEL_KEY_MISMATCH)
		; //TODO: mandar el numeric correspondiente
	else if (response == CHANNEL_IS_FULL)
		; //TODO: mandar el numeric correspondiente	
	else if (response == INVITE_ONLY)
		; //TODO: mandar el numeric correspondiente
}
