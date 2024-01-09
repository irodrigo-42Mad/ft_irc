#include "commands/IRC_OperCommand.hpp"
#include "IRC_Server.hpp"
#include "console.hpp"

IRC_OperCommand::IRC_OperCommand()
	: IRC_ACommand("OPER", 2, REGISTERED)
{}

void IRC_OperCommand::execute(IRC_Message& /*message*/)
{
		debug << "OPER command executed" << std::endl;
}
