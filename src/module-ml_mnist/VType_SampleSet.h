//==============================================================================
// VType_SampleSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_MNIST_VTYPE_SampleSet_H
#define GURAX_MODULE_ML_MNIST_VTYPE_SampleSet_H
#include <gurax.h>
#include "SampleSet.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// VType_SampleSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SampleSet : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SampleSet VTYPE_SampleSet;

//------------------------------------------------------------------------------
// Value_SampleSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SampleSet : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SampleSet);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SampleSet");
protected:
	RefPtr<SampleSet> _pSampleSet;
public:
	static VType& vtype;
public:
	// Constructor
	Value_SampleSet() = delete;
	explicit Value_SampleSet(SampleSet* pSampleSet, VType& vtype = VTYPE_SampleSet) :
		Value_Object(vtype), _pSampleSet(pSampleSet) {}
	// Copy constructor/operator
	Value_SampleSet(const Value_SampleSet& src) :
		Value_Object(src), _pSampleSet(src._pSampleSet->Reference()) {}
	Value_SampleSet& operator=(const Value_SampleSet& src) = delete;
	// Move constructor/operator
	Value_SampleSet(Value_SampleSet&& src) noexcept = delete;
	Value_SampleSet& operator=(Value_SampleSet&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SampleSet() = default;
public:
	SampleSet& GetSampleSet() { return *_pSampleSet; }
	const SampleSet& GetSampleSet() const { return *_pSampleSet; }
public:
	static SampleSet& GetSampleSet(Value& value) {
		return dynamic_cast<Value_SampleSet&>(value).GetSampleSet();
	}
	static const SampleSet& GetSampleSet(const Value& value) {
		return dynamic_cast<const Value_SampleSet&>(value).GetSampleSet();
	}
	static SampleSet* GetEntityPtr(Value& value) { return &GetSampleSet(value); }
	static const SampleSet* GetEntityPtr(const Value& value) { return &GetSampleSet(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetSampleSet().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetSampleSet().IsEqualTo(Value_SampleSet::GetSampleSet(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetSampleSet().IsLessThan(Value_SampleSet::GetSampleSet(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml_mnist)

#endif
