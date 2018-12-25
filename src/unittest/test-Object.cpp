//==============================================================================
// test-Object.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_TesterEntry(Object)
{
	RefPtr<ObjectMap> pObjMap(new ObjectMap());
	//pObjMap->emplace(Symbol::Add("hoge"), new Object_number(3));
}

}
