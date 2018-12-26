//==============================================================================
// Object.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass
//------------------------------------------------------------------------------
String Klass::MakeFullName() const
{
	return GetName();
}

//------------------------------------------------------------------------------
// Object
//------------------------------------------------------------------------------
const Object *Object::_pObj_undefined	= nullptr;
const Object *Object::_pObj_nil			= nullptr;
const Object *Object::_pObj_zero		= nullptr;
const Object *Object::_pObj_emptystr	= nullptr;
const Object *Object::_pObj_false_		= nullptr;
const Object *Object::_pObj_true_		= nullptr;

const Object::KlassEx Object::klass;

void Object::Bootup()
{
	_pObj_undefined	= new Object_undefined();
	_pObj_nil		= new Object_nil();
	_pObj_zero		= new Object_number(0);
	_pObj_emptystr	= new Object_string("");
	_pObj_false_	= new Object_bool(false);
	_pObj_true_		= new Object_bool(true);
}

//------------------------------------------------------------------------------
// ObjectList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ObjectOwner
//------------------------------------------------------------------------------
void ObjectOwner::Clear()
{
	for (Object* pObj : *this) Object::Delete(pObj);
	clear();
}

RefPtr<ObjectOwner> ObjectOwner::Clone() const
{
	RefPtr<ObjectOwner> pObjOwner(new ObjectOwner());
	pObjOwner->reserve(size());
	for (Object* pObj : *this) pObjOwner->push_back(pObj->Reference());
	return pObjOwner;
}

RefPtr<ObjectOwner> ObjectOwner::CloneDeep() const
{
	RefPtr<ObjectOwner> pObjOwner(new ObjectOwner());
	pObjOwner->reserve(size());
	for (Object* pObj : *this) {
		Object* pObjCloned = pObj->Clone();
		if (!pObjCloned) return nullptr;
		pObjOwner->push_back(pObjCloned);
	}
	return pObjOwner;
}

void ObjectOwner::Set(size_t pos, Object* pObj)
{
	iterator ppObj = begin() + pos;
	Object::Delete(*ppObj);
	*ppObj = pObj;
}

//------------------------------------------------------------------------------
// ObjectMap
//------------------------------------------------------------------------------
void ObjectMap::Clear()
{
	for (auto& pair : *this) Object::Delete(pair.second);
	clear();
}

void ObjectMap::Set(const Symbol* pSymbol, Object* pObj)
{
	iterator pPair = find(pSymbol);
	if (pPair == end()) {
		emplace(pSymbol, pObj);
	} else {
		Object::Delete(pPair->second);
		pPair->second = pObj;
	}
}

SymbolList ObjectMap::GetKeys(SortOrder sortOrder) const
{
	SymbolList keys;
	keys.reserve(size());
	for (auto pair : *this) keys.push_back(pair.first);
	keys.Sort(sortOrder);
	return keys;
}

void ObjectMap::Print() const
{
	auto keys = GetKeys();
	for (const Symbol* pSymbol : keys) {
		Object* pObj = Get(pSymbol);
		::printf("%s:%s = %s\n", pSymbol->GetName(),
				 pObj->GetKlass().MakeFullName().c_str(), pObj->ToString().c_str());
	}
}

}
