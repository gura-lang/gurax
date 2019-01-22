//==============================================================================
// Stream.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream
//------------------------------------------------------------------------------
void Stream::Print(const char* str)
{
}
	
void Stream::Println(const char* str)
{
}

void Stream::Printf(const char* format, ...)
{
}

void Stream::PrintFmt(const char* format, const ObjectList& objectList)
{
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
