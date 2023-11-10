# 42 ft_irc

This is a simple IRC server based on RFC's 2812 and 1459 totaly rewriten in C++ 98.

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
- Once you are connected, you can register like a normal IRC server does.
```bash
PASS <password>
```
```bash
NICK <nickname>
```
```bash
USER <username> 0 * <realname>
```


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
