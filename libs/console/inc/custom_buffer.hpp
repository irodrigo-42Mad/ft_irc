#ifndef CUSTOM_BUFFER_HPP
# define CUSTOM_BUFFER_HPP

# include <ostream>

struct CustomBuffer : public std::streambuf
{
		CustomBuffer();
		~CustomBuffer();

protected:
		virtual int_type overflow(int_type ch);
		virtual int_type sync();

};

#endif
