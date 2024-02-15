#include "commands/IRC_PingCommand.hpp"
#include "IRC_Server.hpp"
#include "console.hpp"

IRC_PingCommand::IRC_PingCommand()
	: IRC_ACommand("PING", 1, UNREGISTERED)
{}

void IRC_PingCommand::execute(IRC_Message& message)
{
		IRC_Server &server = message.getServer();
		IRC_User &user = message.getUser();
		std::string data = message[0];

		server.pong(&user, data);

		// enviar peticion de pong al usuario
		// " PONG " + message.get_server().getServerName() + " :" + message.get_params()[0] + "\r\n";

		Console::debug << "PING command executed" << std::endl;
}

/*

void	cmd_ping(Message &message)
{
	User		&user = *message.get_user();
	std::string	line;

	if (message.get_params().empty())
		return message.send_numeric(" 461 ", findAndReplace(Message::numericsMap[ERR_NEEDMOREPARAMS], "<command>", "PING"));
	line = message.prefix + " PONG " + message.get_server().getServerName() + " :" + message.get_params()[0] + "\r\n";
	send_all(&user, line.c_str());
}

void	cmd_pong(Message &message)
{
	User		&user = *message.get_user();
	std::string	line;

	if (!message.get_params().empty() && message.get_params()[0] == PONG_STR)
	{
		if (!user.isRegistered() && user.get_nick() != "*" && user.get_username() != "unknown")
			message.welcome_user();

			user.reset_time();
			user.set_timeout(0);
	}
}
*/
