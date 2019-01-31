//==============================================================================
// Object.h
//==============================================================================
#ifndef GURAX_OBJECT_H
#define GURAX_OBJECT_H
#include "Function.h"
#include "Help.h"
#include "MemoryPool.h"
#include "Referable.h"
#include "Symbol.h"

namespace Gurax {

class Formatter;
class FormatterFlags;
class Frame;
class Object;
class StringStyle;

//------------------------------------------------------------------------------
// ObjectMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectMap :
	public std::unordered_map<const Symbol*, Object*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ObjectMap);
protected:
	~ObjectMap() { Clear(); }
public:
	void Clear();
	void Assign(const Symbol* pSymbol, Object* pObject);
	Object* Lookup(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Klass
//------------------------------------------------------------------------------
class Klass {
public:
	struct Flag {
		static const UInt32 None		= 0;
		static const UInt32 Mutable		= (1 << 0);
		static const UInt32 Immutable	= (0 << 0);
	};
	using SeqId = UInt32;
protected:
	SeqId _seqId;
	RefPtr<HelpProvider> _pHelpProvider;
	Klass* _pKlassParent;
	const Symbol* _pSymbol;
	UInt32 _flags;
	RefPtr<ObjectMap> _pObjectMap;
private:
	static SeqId _seqIdNext;
	static const SeqId SeqId_Invalid = 0;
public:
	// Constructor
	explicit Klass(const char* name);
	// Copy constructor/operator
	Klass(Klass& src) = delete;
	Klass& operator=(Klass& src) = delete;
	// Move constructor/operator
	Klass(Klass&& src) = delete;
	Klass& operator=(Klass&& src) noexcept = delete;
	// Destructor
	virtual ~Klass() = default;
public:
	SeqId GetSeqId() const { return _seqId; }
	void SetAttrs(UInt32 flags) { _flags = flags; }
	void SetAttrs(Klass& klassParent, UInt32 flags) {
		_pKlassParent = &klassParent;
		_flags = flags;
	}
	const HelpProvider& GetHelpProvider() const { return *_pHelpProvider; }
	Klass* GetParent() const { return _pKlassParent; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const char* GetName() const { return _pSymbol->GetName(); }
	String MakeFullName() const;
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Klass& klass) const { return this == &klass; }
	bool IsEqualTo(const Klass& klass) const { return IsIdentical(klass); }
	bool IsLessThan(const Klass& klass) const { return this < &klass; }
	Object* LookupObject(const Symbol* pSymbol) const { return _pObjectMap->Lookup(pSymbol); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(klass)"; }
public:
	void Prepare() { DoPrepare(); }
	virtual void DoPrepare() = 0;
public:
	bool IsMutable() const { return (_flags & Flag::Mutable) != 0; }
	bool IsImmutable() const { return (_flags & Flag::Mutable) == 0; }
};

//------------------------------------------------------------------------------
// Object
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object : public Referable {
public:
	// Algorithm operators
	struct EqualTo {
		size_t operator()(const Object* pObject1, const Object* pObject2) const {
			return pObject1->IsEqualTo(pObject2);
		}
	};
	struct LessThan {
		size_t operator()(const Object* pObject1, const Object* pObject2) const {
			return pObject1->IsLessThan(pObject2);
		}
	};
	struct GreaterThan {
		size_t operator()(const Object* pObject1, const Object* pObject2) const {
			return pObject2->IsLessThan(pObject1);
		}
	};
	struct Hash {
		size_t operator()(const Object* pObject) const {
			return pObject->CalcHash();
		}
	};
public:
	// Referable declaration
	Gurax_DeclareReferable(Object);
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	static const Object* _pObject_undefined;
	static const Object* _pObject_nil;
	static const Object* _pObject_zero;
	static const Object* _pObject_emptystr;
	static const Object* _pObject_false_;
	static const Object* _pObject_true_;
protected:
	Klass& _klass;
public:
	// Constructor
	Object() = delete;
	Object(Klass& klass) : _klass(klass) {}
	// Copy constructor/operator
	Object(const Object& src) = delete;
	Object& operator=(const Object& src) = delete;
	// Move constructor/operator
	Object(Object&& src) = delete;
	Object& operator=(Object&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Object() = default;
public:
	Klass& GetKlass() { return _klass; }
	const Klass& GetKlass() const { return _klass; }
	size_t CalcHash() const { return DoCalcHash(); }
	bool IsIdentical(const Object* pObject) const { return this == pObject; }
	static bool IsIdentical(const Object* pObject1, const Object* pObject2) {
		return pObject1? pObject1->IsIdentical(pObject2) : (!pObject1 && !pObject2);
	}
	bool IsSameType(const Object* pObject) const { return GetKlass().IsIdentical(pObject->GetKlass()); }
	static bool IsSameType(const Object* pObject1, const Object* pObject2) {
		return pObject1 && pObject1->IsSameType(pObject2);
	}
	template<typename T> bool IsType() const { return GetKlass().IsIdentical(T::klass); }
	template<typename T> static bool IsType(const Object* pObject) { return pObject && pObject->IsType<T>(); }
	template<typename T> bool IsInstanceOf() const;
	template<typename T> static bool IsInstanceOf(const Object* pObject) { return pObject && pObject->IsInstanceOf<T>(); }
	String ToString() const { return ToString(StringStyle::Empty); }
public:
	// Virtual functions
	virtual Object* Clone() const = 0;
	virtual size_t DoCalcHash() const = 0;
	virtual bool IsEqualTo(const Object* pObject) const = 0;
	virtual bool IsLessThan(const Object* pObject) const = 0;
	virtual String ToString(const StringStyle& ss) const { return String::Empty; }
	virtual bool Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_c(Formatter& formatter, FormatterFlags& formatterFlags) const;
public:
	bool IsMutable() const { return GetKlass().IsMutable(); }
	bool IsImmutable() const { return GetKlass().IsImmutable(); }
public:
	static void Bootup();
	static Object* nil()		{ return _pObject_nil->Reference(); }
	static Object* undefined()	{ return _pObject_undefined->Reference(); }
	static Object* zero()		{ return _pObject_zero->Reference(); }
	static Object* emptystr()	{ return _pObject_emptystr->Reference(); }
	static Object* false_()		{ return _pObject_false_->Reference(); }
	static Object* true_()		{ return _pObject_true_->Reference(); }
};

template<typename T> bool Object::IsInstanceOf() const
{
	for (const Klass *pKlass = &GetKlass(); pKlass != nullptr; pKlass = pKlass->GetParent()) {
		if (pKlass->IsIdentical(T::klass)) return true;
	}
	return false;
}

//------------------------------------------------------------------------------
// ObjectList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectList : public std::vector<Object*> {
public:
	ObjectList& Sort(SortOrder sortOrder = SortOrder::Ascend);
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ObjectList& objectList) const { return this == &objectList; }
	bool IsEqualTo(const ObjectList& objectList) const { return IsIdentical(objectList); }
	bool IsLessThan(const ObjectList& objectList) const { return this < &objectList; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ObjectOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectOwner : public ObjectList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ObjectOwner);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ObjectOwner");
protected:
	~ObjectOwner() { Clear(); }
public:
	void Clear();
	ObjectOwner* Clone() const;
	ObjectOwner* CloneDeep() const;
	void Set(size_t pos, Object* pObject);
	Object* Get(size_t pos) const { return at(pos); }
public:
	template<typename T_Map> static ObjectOwner* CollectKeys(const T_Map& map);
};

template<typename T_Map>
ObjectOwner* ObjectOwner::CollectKeys(const T_Map& map)
{
	RefPtr<ObjectOwner> pObjectOwner(new ObjectOwner());
	pObjectOwner->reserve(map.size());
	for (auto& pair : map) pObjectOwner->push_back(pair.first->Reference());
	return pObjectOwner.release();
}

//------------------------------------------------------------------------------
// ObjectTypedOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectTypedOwner : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ObjectTypedOwner);
private:
	Klass* _pKlassOfElems;	// set to "undefined", "any" or the other specific class
	RefPtr<ObjectOwner> _pObjectOwner;
public:
	// Constructor
	ObjectTypedOwner();
	ObjectTypedOwner(Klass *pKlassOfElems, ObjectOwner* pObjectOwner) :
		_pKlassOfElems(pKlassOfElems), _pObjectOwner(pObjectOwner) {}
	// Copy constructor/operator
	ObjectTypedOwner(const ObjectTypedOwner& src) = delete;
	ObjectTypedOwner& operator=(const ObjectTypedOwner& src) = delete;
	// Move constructor/operator
	ObjectTypedOwner(ObjectTypedOwner&& src) = delete;
	ObjectTypedOwner& operator=(ObjectTypedOwner&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~ObjectTypedOwner() = default;
public:
	void Clear();
	ObjectTypedOwner* Clone() const;
	ObjectTypedOwner* CloneDeep() const {
		return new ObjectTypedOwner(_pKlassOfElems, _pObjectOwner->CloneDeep());
	}
	void Set(size_t pos, Object* pObject) {
		UpdateKlassOfElems(pObject->GetKlass());
		_pObjectOwner->Set(pos, pObject);
	}
	Object* Get(size_t pos) const { return _pObjectOwner->Get(pos); }
	void Add(Object* pObject) {
		UpdateKlassOfElems(pObject->GetKlass());
		_pObjectOwner->push_back(pObject);
	}
	void UpdateKlassOfElems(Klass& klassAdded);
	const ObjectOwner& GetObjectOwner() const { return *_pObjectOwner; }
};

//------------------------------------------------------------------------------
// ObjectStack
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectStack : public ObjectOwner {
public:
	Object* Peek(int offset) { return *(rbegin() + offset); }
	void Push(Object* pObject) { push_back(pObject); }
	Object* Pop() { Object* pObject = back(); pop_back(); return pObject; }
};

//------------------------------------------------------------------------------
// ObjectDict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectDict :
	public std::unordered_map<Object*, Object*, Object::Hash, Object::EqualTo>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ObjectDict);
protected:
	~ObjectDict() { Clear(); }
public:
	void Clear();
	ObjectDict* Clone() const;
	ObjectDict* CloneDeep() const;
	void Assign(Object* pObjectKey, Object* pObject);
	Object* Lookup(const Object* pObjectKey) const {
		auto pPair = find(const_cast<Object*>(pObjectKey));
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Object* pObjectKey) const { return find(const_cast<Object*>(pObjectKey)) != end(); }
	ObjectOwner* GetKeys() const { return ObjectOwner::CollectKeys(*this); }
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ObjectDict& objectDict) const { return this == &objectDict; }
	bool IsEqualTo(const ObjectDict& objectDict) const { return IsIdentical(objectDict); }
	bool IsLessThan(const ObjectDict& objectDict) const { return this < &objectDict; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// KlassMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE KlassMap :
	public std::unordered_map<const Symbol*, Klass*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(KlassMap);
protected:
	~KlassMap() = default;
public:
	void Assign(const Symbol* pSymbol, Klass* pKlass);
	Klass* Lookup(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
