# include "commands/IRC_PassCommand.hpp"
# include "IRC_Message.hpp"
# include "IRC_User.hpp"
# include "IRC_Errors.hpp"


IRC_PassCommand::IRC_PassCommand()
    : IRC_ACommand("PASS", 1, 0)
{}

void IRC_PassCommand::execute(IRC_Message& message)
{
		IRC_User& user = message.getUser();
    std::string password = message[0];

    if (message.getUser().getAccess() > 0)
    {
		//if (nickname.empty())
		//	nickname = "*";
        user.send(ERR_ALREADYREGISTRED);
        return ;
    }
	message.getUser().setPass(password);
}
