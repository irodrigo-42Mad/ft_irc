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
		user.reply(user, ERR_NOTEXTTOSEND(user.getName()));
		return ;
	}
	
	// ToDo:	¿los dos usuarios deben estar en el mismo canal para enviarse mensajes?
	//			¿qué diferencia hay entre el comando privmsg y notice?
	
	//buscar un usuario/canal
	if (msgTarget[0] == '#')
	{
		IRC_Channel *targetChannel = server.findChannelByName(msgTarget);
		if (targetChannel)
			targetChannel->sendExcept(&user, user, "PRIVMSG " + targetChannel->getName(), textToBeSent);
			//targetChannel->sendExcept(&user, RPL_PRIVMSG(user.getMask(), targetChannel->getName(), textToBeSent));
		else
			user.reply(server, ERR_NOSUCHCHANNEL(user.getName(), msgTarget));
	}
	else
	{
		IRC_User *targetUser = server.findUserByName(msgTarget);
		if (targetUser)
		{
			// ToDo: revisar si es en todos los canales o solo en uno. Duda!!!!!!
			targetUser->send(user, "PRIVMSG " + targetUser->getName(), textToBeSent);
			//targetUser->send(RPL_PRIVMSG(":" + user.getMask(), targetUser->getName(), textToBeSent));
		}
		else
			user.reply(server, ERR_NOSUCHNICK(msgTarget));
	}
}
