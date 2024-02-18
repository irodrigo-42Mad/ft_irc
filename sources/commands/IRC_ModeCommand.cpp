#include "commands/IRC_ModeCommand.hpp"
#include "IRC_Server.hpp"
#include "IRC_Errors.hpp"
#include "tools.hpp"

#include <string>

IRC_ModeCommand::IRC_ModeCommand()
	: IRC_ACommand("MODE", 1, REGISTERED)
{}

void IRC_ModeCommand::execute(IRC_Message& message)
{
	const std::string& target = message[0];

	if (isChannel(target))
	{
		this->_executeChannel(message);
	}
	else
	{
		this->_executeUser(message);
	}
}

void IRC_ModeCommand::_executeChannel(IRC_Message& message)
{
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	IRC_Channel* targetChannel = server.findChannelByName(message[0]);
	std::stringstream creationTime;

	if (!targetChannel)
	{
		user.reply(server, ERR_NOSUCHCHANNEL(user.getName(), message[0]));
		return ;
	}
	if (message.size() == 1) //empty modelist parameter
	{
		creationTime << targetChannel->getCreationTime();
		user.reply(server, RPL_CHANNELMODEIS(user.getName(), targetChannel->getName(), targetChannel->getModes(user)));
		user.reply(server, RPL_CREATIONTIME(user.getName(), targetChannel->getName(), creationTime.str()));
	}
	else //modifying chan modes
	{
	  std::vector<std::string> modes(message.getParams().begin() + 1, message.getParams().end());
		std::string response;

		response = targetChannel->setModes(user, server, modes);
		if (!response.empty())
			targetChannel->send(user, "MODE " + targetChannel->getName() + " " + response);
	}
}

void IRC_ModeCommand::_executeUser(IRC_Message& message)
{
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	IRC_User* targetUser = server.findUserByName(message[0]);

	if (!targetUser)
	{
		user.reply(server, ERR_NOSUCHNICK(user.getName(), message[0]));
		return ;
	}
	if (message.size() == 2) //empty modelist parameter
	{
		//TODO: Show the list modes of that user
		Console::debug << "Showing the modelist of " << targetUser->getName() << std::endl;
	}
	else
	{
		if (targetUser == &user) //try to change modelist for own user
		{
			std::string const& modes = message[1];
			//TODO: process modelist
			Console::debug << "Processing modelist '" << modes << "' of " << targetUser << std::endl;
		}
		else
		{
			user.reply(server, ERR_USERSDONTMATH(targetUser->getName()));
		}
	}
}
