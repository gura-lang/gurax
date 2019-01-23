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
	Error::Bootup();
	Object::Bootup();
	Operators::Bootup();
	Random::Bootup();
	String::Bootup();
	Symbol::Bootup();
	Token::Bootup();
}

}
