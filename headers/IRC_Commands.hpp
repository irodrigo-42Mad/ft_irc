#ifndef IRC_COMMANDS_HPP
# define IRC_COMMANDS_HPP

# include "IRC_Messages.hpp"

	// IRC Commands
void				cmdPass(IRC_Messages& message); // 1  UNREGISTERED
void				cmdNick(IRC_Messages& message); // 1  UNREGISTERED
void				cmdUser(IRC_Messages& message); // 5  UNREGISTERED
void				cmdQuit(IRC_Messages& message); // 1 UNREGISTERED
			
void				cmdPing(IRC_Messages& message); // 1  REGISTERED
void				cmdPong(IRC_Messages& message); // 1  REGISTERED
																									
void				cmdPrivMsg(IRC_Messages& message); // 2
void				cmdNotice(IRC_Messages& message); // 2
																									 //
void				cmdOper(IRC_Messages& message);  // 2  //FLAG OPERATOR (user)
void				cmdKill(IRC_Messages& message);    // 2  OPERATOR
void				cmdDie(IRC_Messages& message);     // 1  OPERATOR
																									 //
void				cmdJoin(IRC_Messages& message);
void				cmdList(IRC_Messages& message);  // 0
void				cmdNames(IRC_Messages& message); // 1
void				cmdPart(IRC_Messages& message);    // 2
void				cmdKick(IRC_Messages& message);    // 3
void				cmdTopic(IRC_Messages& message);   // 2
																									 //
		// probably not necesary
void				cmdMode (IRC_Messages& message);   // >1

# define MAX_COMMANDS 18

struct IRC_Command {
	void (*fn_cmd)(IRC_Messages&);
	std::string cmd;
	int params;
	int access;

	IRC_Command() {}

	IRC_Command(void (*fn_cmd)(IRC_Messages&), const std::string& cmd, int params, int access)
		: fn_cmd(fn_cmd)
		, cmd(cmd)
		, params(params)
		, access(access)
	{}
};

IRC_Command  commands[MAX_COMMANDS];

void init_commands() {
	commands[0] = IRC_Command(cmdJoin, "JOIN", 2, 1);
	commands[1] = IRC_Command(cmdPart, "PART", 3, 1);
	commands[2] = IRC_Command(cmdJoin, 2, 1);
	commands[0] = IRC_Command(cmdJoin, 2, 1);
	commands[0] = IRC_Command(cmdJoin, 2, 1);
	commands[0] = IRC_Command(cmdJoin, 2, 1);
	commands[0] = IRC_Command(cmdJoin, 2, 1);
	commands[0] = IRC_Command(cmdJoin, 2, 1);
	commands[0] = IRC_Command(cmdJoin, 2, 1);
	commands[0] = IRC_Command(cmdJoin, 2, 1);
}

void run_command(IRC_Messages& message) {
	for (int i = 0; i < MAX_COMMANDS; ++i) {
		if (commands[i].cmd == message.cmd) {
			if (message.sourceUser.getAccess() < commands[i].access) {
				//error privillegios insuficientes
				return ;
			}
			if (message.size() > commands[i].params) {
				commands[i].fn_cmd(message);
				return ;
			} else
				;//error // parametros insuficientes
		}
	}
	//error comando no existe
}


#endif
