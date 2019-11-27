//==============================================================================
// VType_Dict.h
//==============================================================================
#ifndef GURAX_VTYPE_DICT_H
#define GURAX_VTYPE_DICT_H
#include "VType_Object.h"
#include "ValueDict.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Dict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Dict : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Dict VTYPE_Dict;

//------------------------------------------------------------------------------
// Value_Dict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Dict : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Dict);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Dict");
protected:
	RefPtr<ValueDict> _pValueDict;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_Dict(VType& vtype = VTYPE_Dict) :
		Value_Dict(new ValueDict(), vtype) {}
	explicit Value_Dict(ValueDict* pValueDict, VType& vtype = VTYPE_Dict) :
		Value_Object(vtype), _pValueDict(pValueDict) {}
	// Copy constructor/operator
	Value_Dict(const Value_Dict& src) :
		Value_Object(src), _pValueDict(src._pValueDict->CloneDeep()) {}
	Value_Dict& operator=(const Value_Dict& src) = delete;
	// Move constructor/operator
	Value_Dict(Value_Dict&& src) = delete;
	Value_Dict& operator=(Value_Dict&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Dict() = default;
public:
	ValueDict& GetValueDict() { return *_pValueDict; }
	const ValueDict& GetValueDict() const { return *_pValueDict; }
public:
	static ValueDict& GetValueDict(Value& value) {
		return dynamic_cast<Value_Dict&>(value).GetValueDict();
	}
	static const ValueDict& GetValueDict(const Value& value) {
		return dynamic_cast<const Value_Dict&>(value).GetValueDict();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return new Value_Dict(*this); }
	virtual size_t DoCalcHash() const override { return GetValueDict().CalcHash(); }
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetValueDict().IsEqualTo(dynamic_cast<const Value_Dict*>(pValue)->GetValueDict());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetValueDict().IsLessThan(dynamic_cast<const Value_Dict*>(pValue)->GetValueDict()) :
			GetVType().IsLessThan(pValue->GetVType());
		
	}
	virtual String ToStringDigest(const StringStyle& ss) const override;
	virtual String ToStringDetail(const StringStyle& ss) const override;
public:
	virtual Value* DoIndexGet(const Index& index) const override;
	virtual void DoIndexSet(const Index& index, Value* pValue) override;
	virtual void DoIndexOpApply(const Index& index, const Value& value, const Operator& op) override;
};

}

#endif
