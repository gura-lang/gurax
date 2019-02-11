//==============================================================================
// Value.h
//==============================================================================
#ifndef GURAX_VALUE_H
#define GURAX_VALUE_H
#include "VType.h"

namespace Gurax {

class Argument;
class DeclCaller;
class Formatter;
class FormatterFlags;

//------------------------------------------------------------------------------
// Value
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value : public Referable {
public:
	// Algorithm operators
	struct EqualTo {
		size_t operator()(const Value* pValue1, const Value* pValue2) const {
			return pValue1->IsEqualTo(pValue2);
		}
	};
	struct LessThan {
		size_t operator()(const Value* pValue1, const Value* pValue2) const {
			return pValue1->IsLessThan(pValue2);
		}
	};
	struct GreaterThan {
		size_t operator()(const Value* pValue1, const Value* pValue2) const {
			return pValue2->IsLessThan(pValue1);
		}
	};
	struct Hash {
		size_t operator()(const Value* pValue) const {
			return pValue->CalcHash();
		}
	};
public:
	// Referable declaration
	Gurax_DeclareReferable(Value);
private:
	static const Value* _pValue_undefined;
	static const Value* _pValue_nil;
	static const Value* _pValue_false_;
	static const Value* _pValue_true_;
	static const Value* _pValue_Zero;
	static const Value* _pValue_EmptyStr;
protected:
	VType* _pVType;
public:
	// Constructor
	Value() = delete;
	explicit Value(VType& vtype) : _pVType(&vtype) {}
	// Copy constructor/operator
	Value(const Value& src) : _pVType(src._pVType) {}
	Value& operator=(const Value& src) = delete;
	// Move constructor/operator
	Value(Value&& src) : _pVType(src._pVType) {}
	Value& operator=(Value&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Value() = default;
public:
	VType& GetVType() { return *_pVType; }
	const VType& GetVType() const { return *_pVType; }
	size_t CalcHash() const { return DoCalcHash(); }
	bool IsIdentical(const Value* pValue) const { return this == pValue; }
	bool IsUndefined() const { return IsIdentical(_pValue_undefined); }
	bool IsNil() const { return IsIdentical(_pValue_nil); }
	bool GetBool() const;
	static bool IsIdentical(const Value* pValue1, const Value* pValue2) {
		return pValue1? pValue1->IsIdentical(pValue2) : (!pValue1 && !pValue2);
	}
	bool IsSameType(const Value* pValue) const { return GetVType().IsIdentical(pValue->GetVType()); }
	static bool IsSameType(const Value* pValue1, const Value* pValue2) {
		return pValue1 && pValue1->IsSameType(pValue2);
	}
	bool IsType(const VType& vtype) const { return GetVType().IsIdentical(vtype); }
	static bool IsType(const Value* pValue, const VType& vtype) { return pValue && pValue->IsType(vtype); }
	bool IsInstanceOf(const VType& vtype) const;
	static bool IsInstanceOf(const Value* pValue, const VType& vtype) { return pValue && pValue->IsInstanceOf(vtype); }
	String ToString() const { return ToString(StringStyle::Empty); }
public:
	bool IsMutable() const { return GetVType().IsMutable(); }
	bool IsImmutable() const { return GetVType().IsImmutable(); }
public:
	static void Bootup();
public:
	static Value* undefined()	{ return _pValue_undefined->Reference(); }
	static Value* nil()			{ return _pValue_nil->Reference(); }
	static Value* false_()		{ return _pValue_false_->Reference(); }
	static Value* true_()		{ return _pValue_true_->Reference(); }
	static Value* Zero()		{ return _pValue_Zero->Reference(); }
	static Value* EmptyStr()	{ return _pValue_EmptyStr->Reference(); }
public:
	// Virtual functions
	virtual Frame* ProvideFrame() { return nullptr; }
	virtual Value* Clone() const = 0;
	virtual size_t DoCalcHash() const = 0;
	virtual bool IsEqualTo(const Value* pValue) const = 0;
	virtual bool IsLessThan(const Value* pValue) const = 0;
	virtual String ToString(const StringStyle& ss) const { return String::Empty; }
	virtual const DeclCaller& GetDeclCaller();
	virtual void DoCall(const Argument& argument);
	virtual void DoIndex(const Argument& argument);
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
};

//------------------------------------------------------------------------------
// ValueList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueList : public std::vector<Value*> {
public:
	ValueList& Sort(SortOrder sortOrder = SortOrder::Ascend);
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ValueList& valueList) const { return this == &valueList; }
	bool IsEqualTo(const ValueList& valueList) const { return IsIdentical(valueList); }
	bool IsLessThan(const ValueList& valueList) const { return this < &valueList; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ValueOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueOwner : public ValueList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ValueOwner);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ValueOwner");
protected:
	~ValueOwner() { Clear(); }
public:
	void Clear();
	ValueOwner* Clone() const;
	ValueOwner* CloneDeep() const;
	void Set(size_t pos, Value* pValue);
	Value* Get(size_t pos) const { return at(pos); }
public:
	template<typename T_Map> static ValueOwner* CollectKeys(const T_Map& map);
};

template<typename T_Map>
ValueOwner* ValueOwner::CollectKeys(const T_Map& map)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(map.size());
	for (auto& pair : map) pValueOwner->push_back(pair.first->Reference());
	return pValueOwner.release();
}

//------------------------------------------------------------------------------
// ValueTypedOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueTypedOwner : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ValueTypedOwner);
private:
	VType* _pVTypeOfElems;	// set to "undefined", "any" or the other specific class
	RefPtr<ValueOwner> _pValueOwner;
public:
	// Constructor
	ValueTypedOwner();
	ValueTypedOwner(VType *pVTypeOfElems, ValueOwner* pValueOwner) :
		_pVTypeOfElems(pVTypeOfElems), _pValueOwner(pValueOwner) {}
	// Copy constructor/operator
	ValueTypedOwner(const ValueTypedOwner& src) = delete;
	ValueTypedOwner& operator=(const ValueTypedOwner& src) = delete;
	// Move constructor/operator
	ValueTypedOwner(ValueTypedOwner&& src) = delete;
	ValueTypedOwner& operator=(ValueTypedOwner&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~ValueTypedOwner() = default;
public:
	void Clear();
	ValueTypedOwner* Clone() const;
	ValueTypedOwner* CloneDeep() const {
		return new ValueTypedOwner(_pVTypeOfElems, _pValueOwner->CloneDeep());
	}
	void Reserve(size_t size) { _pValueOwner->reserve(size); }
	void Set(size_t pos, Value* pValue) {
		UpdateVTypeOfElems(pValue->GetVType());
		_pValueOwner->Set(pos, pValue);
	}
	Value* Get(size_t pos) const { return _pValueOwner->Get(pos); }
	void Add(Value* pValue) {
		UpdateVTypeOfElems(pValue->GetVType());
		_pValueOwner->push_back(pValue);
	}
	void UpdateVTypeOfElems(VType& vtypeAdded);
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
};

//------------------------------------------------------------------------------
// ValueStack
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueStack : public ValueOwner {
public:
	Value* Peek(int offset) { return *(rbegin() + offset); }
	void Push(Value* pValue) { push_back(pValue); }
	Value* Pop() { Value* pValue = back(); pop_back(); return pValue; }
};

//------------------------------------------------------------------------------
// ValueMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueMap :
	public std::unordered_map<const Symbol*, Value*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ValueMap);
protected:
	~ValueMap() { Clear(); }
public:
	void Clear();
	void Assign(const Symbol* pSymbol, Value* pValue);
	Value* Lookup(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ValueDict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueDict :
	public std::unordered_map<Value*, Value*, Value::Hash, Value::EqualTo>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ValueDict);
protected:
	~ValueDict() { Clear(); }
public:
	void Clear();
	ValueDict* Clone() const;
	ValueDict* CloneDeep() const;
	void Assign(Value* pValueKey, Value* pValue);
	Value* Lookup(const Value* pValueKey) const {
		auto pPair = find(const_cast<Value*>(pValueKey));
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Value* pValueKey) const { return find(const_cast<Value*>(pValueKey)) != end(); }
	ValueOwner* GetKeys() const { return ValueOwner::CollectKeys(*this); }
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ValueDict& valueDict) const { return this == &valueDict; }
	bool IsEqualTo(const ValueDict& valueDict) const { return IsIdentical(valueDict); }
	bool IsLessThan(const ValueDict& valueDict) const { return this < &valueDict; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
