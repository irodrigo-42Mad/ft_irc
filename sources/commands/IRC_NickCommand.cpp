# include "commands/IRC_NickCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Utils.hpp"
# include "IRC_Errors.hpp"

IRC_NickCommand::IRC_NickCommand()
	: IRC_ACommand("NICK", 1, 0)
{}

void IRC_NickCommand::execute(IRC_Message& message)
{
	std::string newName = message[0];
	IRC_User& user = message.getUser();
	IRC_Server& server = message.getServer();

	//std::string err_nickName = nickName;
	
	// if (message.getParams().empty() || nickName.empty())
	// {
		// message.reply(ERR_NEEDMOREPARAMS(source, "NICK"));	//ToDo: Review: 431 or 461?
		// return ;
	// }
	if (!checkNickname(newName))
	{
		user.send(ERR_ERRONEUSNICKNAME(user.getName(), newName));
		return ;
		//stetic verification
	}
	else if (toUpperNickname(user.getName()) == toUpperNickname(newName))
	{
		//std::cout << "'" << source << "':'" << nickName << "'" << std::endl;
		if (user.getName() == newName)
			return;
	}
	else if (message.getServer().findUserByName(newName))
	{
		user.send(ERR_NICKNAMEINUSE(newName));
		return ;
	}
	//añadir el nickName
	message.getServer().changeNameUser(&user, newName);
	if (server.setRegisteredUser(user))
	{
			//TODO: check password?
      server.sendMOTDMsg(&user);
	}
	else
		;//informar
	
	std::cout << "se ha cambiado el nick por " << newName << std::endl;		//y si ha habido que crearlo también se crea?
}
