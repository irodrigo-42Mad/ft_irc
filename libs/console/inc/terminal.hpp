#ifndef CONSOLE_SETUP_HPP
# define CONSOLE_SETUP_HPP

# include "custom_buffer.hpp"

# include <term.h>

struct Position
{
		int row;
		int col;
};

struct Terminal
{
	Terminal();
	~Terminal();

	void enableEcho();
	void disableEcho();
	void hideCursor();
	void showCursor();
	void setCursorBottom();
	void setCursorTop();
	void restoreCursorPosition();
	void clearCurrentRow();

	int getRows() const;
	int getColumns() const;

	void increment(int number);

	Position getCursorPosition() const;
	void setCursorPosition(Position position);

	CustomBuffer* getCustomBuffer();

private:
	struct termios	_originalTerm;
	struct termios	_currentTerm;
	Position				_currentPos;
	Position				_limits;

	CustomBuffer		_customBuffer;

	void _setTerm(struct termios& term);
	void _getTerm();
	void _updatePosition();

	static void _sigwinchHandler(int signal);

};

extern Terminal terminal;

#endif

