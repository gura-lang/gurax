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
		pObjMap->Set(Symbol::Add("foo3"), Object::nil());
		pObjMap->Set(Symbol::Add("foo4"), Object::true_());
		pObjMap->Set(Symbol::Add("foo5"), Object::false_());
		pObjMap->Set(Symbol::Add("foo6"), new Object_string("6"));
		pObjMap->Set(Symbol::Add("foo7"), new Object_number(7));
		pObjMap->Set(Symbol::Add("foo8"), Object::undefined());
		pObjMap->Set(Symbol::Add("foo9"), Object::zero());
		pObjMap->Set(Symbol::Add("fooA"), Object::emptystr());
		pObjMap->Print();
	} while (0);
	do {
		Object *pObj = new Object_number(1);
		::printf("%d %d %d %d\n",
				 pObj->IsType<Object_bool>(),
				 pObj->IsType<Object_number>(),
				 pObj->IsType<Object_string>(),
				 pObj->IsInstanceOf<Object>());
	} while (0);
}

}
