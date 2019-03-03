//==============================================================================
// guraxcore.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

void Bootup()
{
	Attribute::Bootup();
	Binary::Bootup();
	Codec::Bootup();
	DeclCallable::Bootup();
	Error::Bootup();
	Operators::Bootup();
	Random::Bootup();
	String::Bootup();
	Stream::Bootup();
	Symbol::Bootup();
	Template::Bootup();
	Token::Bootup();
	Value::Bootup();
}

}
