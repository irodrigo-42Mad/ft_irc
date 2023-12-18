# include "commands/IRC_UserCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Errors.hpp"

IRC_UserCommand::IRC_UserCommand()
    : IRC_ACommand("USER", 4, 0)
{}

void IRC_UserCommand::execute(IRC_Message& message)
{
    if (message.getSourceUser().getAccess() > 0)
    {
        message.reply(ERR_ALREADYREGISTRED);
        return ;
    }  
    message.getSourceUser().setIdent(message.operator[](0));
    message.getSourceUser().setRealName(message.operator[](3));
    if (!message.getSourceUser().getName().empty())
    {
	    message.getSourceUser().setAccess(1);
        message.getServer().sendMOTDMsg(&message.getSourceUser());

        //std::cout << "pass: " << message.getSourceUser().getPass() << std::endl;
        //if (message.getSourceUser().getPass() != message.getServer().getPassword())
        //   message.getServer().userQuit(&message.getSourceUser(), "Invalid server password");
    }

        //ToDo: ¿aquí hay que mirar más cosas ...... Envío del ping y más ....?
}
