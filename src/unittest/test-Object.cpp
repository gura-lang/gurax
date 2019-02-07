//==============================================================================
// test-Object.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

void Test_ObjectMap()
{
	RefPtr<ObjectMap> pObjMap(new ObjectMap());
	pObjMap->Assign(Symbol::Add("foo1"), new Object_Number(1));
	pObjMap->Assign(Symbol::Add("foo2"), new Object_Number(2));
	pObjMap->Assign(Symbol::Add("foo3"), Object::nil());
	pObjMap->Assign(Symbol::Add("foo4"), Object::true_());
	pObjMap->Assign(Symbol::Add("foo5"), Object::false_());
	pObjMap->Assign(Symbol::Add("foo6"), new Object_String("6"));
	pObjMap->Assign(Symbol::Add("foo7"), new Object_Number(7));
	pObjMap->Assign(Symbol::Add("foo8"), Object::undefined());
	pObjMap->Assign(Symbol::Add("foo9"), Object::zero());
	pObjMap->Assign(Symbol::Add("fooA"), Object::emptystr());
	std::cout << pObjMap->ToString();
}

void Test_IsType()
{
	auto func = [](const Object* pObj) {
		::printf("%-12s %d %d %d %d\n",
				 pObj->GetKlass().GetName(),
				 pObj->IsInstanceOf(Klass_object),
				 pObj->IsType(Klass_Bool),
				 pObj->IsType(Klass_Number),
				 pObj->IsType(Klass_String));
	};
	func(new Object_Bool(true));
	func(new Object_Number(1));
	func(new Object_String(""));
}

void Test_Sort()
{
	RefPtr<ObjectOwner> pObjectOwner(new ObjectOwner());
	for (const SampleRecord* pSampleRecord = SampleRecord::tbl;
								 pSampleRecord->name; ++pSampleRecord) {
		pObjectOwner->push_back(new Object_String(pSampleRecord->name));
	}
	std::cout << pObjectOwner->ToString();
	pObjectOwner->Sort();
	for (auto pObject : *pObjectOwner) std::cout << pObject->ToString();
	pObjectOwner->Sort(SortOrder::Descend);
	for (auto pObject : *pObjectOwner) std::cout << pObject->ToString();
}

void Test_Dict()
{
	RefPtr<ObjectDict> pObjectDict(new ObjectDict());
	for (const SampleRecord* pSampleRecord = SampleRecord::tbl;
								 pSampleRecord->name; ++pSampleRecord) {
		pObjectDict->Assign(new Object_String(pSampleRecord->name), new Object_String(pSampleRecord->email));
	}
	std::cout << pObjectDict->ToString();
	for (const SampleRecord* pSampleRecord = SampleRecord::tbl;
								 pSampleRecord->name; ++pSampleRecord) {
		RefPtr<Object> pObjectKey(new Object_String(pSampleRecord->name));
		Object* pObject = pObjectDict->Lookup(pObjectKey.get());
		::printf("%s: %s\n", pObjectKey->ToString().c_str(), pObject->ToString().c_str());
	}
}

Gurax_TesterEntry(Object)
{
	Test_ObjectMap();
	Test_IsType();
	Test_Sort();
	Test_Dict();
}

}
