#ifndef IRC_ACOMMAND_HPP
# define IRC_ACOMMAND_HPP

# include "IRC_Message.hpp"

	// IRC Commands
void				cmdPass(IRC_Message& message); // 1  UNREGISTERED
void				cmdNick(IRC_Message& message); // 1  UNREGISTERED
void				cmdUser(IRC_Message& message); // 5  UNREGISTERED
void				cmdQuit(IRC_Message& message); // 1 UNREGISTERED
			
void				cmdPing(IRC_Message& message); // 1  REGISTERED
void				cmdPong(IRC_Message& message); // 1  REGISTERED
																									
void				cmdPrivMsg(IRC_Message& message); // 2
void				cmdNotice(IRC_Message& message); // 2
																									 //
void				cmdOper(IRC_Message& message);  // 2  //FLAG OPERATOR (user)
void				cmdKill(IRC_Message& message);    // 2  OPERATOR
void				cmdDie(IRC_Message& message);     // 1  OPERATOR
																									 //
void				cmdJoin(IRC_Message& message);
void				cmdList(IRC_Message& message);  // 0
void				cmdNames(IRC_Message& message); // 1
void				cmdPart(IRC_Message& message);    // 2
void				cmdKick(IRC_Message& message);    // 3
void				cmdTopic(IRC_Message& message);   // 2
																									 //
		// probably not necesary
void				cmdMode (IRC_Message& message);   // >1

struct IRC_ACommand {
	std::string cmd;
	size_t 	params;
	int			access;

	IRC_ACommand(const std::string& cmd, int params, int access)
	  : cmd(cmd)
	  , params(params)
		, access(access)
	{}

	~IRC_ACommand();

	virtual void execute(IRC_Message& message) = 0;

private:
	IRC_ACommand();
	IRC_ACommand(const IRC_ACommand& src);
	IRC_ACommand& operator=(const IRC_ACommand& rhs);

};

#endif
