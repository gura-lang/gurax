//==============================================================================
// guraxcore.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

bool Initialize(int& argc, char** argv)
{
	Symbol::Bootup(); String::Bootup();	DottedSymbol::Bootup(); // must be at first
	Array::Bootup();
	Attribute::Bootup();
	Binary::Bootup();
	Color::Bootup();
	Codec::Bootup();
	Constructor::Bootup();
	DeclCallable::Bootup();
	DeclArg::Bootup();
	Directory::Bootup();
	Error::Bootup();
	Expr::Bootup();
	Function::Bootup();
	Half::Bootup();
	Image::Bootup();
	Iterator::Bootup();
	Memory::Bootup();
	NumberBase::Bootup();
	Operator::Bootup();
	Packer::Bootup();
	Palette::Bootup();
	Pointer::Bootup();
	Random::Bootup();
	Referencer::Bootup();
	Stream::Bootup();
	//Template::Bootup();
	Token::Bootup();
	return Basement::Inst.Initialize(argc, argv);
}

}
