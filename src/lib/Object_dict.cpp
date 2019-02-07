//==============================================================================
// Object_dict.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_dict
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Object_dict::KlassEx
//------------------------------------------------------------------------------
Object_dict::KlassEx Object_dict::klass("dict");

void Object_dict::KlassEx::DoPrepare(Frame* pFrame)
{
	SetAttrs(Object::klass, Flag::Mutable);
}

}
