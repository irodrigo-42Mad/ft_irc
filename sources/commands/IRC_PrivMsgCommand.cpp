# include "commands/IRC_PrivMsgCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_User.hpp"
# include "IRC_Errors.hpp"

IRC_PrivMsgCommand::IRC_PrivMsgCommand()
	: IRC_ACommand("PRIVMSG", 2, REGISTERED)
{}

void IRC_PrivMsgCommand::execute(IRC_Message& message) {
	std::string msgTarget = message[0];
	std::string textToBeSent = message[1];
	IRC_User& user = message.getUser();
	IRC_Server& server = message.getServer();

	if (message[1].empty())
	{
		user.reply(server, ERR_NOTEXTTOSEND(user.getName()));
		return ;
	}
	
	// Code for finding channel or user instances 
	if (msgTarget[0] == '#')
	{
		IRC_Channel *targetChannel = server.findChannelByName(msgTarget);

		if (!targetChannel)
		{
			user.reply(server, ERR_NOSUCHCHANNEL(user.getName(), msgTarget));
			return ;
		}	
		if (!targetChannel->isOperator(user) && 
				(targetChannel->isBanned(user) || targetChannel->hasModerate()) &&
				targetChannel->hasNoExternalMessages())
		{
			user.reply(server, ERR_CANNOTSENDTOCHAN(user.getName(), targetChannel->getName()));
			return ;
		}
		targetChannel->sendExcept(&user, user, "PRIVMSG " + targetChannel->getName(), textToBeSent);
	}
	else
	{
		IRC_User *targetUser = server.findUserByName(msgTarget);

		if (!targetUser)
		{
			user.reply(server, ERR_NOSUCHNICK(user.getName(), msgTarget));
			return ;
		}
		targetUser->send(user, "PRIVMSG " + targetUser->getName(), textToBeSent);
	}
}
