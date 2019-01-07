//==============================================================================
// Object_binary.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_binary
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Object_binary::KlassEx
//------------------------------------------------------------------------------
Object_binary::KlassEx Object_binary::klass("binary");

void Object_binary::KlassEx::DoPrepare()
{
	SetAttrs(Object::klass, Flag::Immutable);
}

}
