#include "commands/IRC_UserCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Errors.hpp"

#include <iostream>

IRC_UserCommand::IRC_UserCommand()
    : IRC_ACommand("USER", 4, UNREGISTERED)
{}

void IRC_UserCommand::execute(IRC_Message& message)
{
		IRC_User& user = message.getUser();
		IRC_Server& server = message.getServer();

    if (user.getAccess() > 0)
    {
        user.reply(server, ERR_ALREADYREGISTRED(user.getName()));
        return ;
    }  
    user.setIdent(message[0]);
    user.setRealName(message[3]);
    if (server.setRegisteredUser(user))
    {
		// igual a nickcommand

        //TODO: check password?
		//ToDo: Welcome()
		// ToDo: Revisar como calcular el tiempo de Timeout
        server.sendWelcomeMsg(user);
        server.sendMOTDMsg(user);
    }
    else
        ;
       // si hay timeout nos desconectamos C1 si no tiene nickname
       



		/*
    std::cout << "nick usuario = " << user.getName() << std::endl;
    std::cout << "| ident usuario = " << user.getIdent();
    std::cout << "| fd usuario = " << user.getFd();
    std::cout << " desde IRC_UserCommand" << std::endl;
    */
}
