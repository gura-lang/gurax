//==============================================================================
// Object.h
//==============================================================================
#ifndef GURAX_OBJECT_H
#define GURAX_OBJECT_H
#include "Klass.h"

namespace Gurax {

class Formatter;
class FormatterFlags;

//------------------------------------------------------------------------------
// Object
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object : public Referable {
public:
	// Algorithm operators
	struct EqualTo {
		size_t operator()(const Object* pValue1, const Object* pValue2) const {
			return pValue1->IsEqualTo(pValue2);
		}
	};
	struct LessThan {
		size_t operator()(const Object* pValue1, const Object* pValue2) const {
			return pValue1->IsLessThan(pValue2);
		}
	};
	struct GreaterThan {
		size_t operator()(const Object* pValue1, const Object* pValue2) const {
			return pValue2->IsLessThan(pValue1);
		}
	};
	struct Hash {
		size_t operator()(const Object* pValue) const {
			return pValue->CalcHash();
		}
	};
public:
	// Referable declaration
	Gurax_DeclareReferable(Object);
private:
	static const Object* _pValue_undefined;
	static const Object* _pValue_nil;
	static const Object* _pValue_false_;
	static const Object* _pValue_true_;
	static const Object* _pValue_zero;
	static const Object* _pValue_emptystr;
protected:
	VType* _pVType;
public:
	// Constructor
	Object() = delete;
	explicit Object(VType& vtype) : _pVType(&vtype) {}
	// Copy constructor/operator
	Object(const Object& src) : _pVType(src._pVType) {}
	Object& operator=(const Object& src) = delete;
	// Move constructor/operator
	Object(Object&& src) : _pVType(src._pVType) {}
	Object& operator=(Object&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Object() = default;
public:
	VType& GetVType() { return *_pVType; }
	const VType& GetVType() const { return *_pVType; }
	size_t CalcHash() const { return DoCalcHash(); }
	bool IsIdentical(const Object* pValue) const { return this == pValue; }
	bool IsUndefined() const { return IsIdentical(_pValue_undefined); }
	bool IsNil() const { return IsIdentical(_pValue_nil); }
	bool GetBool() const;
	static bool IsIdentical(const Object* pValue1, const Object* pValue2) {
		return pValue1? pValue1->IsIdentical(pValue2) : (!pValue1 && !pValue2);
	}
	bool IsSameType(const Object* pValue) const { return GetVType().IsIdentical(pValue->GetVType()); }
	static bool IsSameType(const Object* pValue1, const Object* pValue2) {
		return pValue1 && pValue1->IsSameType(pValue2);
	}
	bool IsType(const VType& vtype) const { return GetVType().IsIdentical(vtype); }
	static bool IsType(const Object* pValue, const VType& vtype) { return pValue && pValue->IsType(vtype); }
	bool IsInstanceOf(const VType& vtype) const;
	static bool IsInstanceOf(const Object* pValue, const VType& vtype) { return pValue && pValue->IsInstanceOf(vtype); }
	String ToString() const { return ToString(StringStyle::Empty); }
public:
	// Virtual functions
	virtual Frame* ProvideFrame() { return nullptr; }
	virtual Object* Clone() const = 0;
	virtual size_t DoCalcHash() const = 0;
	virtual bool IsEqualTo(const Object* pValue) const = 0;
	virtual bool IsLessThan(const Object* pValue) const = 0;
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
	bool IsMutable() const { return GetVType().IsMutable(); }
	bool IsImmutable() const { return GetVType().IsImmutable(); }
public:
	static void Bootup();
	static Object* undefined()	{ return _pValue_undefined->Reference(); }
	static Object* nil()		{ return _pValue_nil->Reference(); }
	static Object* false_()		{ return _pValue_false_->Reference(); }
	static Object* true_()		{ return _pValue_true_->Reference(); }
	static Object* zero()		{ return _pValue_zero->Reference(); }
	static Object* emptystr()	{ return _pValue_emptystr->Reference(); }
};

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
	void Set(size_t pos, Object* pValue);
	Object* Get(size_t pos) const { return at(pos); }
public:
	template<typename T_Map> static ObjectOwner* CollectKeys(const T_Map& map);
};

template<typename T_Map>
ObjectOwner* ObjectOwner::CollectKeys(const T_Map& map)
{
	RefPtr<ObjectOwner> pValueOwner(new ObjectOwner());
	pValueOwner->reserve(map.size());
	for (auto& pair : map) pValueOwner->push_back(pair.first->Reference());
	return pValueOwner.release();
}

//------------------------------------------------------------------------------
// ObjectTypedOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectTypedOwner : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ObjectTypedOwner);
private:
	VType* _pVTypeOfElems;	// set to "undefined", "any" or the other specific class
	RefPtr<ObjectOwner> _pValueOwner;
public:
	// Constructor
	ObjectTypedOwner();
	ObjectTypedOwner(VType *pVTypeOfElems, ObjectOwner* pValueOwner) :
		_pVTypeOfElems(pVTypeOfElems), _pValueOwner(pValueOwner) {}
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
		return new ObjectTypedOwner(_pVTypeOfElems, _pValueOwner->CloneDeep());
	}
	void Reserve(size_t size) { _pValueOwner->reserve(size); }
	void Set(size_t pos, Object* pValue) {
		UpdateVTypeOfElems(pValue->GetVType());
		_pValueOwner->Set(pos, pValue);
	}
	Object* Get(size_t pos) const { return _pValueOwner->Get(pos); }
	void Add(Object* pValue) {
		UpdateVTypeOfElems(pValue->GetVType());
		_pValueOwner->push_back(pValue);
	}
	void UpdateVTypeOfElems(VType& vtypeAdded);
	const ObjectOwner& GetObjectOwner() const { return *_pValueOwner; }
};

//------------------------------------------------------------------------------
// ObjectStack
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectStack : public ObjectOwner {
public:
	Object* Peek(int offset) { return *(rbegin() + offset); }
	void Push(Object* pValue) { push_back(pValue); }
	Object* Pop() { Object* pValue = back(); pop_back(); return pValue; }
};

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
	void Assign(const Symbol* pSymbol, Object* pValue);
	Object* Lookup(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
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
	void Assign(Object* pValueKey, Object* pValue);
	Object* Lookup(const Object* pValueKey) const {
		auto pPair = find(const_cast<Object*>(pValueKey));
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Object* pValueKey) const { return find(const_cast<Object*>(pValueKey)) != end(); }
	ObjectOwner* GetKeys() const { return ObjectOwner::CollectKeys(*this); }
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ObjectDict& objectDict) const { return this == &objectDict; }
	bool IsEqualTo(const ObjectDict& objectDict) const { return IsIdentical(objectDict); }
	bool IsLessThan(const ObjectDict& objectDict) const { return this < &objectDict; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
