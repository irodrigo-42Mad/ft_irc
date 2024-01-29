#include "commands/IRC_ModeCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Errors.hpp"

IRC_ModeCommand::IRC_ModeCommand()
	: IRC_ACommand("MODE", 1, REGISTERED)
{}

void IRC_ModeCommand::execute(IRC_Message& /*message*/)
{
	std::cout << "mode!!\n";
}
