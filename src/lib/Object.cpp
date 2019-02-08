//==============================================================================
// Object.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass
//------------------------------------------------------------------------------
Klass::SeqId Klass::_seqIdNext = 1;
Klass Klass::Empty("");

Klass::Klass(const char* name) :
	_seqId(_seqIdNext++), _pHelpProvider(new HelpProvider()), _pKlassParent(nullptr),
	_pSymbol(Symbol::Add(name)), _flags(0), _pObjectMap(new ObjectMap())
{
}

String Klass::MakeFullName() const
{
	return GetName();
}

DottedSymbol* Klass::MakeDottedSymbol() const
{
	RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol());
	pDottedSymbol->Append(GetSymbol());
	return pDottedSymbol.release();
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

String KlassMap::ToString(const StringStyle& ss) const
{
	String str;
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		const Klass* pKlass = Lookup(pSymbol);
		str += pSymbol->GetName();
		str += " = ";
		str += pKlass->MakeFullName();
		str += "\n";
	}
	return str;
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
		str += pObject->GetKlass().MakeFullName().c_str();
		str += " = ";
		str += pObject->ToString();
		str += "\n";
	}
	return str;
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
	Frame* pFrame = Context::GetFrame();
	Klass_Object.Prepare(pFrame);
	Klass_Any.Prepare(pFrame);
	Klass_Argument.Prepare(pFrame);
	Klass_Attribute.Prepare(pFrame);
	Klass_Binary.Prepare(pFrame);
	Klass_Bool.Prepare(pFrame);
	Klass_DateTime.Prepare(pFrame);
	Klass_Dict.Prepare(pFrame);
	Klass_Expr.Prepare(pFrame);
	Klass_Function.Prepare(pFrame);
	Klass_Iterator.Prepare(pFrame);
	Klass_Klass.Prepare(pFrame);
	Klass_List.Prepare(pFrame);
	Klass_Module.Prepare(pFrame);
	Klass_Nil.Prepare(pFrame);
	Klass_Number.Prepare(pFrame);
	Klass_Stream.Prepare(pFrame);
	Klass_String.Prepare(pFrame);
	Klass_StringPtr.Prepare(pFrame);
	Klass_Symbol.Prepare(pFrame);
	Klass_Template.Prepare(pFrame);
	Klass_TimeDelta.Prepare(pFrame);
	Klass_Undefined.Prepare(pFrame);
	_pObject_undefined	= new Object_Undefined();
	_pObject_nil		= new Object_Nil();
	_pObject_zero		= new Object_Number(0);
	_pObject_emptystr	= new Object_String("");
	_pObject_false_		= new Object_Bool(false);
	_pObject_true_		= new Object_Bool(true);
}

bool Object::IsInstanceOf(const Klass& klass) const
{
	for (const Klass *pKlass = &GetKlass(); pKlass != nullptr; pKlass = pKlass->GetParent()) {
		if (pKlass->IsIdentical(klass)) return true;
	}
	return false;
}

bool Object::Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%d qualifier",
				 GetKlass().MakeFullName().c_str());
	return false;
}

bool Object::Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%u qualifier",
				 GetKlass().MakeFullName().c_str());
	return false;
}

bool Object::Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%b qualifier",
				 GetKlass().MakeFullName().c_str());
	return false;
}

bool Object::Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%o qualifier",
				 GetKlass().MakeFullName().c_str());
	return false;
}

bool Object::Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%x qualifier",
				 GetKlass().MakeFullName().c_str());
	return false;
}

bool Object::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%e qualifier",
				 GetKlass().MakeFullName().c_str());
	return false;
}

bool Object::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%f qualifier",
				 GetKlass().MakeFullName().c_str());
	return false;
}

bool Object::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	Error::Issue(ErrorType::ValueError,
				 "value type %s can not be formatted with %%g qualifier",
				 GetKlass().MakeFullName().c_str());
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
				 GetKlass().MakeFullName().c_str());
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
	_pKlassOfElems(&Klass_Undefined), _pObjectOwner(new ObjectOwner())
{}

void ObjectTypedOwner::Clear()
{
	_pKlassOfElems = &Klass_Undefined;
	_pObjectOwner->Clear();
}

void ObjectTypedOwner::UpdateKlassOfElems(Klass& klassAdded)
{
	if (_pKlassOfElems->IsIdentical(Klass_Undefined)) {
		_pKlassOfElems = &klassAdded;
	} else if (!_pKlassOfElems->IsIdentical(klassAdded)) {
		_pKlassOfElems = &Klass_Any;
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
