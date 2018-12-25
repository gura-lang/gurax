//==============================================================================
// test-Object.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_TesterEntry(Object)
{
	do {
		RefPtr<ObjectMap> pObjMap(new ObjectMap());
		pObjMap->Set(Symbol::Add("foo1"), new Object_number(1));
		pObjMap->Set(Symbol::Add("foo2"), new Object_number(2));
		pObjMap->Set(Symbol::Add("foo3"), new Object_number(3));
		pObjMap->Set(Symbol::Add("foo4"), new Object_number(4));
		pObjMap->Set(Symbol::Add("foo5"), new Object_number(5));
		pObjMap->Set(Symbol::Add("foo6"), new Object_number(6));
		pObjMap->Set(Symbol::Add("foo7"), new Object_number(7));
		pObjMap->Set(Symbol::Add("foo8"), new Object_number(8));
		pObjMap->Set(Symbol::Add("foo9"), new Object_number(9));
		auto keys = pObjMap->GetKeys(SortOrder::Descend);
		for (const Symbol* pSymbol : keys) {
			Object* pObj = pObjMap->Get(pSymbol);
			::printf("%s %s\n", pSymbol->GetName(), pObj->GetTypeInfo().GetName());
		}
	} while (0);
}

}
