# include "commands/IRC_PassCommand.hpp"
# include "IRC_Message.hpp"
# include "IRC_User.hpp"
# include "IRC_Errors.hpp"


IRC_PassCommand::IRC_PassCommand()
    : IRC_ACommand("PASS", 1, 0)
{}

void IRC_PassCommand::execute(IRC_Message& message)
{
	//std::string nickname = message.getSourceUser().getName();
    std::string password = message.operator[](0);

    if (message.getSourceUser().getAccess() > 0)
    {
		//if (nickname.empty())
		//	nickname = "*";
        message.reply(ERR_ALREADYREGISTRED);
        return ;
    }
	message.getSourceUser().setPass(password);
}
