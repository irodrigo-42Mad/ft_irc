# include "commands/IRC_NickCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Utils.hpp"

IRC_NickCommand::IRC_NickCommand()
	: IRC_ACommand("NICK", 1, 1)
{}

void IRC_NickCommand::execute(IRC_Message& message)
{
	std::string nickName = message.operator[](0);
	
	std::cout << "NICK command executed" << std::endl;
	//IRC_User& user = message.getSourceUser();
	if (message.getParams().empty() || nickName.empty())
	{
		std::cout << "error 431 ERR_NONNICKNAMEGIVEN\n";
		return ;
	}
	if (!checkNickname(nickName))
	{
		std::cout << "error 432 ERR_ERRONEUSNICKNAME\n";
		return ;
	}
	IRC_Server &srv = message.getServer();
	std::string const nickNameC = toUpperInIRC(nickName);
	if (srv.findUserByName(nickNameC))
	{
		std::cout << "error 433 ERR_NICKNAMEINUSE\n";
		return ;
	}
	// if (message.getServer().findUserByName(toUpperInIRC(nickName)))
	// {
	
	// }
	//añadir el nickName
}
