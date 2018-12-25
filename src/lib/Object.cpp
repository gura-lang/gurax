//==============================================================================
// Object.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object
//------------------------------------------------------------------------------
const Object *Object::_pObj_undefined	= nullptr;
const Object *Object::_pObj_nil			= nullptr;
const Object *Object::_pObj_zero		= nullptr;
const Object *Object::_pObj_emptystr	= nullptr;
const Object *Object::_pObj_false_		= nullptr;
const Object *Object::_pObj_true_		= nullptr;

const Object::TypeInfo Object::typeInfo(nullptr, "object");

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
	for (auto& pObj : *this) Object::Delete(pObj);
	clear();
}

RefPtr<ObjectOwner> ObjectOwner::Clone() const
{
	RefPtr<ObjectOwner> pObjOwner(new ObjectOwner());
	pObjOwner->reserve(size());
	for (auto pObj : *this) pObjOwner->push_back(pObj->Reference());
	return pObjOwner;
}

RefPtr<ObjectOwner> ObjectOwner::CloneDeep() const
{
	RefPtr<ObjectOwner> pObjOwner(new ObjectOwner());
	pObjOwner->reserve(size());
	for (auto pObj : *this) {
		Object* pObjCloned = pObj->Clone();
		if (!pObjCloned) return nullptr;
		pObjOwner->push_back(pObjCloned);
	}
	return pObjOwner;
}

//------------------------------------------------------------------------------
// ObjectMap
//------------------------------------------------------------------------------
void ObjectMap::Clear()
{
	for (auto& iter : *this) Object::Delete(iter.second);
	clear();
}

}
