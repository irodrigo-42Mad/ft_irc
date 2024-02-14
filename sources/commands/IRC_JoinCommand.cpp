#include "commands/IRC_JoinCommand.hpp"
#include "IRC_Channel.hpp"
#include "IRC_Server.hpp"

IRC_JoinCommand::IRC_JoinCommand()
	: IRC_ACommand("JOIN", 1, REGISTERED)
{}

void IRC_JoinCommand::execute(IRC_Message& message){

	const std::string& channelName = message[0];
	IRC_Channel *channel = message.getServer().findChannelByName(message[0]);
	IRC_Server& server = message.getServer();
	IRC_User& user = message.getUser();
	//IRC_Channel *newChannel;

	if (channelName[0] != '#')
	{
		user.reply(server, ERR_BADCHANMASK(user.getName(), channelName));		
		return ;
	}

	if (!channel) // channel doesn't exist
	{
		//std::cout << "new channel " << message.operator[](0) << "created" << std::endl;
		channel = server.createChannel(channelName, user);
		//newChannel = new IRC_Channel(message.getServer(), &message.getSourceUser(), message.operator[](0));

		//El nivel de acceso afecta a todo el servidor. No debe ser cambiado por
		//el hecho de entrar a un canal vacío. El canal, cuando se crea
		//ya apunta quien es el creador. Esto es algo que se ha hecho por demostrar
		//que sólo quien crea el canal tiene privilegios. Ahora, con la aparición
		//de los modos de canal, esto no tiene sentido y se cambiará.
		//user.setAccess(2); // change user access level to IRC Operator
		//ToDo: RPL de canales
	}

	if (!user.isInChannel(*channel))
	{
		server.addUserToChannel(user, *channel);
		channel->send(":" + user.getMask() + " JOIN " + channel->getName());
		//TODO: falta enviar names al entrar en el canal.
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
