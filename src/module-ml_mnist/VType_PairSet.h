//==============================================================================
// VType_PairSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_MNIST_VTYPE_PAIRSET_H
#define GURAX_MODULE_ML_MNIST_VTYPE_PAIRSET_H
#include <gurax.h>
#include "PairSet.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// VType_PairSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_PairSet : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_PairSet VTYPE_PairSet;

//------------------------------------------------------------------------------
// Value_PairSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_PairSet : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_PairSet);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_PairSet");
protected:
	RefPtr<PairSet> _pPairSet;
public:
	static VType& vtype;
public:
	// Constructor
	Value_PairSet() = delete;
	explicit Value_PairSet(PairSet* pPairSet, VType& vtype = VTYPE_PairSet) :
		Value_Object(vtype), _pPairSet(pPairSet) {}
	// Copy constructor/operator
	Value_PairSet(const Value_PairSet& src) :
		Value_Object(src), _pPairSet(src._pPairSet->Reference()) {}
	Value_PairSet& operator=(const Value_PairSet& src) = delete;
	// Move constructor/operator
	Value_PairSet(Value_PairSet&& src) noexcept = delete;
	Value_PairSet& operator=(Value_PairSet&& src) noexcept = delete;
protected:
	// Destructor
	~Value_PairSet() = default;
public:
	PairSet& GetPairSet() { return *_pPairSet; }
	const PairSet& GetPairSet() const { return *_pPairSet; }
public:
	static PairSet& GetPairSet(Value& value) {
		return dynamic_cast<Value_PairSet&>(value).GetPairSet();
	}
	static const PairSet& GetPairSet(const Value& value) {
		return dynamic_cast<const Value_PairSet&>(value).GetPairSet();
	}
	static PairSet* GetEntityPtr(Value& value) { return &GetPairSet(value); }
	static const PairSet* GetEntityPtr(const Value& value) { return &GetPairSet(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetPairSet().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetPairSet().IsEqualTo(Value_PairSet::GetPairSet(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetPairSet().IsLessThan(Value_PairSet::GetPairSet(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml_mnist)

#endif
