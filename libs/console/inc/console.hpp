#ifndef CONSOLE_HPP
# define CONSOLE_HPP

# include "terminal.hpp"

# include <iostream>

enum LogLevel {
	LOGLEVEL_NONE,
	LOGLEVEL_LOG,
	LOGLEVEL_WARNING,
	LOGLEVEL_ERROR,
	LOGLEVEL_DEBUG
};

struct Console {
    typedef std::ostream& (*Manipulator)(std::ostream&);

		struct IDisplayManager {
			virtual void displayBottom(std::stringstream& ss, int width) = 0;
		};

    Console(std::ostream& os, const std::string& tag, int color, LogLevel logLevel);

    template <typename T>
    Console& operator<<(const T& value);
    Console& operator<<(Manipulator manip);

		/*
		static std::ostream& endl(std::ostream& os) {
        // Lógica personalizada si es necesario
        std::cout << "Manipulador personalizado\n";
        // Llamada al manipulador proporcionado
        os.put(os.widen('\n'));  // Carácter de nueva línea
        os.flush();              // Flushear el búfer
        return os;
    }
    */

		static void setLogLevel(LogLevel logLevel);	
		static void setDisplayManager(IDisplayManager* displayManager);
		static void displayBottom();

private:
    std::ostream&	_os;
		std::string		_tag;
    int						_color;
    bool					_colorSet;
    LogLevel			_logLevel;

    static IDisplayManager*	_displayManager;

    void _setColor(int color);
    void _resetColor();
		void _timestamp();

		static LogLevel logLevel;

		friend struct Terminal;
};

template <typename T>
Console& Console::operator<<(const T& value)
{
		if (Console::logLevel < this->_logLevel)
		{
			  return *this;
		}
    if (!this->_colorSet)
    {
				this->_os << "\033[K\r";
        this->_setColor(this->_color);
        this->_timestamp();	
        this->_colorSet = true;
    }
    this->_os << value;
    return *this;
}

extern Console debug;
extern Console log;
extern Console warning;
extern Console error;

#endif
