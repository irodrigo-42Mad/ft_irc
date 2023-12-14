# include "commands/IRC_NickCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Utils.hpp"
# include "IRC_Errors.hpp"

IRC_NickCommand::IRC_NickCommand()
	: IRC_ACommand("NICK", 1, 0)
{}

void IRC_NickCommand::execute(IRC_Message& message)
{
	std::string nickName = message.operator[](0);
	
	std::cout << "NICK command executed" << std::endl;
	//IRC_User& user = message.getSourceUser();
	if (message.getParams().empty() || nickName.empty())
	{
		std::cout << "error 431 ERR_NONNICKNAMEGIVEN\n";
		message.getSourceUser().errorReply(ERR_NONICKNAMEGIVEN(nickName));
		//client->reply(ERR_NONICKNAMEGIVEN(client->get_nickname()));
		return ;
	}
	if (!checkNickname(nickName))
	{
		std::cout << "error 432 ERR_ERRONEUSNICKNAME\n";
		message.getSourceUser().errorReply(ERR_ERRONEUSNICKNAME(nickName));
		return ;
	}
	if (message.getServer().findUserByName(toUpperNickname(nickName)))
	{
		std::cout << "error 433 ERR_NICKNAMEINUSE\n";
		message.getSourceUser().errorReply(ERR_NICKNAMEINUSE(nickName));
		return ;
	}
	//añadir el nickName
	message.getServer().changeNameUser(&message.getSourceUser(), nickName);//TODO: comprobar si esto hay que ponerlo en mayúsculas
	std::cout << "se ha cambiado el nick por" << nickName << std::endl;		//y si ha habido que crearlo también se crea?
}
