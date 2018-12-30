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
const Object *Object::_pObject_undefined	= nullptr;
const Object *Object::_pObject_nil			= nullptr;
const Object *Object::_pObject_zero			= nullptr;
const Object *Object::_pObject_emptystr		= nullptr;
const Object *Object::_pObject_false_		= nullptr;
const Object *Object::_pObject_true_		= nullptr;

void Object::Bootup()
{
	Object::klass.Prepare();
	Object_bool::klass.Prepare();
	Object_function::klass.Prepare();
	Object_nil::klass.Prepare();
	Object_number::klass.Prepare();
	Object_string::klass.Prepare();
	Object_symbol::klass.Prepare();
	Object_undefined::klass.Prepare();
	_pObject_undefined	= new Object_undefined();
	_pObject_nil		= new Object_nil();
	_pObject_zero		= new Object_number(0);
	_pObject_emptystr	= new Object_string("");
	_pObject_false_		= new Object_bool(false);
	_pObject_true_		= new Object_bool(true);
}

//------------------------------------------------------------------------------
// Object::KlassEx
//------------------------------------------------------------------------------
Object::KlassEx Object::klass("object");

void Object::KlassEx::DoPrepare()
{
	SetAttrs(Flag::Immutable);
}

//------------------------------------------------------------------------------
// ObjectList
//------------------------------------------------------------------------------
ObjectList& ObjectList::Sort(Sorter::Order order)
{
	Sorter::Sort<ObjectList, Object::LessThan, Object::GreaterThan>(*this, order);
	return *this;
}

String ObjectList::ToString(const StringStyle&) const
{
	return String::Empty;
}

//------------------------------------------------------------------------------
// ObjectOwner
//------------------------------------------------------------------------------
void ObjectOwner::Clear()
{
	for (Object* pObject : *this) Object::Delete(pObject);
	clear();
}

ObjectOwner* ObjectOwner::Clone() const
{
	RefPtr<ObjectOwner> pObjectOwner = new ObjectOwner();
	pObjectOwner->reserve(size());
	for (Object* pObject : *this) pObjectOwner->push_back(pObject->Reference());
	return pObjectOwner.release();
}

ObjectOwner* ObjectOwner::CloneDeep() const
{
	RefPtr<ObjectOwner> pObjectOwner = new ObjectOwner();
	pObjectOwner->reserve(size());
	for (Object* pObject : *this) {
		Object* pObjectCloned = pObject->Clone();
		if (!pObjectCloned) return nullptr;
		pObjectOwner->push_back(pObjectCloned);
	}
	return pObjectOwner.release();
}

void ObjectOwner::Set(size_t pos, Object* pObject)
{
	iterator ppObject = begin() + pos;
	Object::Delete(*ppObject);
	*ppObject = pObject;
}

//------------------------------------------------------------------------------
// ObjectMap
//------------------------------------------------------------------------------
void ObjectMap::Clear()
{
	for (auto& pair : *this) Object::Delete(pair.second);
	clear();
}

void ObjectMap::Assign(const Symbol* pSymbol, Object* pObject)
{
	iterator pPair = find(pSymbol);
	if (pPair == end()) {
		emplace(pSymbol, pObject);
	} else {
		Object::Delete(pPair->second);
		pPair->second = pObject;
	}
}

void ObjectMap::Print() const
{
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		Object* pObject = Lookup(pSymbol);
		::printf("%s:%s = %s\n", pSymbol->GetName(),
				 pObject->GetKlass().MakeFullName().c_str(), pObject->ToString().c_str());
	}
}

//------------------------------------------------------------------------------
// ObjectDict
//------------------------------------------------------------------------------
void ObjectDict::Clear()
{
	for (auto& pair : *this) {
		Object::Delete(pair.first);
		Object::Delete(pair.second);
	}
	clear();
}

ObjectDict* ObjectDict::Clone() const
{
	RefPtr<ObjectDict> pObjectDict = new ObjectDict();
	pObjectDict->reserve(size());
	for (auto pair : *this) {
		pObjectDict->emplace(pair.first->Reference(), pair.second->Reference());
	}
	return pObjectDict.release();
}

ObjectDict* ObjectDict::CloneDeep() const
{
	RefPtr<ObjectDict> pObjectDict = new ObjectDict();
	pObjectDict->reserve(size());
	for (auto pair : *this) {
		Object* pObjectKeyCloned = pair.first->Clone();
		if (!pObjectKeyCloned) return nullptr;
		Object* pObjectCloned = pair.second->Clone();
		if (!pObjectCloned) return nullptr;
		pObjectDict->emplace(pObjectKeyCloned, pObjectCloned);
	}
	return pObjectDict.release();
}

void ObjectDict::Assign(Object* pObjectKey, Object* pObject)
{
	iterator pPair = find(pObjectKey);
	if (pPair == end()) {
		emplace(pObjectKey, pObject);
	} else {
		Object::Delete(pPair->second);
		pPair->second = pObject;
	}
}

String ObjectDict::ToString(const StringStyle&) const
{
	return String::Empty;
}

void ObjectDict::Print() const
{
	RefPtr<ObjectOwner> pKeys = GetKeys();
	//pKeys->Sort();
	for (const Object* pObjectKey : *pKeys) {
		Object* pObject = Lookup(pObjectKey);
		::printf("%s = %s\n", pObjectKey->ToString().c_str(), pObject->ToString().c_str());
	}
}

//------------------------------------------------------------------------------
// KlassMap
//------------------------------------------------------------------------------
void KlassMap::Assign(const Symbol* pSymbol, Klass* pKlass)
{
	iterator pPair = find(pSymbol);
	if (pPair == end()) {
		emplace(pSymbol, pKlass);
	} else {
		pPair->second = pKlass;
	}
}

void KlassMap::Print() const
{
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		const Klass* pKlass = Lookup(pSymbol);
		::printf("%s = %s\n", pSymbol->GetName(), pKlass->MakeFullName().c_str());
	}
}

}
