#include "custom_buffer.hpp"
#include "terminal.hpp"

#include <iostream>
#include <unistd.h>

CustomBuffer::CustomBuffer()
{
	char* buffer = new char[100];
	setp(buffer, buffer + 100);
}

CustomBuffer::~CustomBuffer()
{
	delete[] pbase();
}

CustomBuffer::int_type CustomBuffer::overflow(int_type ch)
{
	this->sync();
	if (ch != traits_type::eof())
	{
		*pptr() = static_cast<char>(ch);
		pbump(1);
	}

	return traits_type::not_eof(ch);
}

CustomBuffer::int_type CustomBuffer::sync()
{
	write(0, pbase(), gptr() - pbase());
	terminal.increment(gptr() - pbase());
	setp(pbase(), epptr());
	return (0);
}
