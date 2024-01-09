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

	// en algun momento tenemos que comprobar si es el primer nick de todos, en este caso, deberemos comprobar si
	// existe nickname, realname y se ha contestado correctamente a ping para consolidar al usuario y darle un realname



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
	// ToDo: check valid nickname, valid realname, valid ping
	// if toesto es true 

	if (server.setRegisteredUser(user))
	{
			//TODO: check password?
			
			//ToDo: Welcome()

			// ToDo: Revisar como calcular el tiempo de Timeout
		server.sendWelcomeMsg(&user);
      	server.sendMOTDMsg(&user);
	}
	else
		// c1 gestionar el timeout y si no tiene realname salir
		// c2 el nivel de acceso quiere cambiar el nickname no controla ping ni pong
		
		; //informar
	
	std::cout << "se ha cambiado el nick por " << newName << std::endl;		//y si ha habido que crearlo también se crea?
}
