//==============================================================================
// Binary.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Binary
//------------------------------------------------------------------------------
const Binary Binary::Empty("");

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
			::sprintf(tmp, "\\x%02x", ch);
			strRtn += tmp;
		}
	}
	if (surroundFlag) strRtn += chQuote;
	return strRtn;
}

//------------------------------------------------------------------------------
// BinaryList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// BinaryReferable
//------------------------------------------------------------------------------

}
