//==============================================================================
// guraxcore.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

void Initialize()
{
	Attribute::Bootup();
	Binary::Bootup();
	Codec::Bootup();
	DeclArg::Bootup();
	DeclCallable::Bootup();
	Error::Bootup();
	Expr::Bootup();
	Operators::Bootup();
	Random::Bootup();
	String::Bootup();
	Stream::Bootup();
	Symbol::Bootup();
	Template::Bootup();
	Token::Bootup();
	Context::GetGlobal().Prepare();
}

}
