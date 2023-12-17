# include "commands/IRC_UserCommand.hpp"

# include "commands/IRC_PassCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Errors.hpp"

IRC_UserCommand::IRC_UserCommand()
    : IRC_ACommand("USER", 4, 0)
{}

void IRC_UserCommand::execute(IRC_Message& message)
{
    std::string source = message.getSourceUser().getName();

    if (message.getParams().empty() || message.getParamSize() < 4)
    {
        message.reply(ERR_NEEDMOREPARAMS(source, "USER"));
        return ;
    }
    if (message.getSourceUser().getAccess() >= 1)
    {
        message.reply(ERR_ALREADYREGISTRED);
        return ;
    }  
    //message.getSourceUser().setIdent() = message.operator[](0);
    //message.getSourceUser().setRealname() = message.operator[](3);
	//message.getSourceUser().setAccess(1);
    //message.getSourceUser().updateMask();

        //aquí hay que mirar más cosas ...... Envío del ping y más ....
    
}
