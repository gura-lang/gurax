//==============================================================================
// guraxcore.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

void Initialize(int argc, char** argv)
{
	Symbol::Bootup();	// must be at first
	Attribute::Bootup();
	Binary::Bootup();
	Codec::Bootup();
	DeclCallable::Bootup();
	DeclArg::Bootup();
	Error::Bootup();
	Expr::Bootup();
	Function::Bootup();
	Operators::Bootup();
	Random::Bootup();
	String::Bootup();
	Stream::Bootup();
	Template::Bootup();
	Token::Bootup();
	Basement::Inst.Initialize(argc, argv);
}

}
