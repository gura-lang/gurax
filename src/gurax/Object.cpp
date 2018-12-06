//==============================================================================
// Object.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object
//------------------------------------------------------------------------------
void Object::Bootup()
{
}

//------------------------------------------------------------------------------
// ObjectList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ObjectOwner
//------------------------------------------------------------------------------
void ObjectOwner::Clear()
{
	for (auto pObject : *this) Object::Delete(pObject);
	clear();
}

}
