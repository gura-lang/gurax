//==============================================================================
// Object.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object
//------------------------------------------------------------------------------
const Object *Object::_pObject_undefined	= nullptr;
const Object *Object::_pObject_nil			= nullptr;
const Object *Object::_pObject_false_		= nullptr;
const Object *Object::_pObject_true_		= nullptr;
const Object *Object::_pObject_zero			= nullptr;
const Object *Object::_pObject_emptystr		= nullptr;

void Object::Bootup()
{
	Frame* pFrame = Context::GetFrame();
	VType_Object.Prepare(pFrame);
	VType_Any.Prepare(pFrame);
	VType_Argument.Prepare(pFrame);
	VType_Attribute.Prepare(pFrame);
	VType_Binary.Prepare(pFrame);
	VType_Bool.Prepare(pFrame);
	VType_DateTime.Prepare(pFrame);
	VType_Dict.Prepare(pFrame);
	VType_Expr.Prepare(pFrame);
	VType_Function.Prepare(pFrame);
	VType_Iterator.Prepare(pFrame);
	VType_VType.Prepare(pFrame);
	VType_List.Prepare(pFrame);
	VType_Module.Prepare(pFrame);
	VType_Nil.Prepare(pFrame);
	VType_Number.Prepare(pFrame);
	VType_Stream.Prepare(pFrame);
	VType_String.Prepare(pFrame);
	VType_StringPtr.Prepare(pFrame);
	VType_Symbol.Prepare(pFrame);
	VType_Template.Prepare(pFrame);
	VType_TimeDelta.Prepare(pFrame);
	VType_Undefined.Prepare(pFrame);
	_pObject_undefined	= new Object_Undefined();
	_pObject_nil		= new Object_Nil();
	_pObject_false_		= new Object_Bool(false);
	_pObject_true_		= new Object_Bool(true);
	_pObject_zero		= new Object_Number(0);
	_pObject_emptystr	= new Object_String("");
}

bool Object::GetBool() const
{
	return !(IsUndefined() || IsNil() ||
			 (IsType(VType_Bool) && !dynamic_cast<const Object_Bool*>(this)->GetBool()));
}

bool Object::IsInstanceOf(const VType& vtype) const
{
	for (const VType *pVType = &GetVType(); pVType != nullptr; pVType = &pVType->GetVTypeInherited()) {
		if (pVType->IsIdentical(vtype)) return true;
	}
	return false;
}

bool Object::Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%d qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Object::Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%u qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Object::Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%b qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Object::Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%o qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Object::Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%x qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Object::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%e qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Object::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%f qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Object::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%g qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

bool Object::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, ToString().c_str(), formatterFlags.precision);
}

bool Object::Format_c(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%c qualifier",
				 GetVType().MakeFullName().c_str());
	return false;
}

//------------------------------------------------------------------------------
// ObjectList
//------------------------------------------------------------------------------
ObjectList& ObjectList::Sort(SortOrder sortOrder)
{
	SortListByOrder<ObjectList, Object::LessThan, Object::GreaterThan>(*this, sortOrder);
	return *this;
}

String ObjectList::ToString(const StringStyle& ss) const
{
	String str;
	str += "[";
	for (auto ppObject = begin(); ppObject != end(); ++ppObject) {
		if (ppObject != begin()) str += ss.GetComma();
		str += (*ppObject)->ToString(ss);
	}
	str += "]";
	return str;
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
	RefPtr<ObjectOwner> pObjectOwner(new ObjectOwner());
	pObjectOwner->reserve(size());
	for (Object* pObject : *this) pObjectOwner->push_back(pObject->Reference());
	return pObjectOwner.release();
}

ObjectOwner* ObjectOwner::CloneDeep() const
{
	RefPtr<ObjectOwner> pObjectOwner(new ObjectOwner());
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
// ObjectTypedOwner
//------------------------------------------------------------------------------
ObjectTypedOwner::ObjectTypedOwner() :
	_pVTypeOfElems(&VType_Undefined), _pObjectOwner(new ObjectOwner())
{}

void ObjectTypedOwner::Clear()
{
	_pVTypeOfElems = &VType_Undefined;
	_pObjectOwner->Clear();
}

void ObjectTypedOwner::UpdateVTypeOfElems(VType& vtypeAdded)
{
	if (_pVTypeOfElems->IsIdentical(VType_Undefined)) {
		_pVTypeOfElems = &vtypeAdded;
	} else if (!_pVTypeOfElems->IsIdentical(vtypeAdded)) {
		_pVTypeOfElems = &VType_Any;
	}
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

String ObjectMap::ToString(const StringStyle& ss) const
{
	String str;
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		Object* pObject = Lookup(pSymbol);
		str += pSymbol->GetName();
		str += ":";
		str += pObject->GetVType().MakeFullName().c_str();
		str += " = ";
		str += pObject->ToString();
		str += "\n";
	}
	return str;
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
	RefPtr<ObjectDict> pObjectDict(new ObjectDict());
	pObjectDict->reserve(size());
	for (auto pair : *this) {
		pObjectDict->emplace(pair.first->Reference(), pair.second->Reference());
	}
	return pObjectDict.release();
}

ObjectDict* ObjectDict::CloneDeep() const
{
	RefPtr<ObjectDict> pObjectDict(new ObjectDict());
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

String ObjectDict::ToString(const StringStyle& ss) const
{
	const char* strPair = ss.IsCram()? "=>" : " => ";
	RefPtr<ObjectOwner> pKeys(GetKeys());
	pKeys->Sort();
	String str;
	str += "{";
	for (auto ppObjectKey = pKeys->begin(); ppObjectKey != pKeys->end(); ppObjectKey++) {
		const Object* pObjectKey = *ppObjectKey;
		Object* pObject = Lookup(pObjectKey);
		if (ppObjectKey != pKeys->begin()) str += ss.GetComma();
		str += pObjectKey->ToString(ss);
		str += strPair;
		str += pObject->ToString(ss);
	}
	str += "}";
	return str;
}

}
