//==============================================================================
// guraxcore.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

void Bootup()
{
	Binary::Bootup();
	Error::Bootup();
	Object::Bootup();
	Random::Bootup();
	String::Bootup();
	Symbol::Bootup();
	Token::Bootup();
}

}
