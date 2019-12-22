//==============================================================================
// Binary.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Binary
//------------------------------------------------------------------------------
const Binary Binary::Empty("");

Binary& Binary::operator=(const Binary& src) noexcept
{
	basic_string::operator=(src);
	_writableFlag = src._writableFlag;
	return *this;
}

Binary& Binary::operator=(Binary&& src) noexcept
{
	basic_string::operator=(src);
	_writableFlag = src._writableFlag;
	return *this;
}

void Binary::Bootup()
{
}

size_t Binary::CalcHash(const UInt8* binary, size_t len)
{
	size_t hash = 0;
	for ( ; len > 0; ++binary, --len) hash = hash * 137 + *binary;
	return hash;
}

String Binary::MakeQuoted(bool surroundFlag) const
{
	String strRtn;
	char chQuote = '\'';
	if (surroundFlag) strRtn += chQuote;
	for (char ch : *this) {
		if (String::IsPrint(ch)) {
			strRtn += ch;
		} else {
			char tmp[16];
			::sprintf(tmp, "\\x%02x", static_cast<UInt8>(ch));
			strRtn += tmp;
		}
	}
	if (surroundFlag) strRtn += chQuote;
	return strRtn;
}

bool Binary::CheckWritable() const
{
	if (IsWritable()) return true;
	Error::Issue(ErrorType::AccessError, "the binary is not writable");
	return false;
}

void Binary::Dump(Stream& stream, const StringStyle& ss) const
{
	stream.Dump(data(), size(), ss);
}

//------------------------------------------------------------------------------
// BinaryList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// BinaryReferable
//------------------------------------------------------------------------------

}
