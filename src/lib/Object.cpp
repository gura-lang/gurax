//==============================================================================
// Object.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

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
// Klass
//------------------------------------------------------------------------------
Klass::SeqId Klass::_seqIdNext = 1;

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
	Klass_object.Prepare(pFrame);
	Klass_any.Prepare(pFrame);
	Klass_argument.Prepare(pFrame);
	Klass_attribute.Prepare(pFrame);
	Klass_binary.Prepare(pFrame);
	Klass_bool.Prepare(pFrame);
	Klass_datetime.Prepare(pFrame);
	Klass_dict.Prepare(pFrame);
	Klass_expr.Prepare(pFrame);
	Klass_function.Prepare(pFrame);
	Klass_iterator.Prepare(pFrame);
	Klass_klass.Prepare(pFrame);
	Klass_list.Prepare(pFrame);
	Klass_module.Prepare(pFrame);
	Klass_nil.Prepare(pFrame);
	Klass_number.Prepare(pFrame);
	Klass_stream.Prepare(pFrame);
	Klass_string.Prepare(pFrame);
	Klass_stringptr.Prepare(pFrame);
	Klass_symbol.Prepare(pFrame);
	Klass_template.Prepare(pFrame);
	Klass_timedelta.Prepare(pFrame);
	Klass_undefined.Prepare(pFrame);
	_pObject_undefined	= new Object_undefined();
	_pObject_nil		= new Object_nil();
	_pObject_zero		= new Object_number(0);
	_pObject_emptystr	= new Object_string("");
	_pObject_false_		= new Object_bool(false);
	_pObject_true_		= new Object_bool(true);
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
// Klass_object
//------------------------------------------------------------------------------
KlassT_object Klass_object("object");

void KlassT_object::DoPrepare(Frame* pFrame)
{
	SetAttrs(Flag::Immutable);
	pFrame->AssignKlass(*this);
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
	_pKlassOfElems(&Klass_undefined), _pObjectOwner(new ObjectOwner())
{}

void ObjectTypedOwner::Clear()
{
	_pKlassOfElems = &Klass_undefined;
	_pObjectOwner->Clear();
}

void ObjectTypedOwner::UpdateKlassOfElems(Klass& klassAdded)
{
	if (_pKlassOfElems->IsIdentical(Klass_undefined)) {
		_pKlassOfElems = &klassAdded;
	} else if (!_pKlassOfElems->IsIdentical(klassAdded)) {
		_pKlassOfElems = &Klass_any;
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

}
