#include "custom_buffer.hpp"
#include "terminal.hpp"

#include <iostream>
#include <unistd.h>

CustomBuffer::CustomBuffer()
{
	buffer.resize(10);
	printf("CustomBuffer constructor\n");
	//setp(buffer.data(), buffer.data() + buffer.size() - 1);
}

CustomBuffer::~CustomBuffer()
{
//	this->displayBuffer();
}

CustomBuffer::int_type CustomBuffer::overflow(int_type ch)
{
	if (ch != traits_type::eof())
	{
	//	if (pptr() == epptr())
	//	{
		//	displayBuffer();
	//	}

		//*pptr() = static_cast<char>(ch);
		write(1, &ch, 1);
		//pbump(1);
		if (ch == '\n')
		{
		//	displayBuffer();
		}

		return ch;
	}
//	displayBuffer();

	return traits_type::eof();
}

CustomBuffer::int_type CustomBuffer::sync()
{
//	write(1, "sync\n", 5);
//	displayBuffer();
	return 0;
}

void CustomBuffer::displayBuffer() {
	if (pptr() > buffer.data())
  {
		//printf("%lu\n", pptr() - buffer.data());
		write(1, buffer.data(), pptr() - buffer.data());
		terminal.increment(pptr() - buffer.data());
	  setp(buffer.data(), buffer.data() + buffer.size() - 1);
	}
}
