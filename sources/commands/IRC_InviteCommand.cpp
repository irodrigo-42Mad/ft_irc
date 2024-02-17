# include "commands/IRC_InviteCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_User.hpp"
# include "IRC_Channel.hpp"
# include "IRC_Errors.hpp"

IRC_InviteCommand::IRC_InviteCommand()
	: IRC_ACommand("INVITE", 2, REGISTERED)
{}

void IRC_InviteCommand::execute(IRC_Message& message) {
	std::string nickName = message[0];
	IRC_User& user = message.getUser();
	IRC_Server& server = message.getServer();
	IRC_Channel *channel = server.findChannelByName(message[1]);
	std::string reason = "No reason specified!";
	
	if (!channel)
  	{
		user.reply(server, ERR_NOSUCHCHANNEL(nickName, message[1]));
    	return ;
  	}

	if (!channel->isOperator(user)) //toUpperNickname(user.getName()) != toUpperNickname(channel->getCreator().getName()))
	{
		user.reply(server, ERR_CHANOPRIVSNEEDED(nickName, channel->getName()));
		return ;
	}
	
	IRC_User	*invitedUser = server.findUserByName(nickName);

	if (!invitedUser)
	{
		user.reply(server, ERR_NOSUCHNICK(user.getName(), nickName));
		return ;
	}

	if (invitedUser->isInChannel(*channel))
	{
        user.reply(server, ERR_USERONCHANNEL(nickName, channel->getName()));
        return ;
    }

	if (!server.findInvitedUserToAChannel(nickName, channel->getName()))
		server.insertInvitedUser(nickName, *channel);

	invitedUser->reply(server, RPL_INVITING(nickName, channel->getName()));
}
