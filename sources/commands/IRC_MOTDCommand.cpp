# include "commands/IRC_MOTDCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Errors.hpp"

IRC_MOTDCommand::IRC_MOTDCommand()
    : IRC_ACommand("MOTD", 0, 1)
{}

void IRC_MOTDCommand::execute(IRC_Message& message)
{
		IRC_Server& server = message.getServer();
		IRC_User& user = message.getUser();

    server.sendMOTDMsg(&user);
}
