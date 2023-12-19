# include "commands/IRC_MOTDCommand.hpp"
# include "IRC_Server.hpp"
# include "IRC_Errors.hpp"

IRC_MOTDCommand::IRC_MOTDCommand()
    : IRC_ACommand("MOTD", 0, 1)
{}

void IRC_MOTDCommand::execute(IRC_Message& message)
{
    message.getServer().sendMOTDMsg(&message.getSourceUser());
}
