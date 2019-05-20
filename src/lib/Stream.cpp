//==============================================================================
// Stream.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream
//------------------------------------------------------------------------------
RefPtr<Stream> Stream::Dumb;
RefPtr<Stream> Stream::CIn;
RefPtr<Stream> Stream::COut;
RefPtr<Stream> Stream::CErr;

void Stream::Bootup()
{
	Dumb.reset(new Stream_Dumb());
	CIn.reset(new Stream_File(stdin, false, "CIn"));
	COut.reset(new Stream_File(stdout, false, "COut"));
	CErr.reset(new Stream_File(stderr, false, "CErr"));
}

Stream& Stream::Print(const char* str)
{
	for (const char* p = str; *p != '\0'; ++p) PutChar(*p);
	return *this;
}

Stream& Stream::Print(StringPicker&& strPicker)
{
	while (const char* str = strPicker.Pick()) Print(str);
	return *this;
}

Stream& Stream::Println(const char* str)
{
	Print(str);
	PutChar('\n');
	return *this;
}

Stream& Stream::Println(StringPicker&& strPicker)
{
	Print(std::move(strPicker));
	PutChar('\n');
	return *this;
}

Stream& Stream::PrintfV(const char* format, va_list ap)
{
	FormatterEx(*this).Format(format, ap);
	return *this;
}

Stream& Stream::Printf(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	return PrintfV(format, ap);
}

Stream& Stream::PrintFmt(const char* format, const ValueList& valueList)
{
	FormatterEx(*this).Format(format, valueList);
	return *this;
}

bool Stream::ReadLine(String& str, bool includeEOLFlag)
{
	int ch = GetChar();
	if (ch < 0) return false;
	for ( ; ch >= 0; ch = GetChar()) {
		if (ch == '\n') {
			if (includeEOLFlag) str += ch;
			break;
		}
		str += ch;
	}
	return !Error::IsIssued();
}

bool Stream::ReadLines(StringList& strList, bool includeEOLFlag)
{
	for (;;) {
		String str;
		if (!ReadLine(str, includeEOLFlag)) break;
		strList.push_back(str);
	}
	return !Error::IsIssued();
}

void Stream::Dump(const void* buff, size_t bytes, const StringStyle& stringStyle)
{
	const int nCols = 16;
	int iCol = 0;
	char str[64];
	String strLine, strASCII;
	const UInt8* p = reinterpret_cast<const UInt8*>(buff);
	for (size_t i = 0; i < bytes; ++i, ++p) {
		UInt8 data = *p;
		if (iCol > 0) strLine += ' ';
		::sprintf(str, stringStyle.IsUpperCase()? "%02X" : "%02x", data);
		strLine += str;
		strASCII += (0x20 <= data && data < 0x7f)? data : '.';
		iCol++;
		if (iCol == nCols) {
			strLine += "  ";
			strLine += strASCII;
			Println(strLine.c_str());
			if (Error::IsIssued()) return;
			strLine.clear();
			strASCII.clear();
			iCol = 0;
		}
	}
	if (iCol > 0) {
		for ( ; iCol < nCols; iCol++) strLine += "   ";
		strLine += "  ";
		strLine += strASCII;
		Println(strLine.c_str());
	}
}

}
