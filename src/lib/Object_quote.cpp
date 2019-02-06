//==============================================================================
// Object_quote.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_quote
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Object_quote::KlassEx
//------------------------------------------------------------------------------
Object_quote::KlassEx Object_quote::klass("quote");

void Object_quote::KlassEx::DoPrepare()
{
	SetAttrs(Object::klass, Flag::Immutable);
}

}
