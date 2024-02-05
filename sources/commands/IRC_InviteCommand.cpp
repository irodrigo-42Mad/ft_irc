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

	if (toUpperNickname(user.getName()) != toUpperNickname(channel->getCreator().getName()))
	{
		user.reply(server, ERR_CHANOPRIVSNEEDED(nickName, channel->getName()));
		return ;
	}
	
	IRC_User	*invitedUser = server.findUserByName(nickName);

	if (!invitedUser)
	{
		user.reply(server, ERR_NOSUCHNICK(nickName));
		return ;
	}

	if (invitedUser->isInChannel(*channel))
	{
        user.reply(server, ERR_USERONCHANNEL(nickName, channel->getName()));
        return ;
    }
	// meter al invitedUser al multimap siempre que no esté y comunicar que ha sido invitdo
	std::cout << server.findInvitedUserToAChannel(nickName, channel->getName()) << std::endl;
	if (!server.findInvitedUserToAChannel(nickName, channel->getName()))
		server.insertInvitedUser(nickName, *channel);

	invitedUser->reply(server, RPL_INVITING(nickName, channel->getName()));
	
	//channel->addUser(user);	//hacer un nuevo mapa (multimap) para almacenar los usuarios invitados.
	// invitación de un único uso
	// si se sale de IRC te tienen que volver a invitar
}

// syntax: Invite <client> <channel>

// void    Invite::execute(Client* client, std::vector<std::string> args)
// {
// 
    // if (args.size() >= 3 && (args[2][0] != ':' || args[2].size() > 1))
    // {
        // reason = "";
// 
        // std::vector<std::string>::iterator it = args.begin();
        // std::vector<std::string>::iterator end = args.end();
// 
        // while (it != end)
        // {
            // reason.append(*it + " ");
            // it++;
        // }
    // }
	    // Channel *channel = _srv->get_channel(name);
		// Client* clientinvited = _srv->get_client(target);
// 
    // if (!clientinvited)
    // {
        // client->reply(ERR_NOSUCHNICK(client->get_nickname(), target));
        // return;
    // }
	// if (channel->is_ban_client(clientinvited))
	// {
		// client->reply(ERR_BANEDFROMCHAN(channel->get_name(), target));
// 
		// return ;
	// }
	// if (channel->is_invited(clientinvited))
	// {
		// client->reply(ERR_ALREADYINVITED(client->get_nickname(), target, name));
		// return ;
	// }
    // channel->invite(client, clientinvited);
// }
