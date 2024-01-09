#include "commands/IRC_PassCommand.hpp"
#include "IRC_Message.hpp"
#include "IRC_User.hpp"
#include "IRC_Errors.hpp"

IRC_PassCommand::IRC_PassCommand()
    : IRC_ACommand("PASS", 1, UNREGISTERED)
{}

void IRC_PassCommand::execute(IRC_Message& message)
{
		IRC_User& user = message.getUser();
		IRC_Server& server = message.getServer();
    std::string password = message[0];


    if (message.getUser().getAccess() > 0)
    {
        user.reply(server, ERR_ALREADYREGISTRED(user.getName()));
        return ;
    }
		message.getUser().setPass(password);
}
