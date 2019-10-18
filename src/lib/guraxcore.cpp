//==============================================================================
// guraxcore.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

bool Initialize(int& argc, char** argv)
{
	Symbol::Bootup(); String::Bootup();	// must be at first
	Attribute::Bootup();
	Binary::Bootup();
	Color::Bootup();
	Codec::Bootup();
	DeclCallable::Bootup();
	DeclArg::Bootup();
	Error::Bootup();
	Expr::Bootup();
	Function::Bootup();
	Random::Bootup();
	Stream::Bootup();
	//Template::Bootup();
	Token::Bootup();
	return Basement::Inst.Initialize(argc, argv);
}

}
