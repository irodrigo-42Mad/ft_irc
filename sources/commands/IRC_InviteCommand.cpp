# include "commands/IRC_InviteCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_User.hpp"
# include "IRC_Channel.hpp"
# include "IRC_Errors.hpp"

IRC_InviteCommand::IRC_InviteCommand()
	: IRC_ACommand("INVITE", 2, REGISTERED)
{}

void IRC_InviteCommand::execute(IRC_Message& message) {
	std::string nickName;
	IRC_User& user = message.getUser();
	IRC_Server& server = message.getServer();
	IRC_Channel *channel = server.findChannelByName(message[1]);
	std::string reason = "No reason specified!";

	if (!message.empty())
	{
		nickName = message[0];
		IRC_User *invitedUser = server.findUserByName(nickName);
	  (void)invitedUser;
	}
	

	if (!channel)
    {
        user.reply(server, ERR_NOSUCHCHANNEL(nickName, message[1]));
        return ;
    }
	if (!user.isInChannel(*channel))
	{
        user.reply(server, ERR_NOTONCHANNEL(nickName, channel->getName()));
        return ;
    }
	//if (!clientinvited)
    //{
    //    client->reply(ERR_NOSUCHNICK(client->get_nickname(), target));
    //    return;
    //}
	channel->addUser(user);	//hacer un nuevo mapa (multimap) para almacenar los usuarios invitados.
	// invitación de un único uso
	// si se sale de IRC te tienen que volver a invitar
}
