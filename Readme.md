# 42 ft_irc

This is a simple IRC server based on RFC's [2812](https://datatracker.ietf.org/doc/html/rfc2812) and [1459](https://www.rfc-es.org/rfc/rfc1459-es.txt) totalLy rewriten in C++ 98.

This server not support Server - Server comunication (not implemented yet) and it´s functional in any client that supports common 'endl' characters '\r \n' at send packets.

## Getting Started

These instructions will permits you download and compile a copy of this proyect on your local machine for development and testing purposes. See deployment for notes on how to deploy this proyect on a live system or network.

```
	git clone https://github.com/irodrigo-42Mad/ft_irc.git
```
or

```
	go to https://github.com/irodrigo-42Mad/ft_irc.git and in the "Code" button, you can select download zip option and uncompress in your local machine.
```

### Prerequisites

For the correct compilation and use of these functions we must have installed in the system the GNU GCC compiler as well as the make tool to be able to mount the library.

```
	In OS X only need to have installed Xcode, the developer IDE from Apple. 
	
	$ xcode-select --install

	for Mac and Linux users, need install GCC compiler and developer tools using following commands:
	
	$ sudo apt install gcc
	$ sudo apt install build-essential

	after this you can compile this program correctly.

```

### Installing

Next commands compile this program in current OSX or Linux environments:

```
	$ make
	
	or
	
	$ make all
```

### Running and using this software

To run this server you need to execute en bash or zsh next commands:
```bash
./ft_irc <port> <password>
```

### Connect

If you'd like to try the server without using a IRC client, you can connect to it using the following steps.

- First open a new terminal and type:
```bash
nc -c <server host> <port>
```
- Once you are connected, you can register as normal IRC server doing this procedure.
```bash
PASS <password>
```
```bash
NICK <nickname>
```
```bash
USER <username> 0 * <realname>
```
- Then the server will send you a PING and you shoud answer with a PONG for register succesfully.
```bash
PONG server
```
From this moment we can create channels, send private messages, and using normaly IRC clients with basic command use.

## Commands handle

```
- PASS
**

- NICK
**

- USER
**

- MOTD
*

*

- JOIN
	JOIN <#channel> [password]

<italic>If the channel is protected with a password, it is necessary to include it in the order. If the channel does not exist, it will be created for us and we will enter it as a single user.</italic>

- WELCOME
*

*

- INVITE
*Send an invitation to the specified nick to join the channel we have specified. It is necessary to have channel operator status to be able to execute this command. If the channel is in +i mode (see /MODE command) only users who have been previously invited can access it.*

- TOPIC
**

- PING
**

- PONG
**

- MOTD
**

- NOTICE
**

- PRIVMSG
**

- LIST
**

- NAMES
**

- PART
**

- OPER
**

- KICK
*
```bash
Kick <#canal> [razón]
```
Este comando solo puede ser empleado por aquellos usuarios que tengan estatus de operador del canal. Provoca la inmediata expulsión del nick especificado del canal que se indique, esta expulsión podrá ir acompañada de un mensaje.
*

- KILL
*
```bash
KILL <client> <comment>
```
Forcibly removes <client> from the network. This command may only be issued by IRC operators. Defined in RFC 1459.
*

- QUIT
*
It sends the IRC server a command that causes our immediate disconnection from IRC.
*

- DIE
*
Instructs the server to shut down. This command may only be issued by IRC server operators.
*

```
## Internal functions explained

- IRC_Server

- IRC_Channel

- IRC_User

- IRC_Message

- IRC_Utils

- IRC_Errors



## Built With

* [GNU GCC](https://gcc.gnu.org) - The C Compiler used
* [Xcode](https://developer.apple.com/xcode/) - IDE GUI Editor to deploy
* [Visual Studio Code](https://code.visualstudio.com/docs/) - IDE GUI Editor to deploy
* [VIM](https://www.vim.org/download.php) - Terminal Editor to deploy
* [LLDB](https://lldb.llvm.org) - Debuger aplication
* [leaks](https://developer.apple.com/forums/thread/680081) - Check memory assigment and leak situations
* [Valgrind](https://valgrind.org/) - Check memory assigment and leak situations
* [Docker](https://www.docker.com/) - Container orchestrator

## Versioning

Version 1.0 

## Authors

* **Isaac Rodrigo** - *other repositories* - [irodrigo-42Mad](https://github.com/irodrigo-42Mad/)

* **Idoya Castell** - *other repositories* - [icastell1974](https://github.com/icastell1974/)

## Acknowledgments

* To the 42 Network students and specially to @icastell, @fballest, @rnavarre and @ccardozom colaborators and testers of this proyect.

