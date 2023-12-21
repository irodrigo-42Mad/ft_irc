#ifndef CONSOLE_HPP
# define CONSOLE_HPP

# define CONSOLE_DEBUG_COLOR		"\033[35m"
# define CONSOLE_WARNING_COLOR	"\33[33m"
# define CONSOLE_ERROR_COLOR		"\33[31m"
# define CONSOLE_LOG_COLOR			"\33[32m"
# define CONSOLE_RESET_COLOR		"\033[0m"

# include <iostream>
# include <ctime>
# include <cstring>
# include <sstream>
# include <ostream>

enum LogLevel {
	LOGLEVEL_NONE,
	LOGLEVEL_LOG,
	LOGLEVEL_WARNING,
	LOGLEVEL_ERROR,
	LOGLEVEL_DEBUG
};

struct Console {
    Console(std::ostream& os, int colorCode)
    	: _os(os)
    	, _colorCode(colorCode)
    	, _colorSet(false)
		{}

    template <typename T>
    Console& operator<<(const T& value) {
        if (!this->_colorSet) {
            this->_setConsoleColor(this->_colorCode);
            this->_timestamp();	
            this->_colorSet = true;
        }

        std::ostringstream oss;
        oss << value;
        this->_os << oss.str();
        return *this;
    }

    typedef std::ostream& (*Manipulator)(std::ostream&);

    Console& operator<<(Manipulator manip) {
        if (manip == static_cast<Manipulator>(std::endl)) {
            this->_resetConsoleColor();
            this->_colorSet = false;
        }

        this->_os << manip;
        return *this;
    }

		static std::ostream& endl(std::ostream& os) {
        // Lógica personalizada si es necesario
        std::cout << "Manipulador personalizado\n";
        // Llamada al manipulador proporcionado
        os.put(os.widen('\n'));  // Carácter de nueva línea
        os.flush();              // Flushear el búfer
        return os;
    }

		static std::ostream& color(std::ostream& os, int num) {
				os << "\033[" << num << "m";
				return os;
		}


		static std::ostream& reset(std::ostream& os) {
				os << "\033[0m";
				return os;
		}

    static Console debug;
    static Console log;
    static Console warning;
    static Console error;

private:
    std::ostream& _os;
    int _colorCode;
    bool _colorSet;

    void _setConsoleColor(int colorCode) {
        this->_os << "\033[" << colorCode << "m";
    }

    void _resetConsoleColor() {
        this->_os << "\033[0m";
    }

		void _timestamp() {
			struct tm *timeinfo;
			time_t now;
			char buffer[12];

			now = time(NULL);
			timeinfo = localtime(&now);

			strftime(buffer, sizeof(buffer), "[%H:%M:%S] ", timeinfo);
			this->_os << buffer;
		} 
};


Console Console::debug(std::cout, 36);
Console Console::log(std::cout, 32);
Console Console::warning(std::cout, 33);
Console Console::error(std::cout, 31);

#endif
