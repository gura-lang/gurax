//==============================================================================
// Stream.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream
//------------------------------------------------------------------------------
Stream& Stream::Print(const char* str)
{
	return *this;
}
	
Stream& Stream::Println(const char* str)
{
	return *this;
}

Stream& Stream::PrintfV(const char* format, va_list ap)
{
	FormatterEx formatter(*this);
	formatter.DoFormat(format, ap);
	return *this;
}

Stream& Stream::Printf(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	return PrintfV(format, ap);
}

Stream& Stream::PrintFmt(const char* format, const ObjectList& objectList)
{
	FormatterEx formatter(*this);
	formatter.DoFormat(format, objectList);
	return *this;
}

bool Stream::ReadLine(String& str, bool includeEOLFlag)
{
	return false;
}

bool Stream::ReadLines(StringList& strList, bool includeEOLFlag)
{
	return false;
}

void Stream::Dump(const void* buff, size_t bytes, bool upperFlag)
{
}

}
