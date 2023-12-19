# include "commands/IRC_NickCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Utils.hpp"
# include "IRC_Errors.hpp"

IRC_NickCommand::IRC_NickCommand()
	: IRC_ACommand("NICK", 1, 0)
{}

void IRC_NickCommand::execute(IRC_Message& message)
{
	std::string nickName = message[0];
	std::string source = message.getSourceUser().getName();
	IRC_User& sourceUser = message.getSourceUser();

	std::string err_nickName = nickName;
	
	// if (message.getParams().empty() || nickName.empty())
	// {
		// message.reply(ERR_NEEDMOREPARAMS(source, "NICK"));	//ToDo: Review: 431 or 461?
		// return ;
	// }
	if (!checkNickname(nickName))
	{
		message.reply(ERR_ERRONEUSNICKNAME(source, err_nickName));
		return ;
		//stetic verification
	}
	else if (toUpperNickname(source) == toUpperNickname(nickName))
	{
		//std::cout << "'" << source << "':'" << nickName << "'" << std::endl;
		if (source == nickName)
			return;
	}
	else if (message.getServer().findUserByName(nickName))
	{
		message.reply(ERR_NICKNAMEINUSE(nickName));
		return ;
	}
	//añadir el nickName
	message.getServer().changeNameUser(&sourceUser, nickName);
	if (sourceUser.getAccess() == 0)
	{
		if (!sourceUser.getIdent().empty())
		{
			std::cout << "ident " << sourceUser.getIdent() << std::endl;
			sourceUser.setAccess(1);
			//verificar que la contraseña es correcta: pass user == pass server?
		}
	}
	else
		;//informar
	
	std::cout << "se ha cambiado el nick por " << nickName << std::endl;		//y si ha habido que crearlo también se crea?
}
