//==============================================================================
// VType_Index.h
//==============================================================================
#ifndef GURAX_VTYPE_INDEX_H
#define GURAX_VTYPE_INDEX_H
#include "VType_Object.h"
#include "Index.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Index
//------------------------------------------------------------------------------
class VType_Index : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Index VTYPE_Index;

//------------------------------------------------------------------------------
// Value_Index
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Index : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Index);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Index");
protected:
	RefPtr<Index> _pIndex;
public:
	// Constructor
	Value_Index() = delete;
	Value_Index(Index* pIndex, VType& vtype = VTYPE_Index) :
		Value_Object(vtype), _pIndex(pIndex) {}
	// Copy constructor/operator
	Value_Index(const Value_Index& src) :
		Value_Object(src), _pIndex(src._pIndex->Reference()) {}
	Value_Index& operator=(const Value_Index& src) = delete;
	// Move constructor/operator
	Value_Index(Value_Index&& src) = delete;
	Value_Index& operator=(Value_Index&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Index() = default;
public:
	Index& GetIndex() { return *_pIndex; }
	const Index& GetIndex() const { return *_pIndex; }
public:
	static Index& GetIndex(Value& value) {
		return dynamic_cast<Value_Index&>(value).GetIndex();
	}
	static const Index& GetIndex(const Value& value) {
		return dynamic_cast<const Value_Index&>(value).GetIndex();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetIndex().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetIndex().IsEqualTo(dynamic_cast<const Value_Index*>(pValue)->GetIndex());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetIndex().IsLessThan(dynamic_cast<const Value_Index*>(pValue)->GetIndex()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetIndex().ToString(ss);
	}
};

}

#endif
