#include "terminal.hpp"
#include "console.hpp"

#include <unistd.h>
#include <signal.h>
#include <sstream>
#include <sys/ioctl.h>

Terminal terminal;

Terminal::Terminal()
{
	this->_limits.row = 0;
	this->_limits.col = 0;
	this->_getTerm();
	this->_currentTerm = this->_originalTerm;

	signal(SIGWINCH, Terminal::_sigwinchHandler);
	terminal._updateLimits();
}

Terminal::~Terminal()
{
	this->_setTerm(this->_originalTerm);
}

void Terminal::enableEcho()
{
	this->_currentTerm.c_lflag |= ECHO;
	this->_setTerm(this->_currentTerm);
}

void Terminal::disableEcho()
{
	this->_currentTerm.c_lflag &= ~ECHO;
	this->_setTerm(this->_currentTerm);
}

void Terminal::_getTerm()
{
	tcgetattr(STDIN_FILENO, &this->_originalTerm);
}

void Terminal::_setTerm(struct termios& term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void Terminal::_updatePosition()
{
	this->_currentPos = this->getCursorPosition();
}

void Terminal::clearCurrentRow()
{
	std::cout << "\r\033[K" << std::flush;
}

void Terminal::hideCursor()
{
	std::cout << "\033[?25l" << std::flush;
}

void Terminal::showCursor()
{
	std::cout << "\033[?25h" << std::flush;
}

CustomBuffer* Terminal::getCustomBuffer()
{
	return (&this->_customBuffer);
}

void Terminal::setCursorPosition(Position position)
{	
	//std::cout << "this = " << this << " ";
	std::cout << "\033[" << position.row << ":" << position.col << "H";
	if (position.row > this->_limits.row)
	{
		position.row = this->_limits.row;
	}
	if (position.col > this->_limits.col)
	{
		position.col = this->_limits.col;
	}
}

void Terminal::setCursorBottom()
{
	Position position;

	position.col = 0;
	position.row = this->_limits.row;

	//std::cout << "this = " << this << " ";
	//std::cout << "position.row = " << position.row << " : position.col = " << position.col << std::endl;
	this->setCursorPosition(position);
}

Position Terminal::getCursorPosition() const
{
	Position pos;
	char response[32];

	std::cout << "\033[6n";
	std::cin.readsome(response, sizeof(response));
	std::stringstream ss(response);
	char dummy;

	ss >> dummy >> pos.row >> dummy >> pos.col;
	return (pos);
}

void Terminal::restoreCursorPosition()
{
	this->setCursorPosition(this->_currentPos);
}

void Terminal::_updateLimits()
{
	struct winsize size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	terminal._limits.col = size.ws_col;
	terminal._limits.row = size.ws_row;
	terminal._updatePosition();
}

void Terminal::_sigwinchHandler(int /*signal*/)
{
	terminal._updateLimits();
}

int Terminal::getColumns() const
{
	return (this->_limits.col);
}

int Terminal::getRows() const
{
	return (this->_limits.row);
}

void Terminal::increment(int number)
{
	this->_currentPos.col += number;
	this->_currentPos.row += this->_currentPos.col / this->_limits.col;
	this->_currentPos.col %= this->_limits.col;

	if (this->_currentPos.row >= this->_limits.row)
	{
		this->_currentPos.row = this->_limits.row;
	}
}
