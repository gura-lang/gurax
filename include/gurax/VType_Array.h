//==============================================================================
// VType_Array.h
//==============================================================================
#ifndef GURAX_VTYPE_ARRAY_H
#define GURAX_VTYPE_ARRAY_H
#include "VType_Object.h"
#include "Array.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Array
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Array : public VType {
public:
	static const UInt32 SerializeId = 0x00000400;
public:
	class GURAX_DLLDECLARE Iterator_Each : public Iterator {
	private:
		RefPtr<Array> _pArray;
		size_t _idx;
		size_t _len;
	public:
		Iterator_Each(Array* pArray) : _pArray(pArray),
					_idx(0), _len(pArray->GetDimSizes().CalcLength()) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override {
			return Flag::Finite | Flag::LenDetermined;
		}
		virtual size_t GetLength() const override { return _len; }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Array VTYPE_Array;

//------------------------------------------------------------------------------
// Value_Array
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Array : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Array);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Array");
protected:
	RefPtr<Array> _pArray;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Array() = delete;
	explicit Value_Array(Array* pArray, VType& vtype = VTYPE_Array) :
		Value_Object(vtype), _pArray(pArray) {}
	// Copy constructor/operator
	Value_Array(const Value_Array& src) :
		Value_Object(src), _pArray(src._pArray->Reference()) {}
	Value_Array& operator=(const Value_Array& src) = delete;
	// Move constructor/operator
	Value_Array(Value_Array&& src) = delete;
	Value_Array& operator=(Value_Array&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Array() = default;
public:
	Array& GetArray() { return *_pArray; }
	const Array& GetArray() const { return *_pArray; }
public:
	static Array& GetArray(Value& value) {
		return dynamic_cast<Value_Array&>(value).GetArray();
	}
	static const Array& GetArray(const Value& value) {
		return dynamic_cast<const Value_Array&>(value).GetArray();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetArray().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetArray().IsEqualTo(Value_Array::GetArray(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetArray().IsLessThan(Value_Array::GetArray(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	virtual const DeclCallable* GetDeclCallable();
	virtual Value* DoEval(Processor& processor, Argument& argument) const;
	virtual Value* DoIndexGet(const Index& index) const override;
	virtual void DoIndexSet(const Index& index, RefPtr<Value> pValue) override;
	virtual bool DoEmptyIndexGet(Value** ppValue) const override;
};

}

#endif
