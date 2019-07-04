//==============================================================================
// guraxcore.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

void Initialize(int argc, char** argv)
{
	Attribute::Bootup();
	Binary::Bootup();
	Codec::Bootup();
	DeclArg::Bootup();
	DeclCallable::Bootup();
	Error::Bootup();
	Expr::Bootup();
	Function::Bootup();
	Operators::Bootup();
	Random::Bootup();
	String::Bootup();
	Stream::Bootup();
	Symbol::Bootup();
	Template::Bootup();
	Token::Bootup();
	Basement::Inst.Initialize(argc, argv);
}

}
