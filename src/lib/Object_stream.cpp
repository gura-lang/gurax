//==============================================================================
// Object_stream.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_stream
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Object_stream::KlassEx
//------------------------------------------------------------------------------
Object_stream::KlassEx Object_stream::klass("stream");

void Object_stream::KlassEx::DoPrepare(Frame* pFrame)
{
	SetAttrs(Object::klass, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

}
