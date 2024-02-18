#ifndef IRC_EXCEPTION_HPP
# define IRC_EXCEPTION_HPP

# include <exception>

struct IRC_Exception : public std::exception
{
	IRC_Exception(const char* message)
		: _message(message)
	{}

	virtual const char* what() const throw()
	{
		return this->_message;
	}

private:
	const char* _message;

};

#endif
