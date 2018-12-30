//==============================================================================
// Object_list.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_list
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Object_list::KlassEx
//------------------------------------------------------------------------------
Object_list::KlassEx Object_list::klass("list");

void Object_list::KlassEx::DoPrepare()
{
	SetAttrs(Object::klass, Flag::Mutable);
}

}
