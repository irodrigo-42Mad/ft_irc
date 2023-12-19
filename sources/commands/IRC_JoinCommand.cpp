# include "commands/IRC_JoinCommand.hpp"
# include "IRC_Channel.hpp"
# include "IRC_Server.hpp"

IRC_JoinCommand::IRC_JoinCommand()
	: IRC_ACommand("JOIN", 1, 1)
{}

void IRC_JoinCommand::execute(IRC_Message& message){

	const std::string& channelName = message[0];
	IRC_Channel *channel = message.getServer().findChannelByName(message[0]);
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getSourceUser();
	//IRC_Channel *newChannel;

	if (!channel) // channel doesn't exist
	{
		//std::cout << "new channel " << message.operator[](0) << "created" << std::endl;
		channel = server.createChannel(channelName, &user);
		//newChannel = new IRC_Channel(message.getServer(), &message.getSourceUser(), message.operator[](0));

		server.addUserToChannel(&user, channel);
		user.setAccess(2); // change user access level to operator
		//ToDo: RPL de canales
	}
	else
	{
		if (!user.isInChannel(channel))
		{
			server.addUserToChannel(&user, channel);
			//RPL a todos
		}
		// else
		// {
		// 	//RPL error a canal;
		// }
	}
	
	/*
	//1 comprobar que el canal existe o no
	//	    2 si no existe crearlo con el usuario
	TODO	3 avisar de la creacion del canal y la "union del usuario"
		3 si existe comprobar que el usuario no se encuentra en el channel
		4 si ya se encuentra reply de error en channel
		5 si no se encuentra, añadir el usuario al canal
		6 informar al resto de usuarios del canal del nuevo usuario
	*/

}
