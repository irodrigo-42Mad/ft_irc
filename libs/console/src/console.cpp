#include "console.hpp"
#include "terminal.hpp"

#include <csignal>
#include <sstream>
#include <sys/ioctl.h>

namespace Console
{

LogLevel Console::logLevel = LOGLEVEL_NONE;

Console debug = Console(std::cout, "DEBUG", 36, LOGLEVEL_DEBUG);
Console log = Console(std::cout, "LOG", 32, LOGLEVEL_LOG);
Console warning = Console(std::cout, "WARNING", 33, LOGLEVEL_WARNING);
Console error = Console(std::cout, "ERROR", 31, LOGLEVEL_ERROR);

Console::IDisplayManager* Console::_displayManager = NULL;

Console::Console(std::ostream& os, const std::string& tag, int color, LogLevel logLevel)
	: _os(os)
	, _tag(tag)
	, _color(color)
	, _colorSet(false)
	, _logLevel(logLevel)
{
	//this->_os.rdbuf(terminal.getCustomBuffer());
}

Console& Console::operator<<(Manipulator manip)
{
	if (manip == static_cast<Manipulator>(std::endl))
	{
		terminal.clearCurrentRow();
		this->_resetColor();
		this->_colorSet = false;
	}
	this->_os << manip;
	return *this;
}

void Console::setLogLevel(LogLevel logLevel)
{
	Console::logLevel = logLevel;
}

void Console::setDisplayManager(Console::IDisplayManager* displayManager)
{
	Console::_displayManager = displayManager;
}

void Console::displayBottom()
{
	std::stringstream ss;

	Console::_displayManager->displayBottom(ss, terminal.getColumns());
	//terminal.setCursorBottom();
	terminal.clearCurrentRow();
	std::cout << ss.str().substr(0, terminal.getColumns()) << '\r';
	//terminal.restoreCursorPosition();
	std::cout << std::flush;
}

void Console::_setColor(int color)
{
	this->_os << "\033[" << color << "m";
}

void Console::_resetColor()
{
	this->_setColor(0);
}

void Console::_timestamp()
{
	struct tm *timeinfo;
	time_t now;
	char buffer[9];

	now = time(NULL);
	timeinfo = localtime(&now);

	strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
	this->_os << "[" << buffer << " " << this->_tag + "] ";
}

} // namespace Console 
