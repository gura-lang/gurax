//==============================================================================
// VType_Sample.h
//==============================================================================
#ifndef GURAX_MODULE_ML_MNIST_VTYPE_SAMPLE_H
#define GURAX_MODULE_ML_MNIST_VTYPE_SAMPLE_H
#include <gurax.h>
#include "Sample.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// VType_Sample
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Sample : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Sample VTYPE_Sample;

//------------------------------------------------------------------------------
// Value_Sample
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Sample : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Sample);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Sample");
protected:
	RefPtr<Sample> _pSample;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Sample() = delete;
	explicit Value_Sample(Sample* pSample, VType& vtype = VTYPE_Sample) :
		Value_Object(vtype), _pSample(pSample) {}
	// Copy constructor/operator
	Value_Sample(const Value_Sample& src) :
		Value_Object(src), _pSample(src._pSample->Reference()) {}
	Value_Sample& operator=(const Value_Sample& src) = delete;
	// Move constructor/operator
	Value_Sample(Value_Sample&& src) noexcept = delete;
	Value_Sample& operator=(Value_Sample&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Sample() = default;
public:
	Sample& GetSample() { return *_pSample; }
	const Sample& GetSample() const { return *_pSample; }
public:
	static Sample& GetSample(Value& value) {
		return dynamic_cast<Value_Sample&>(value).GetSample();
	}
	static const Sample& GetSample(const Value& value) {
		return dynamic_cast<const Value_Sample&>(value).GetSample();
	}
	static Sample* GetEntityPtr(Value& value) { return &GetSample(value); }
	static const Sample* GetEntityPtr(const Value& value) { return &GetSample(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetSample().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetSample().IsEqualTo(Value_Sample::GetSample(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetSample().IsLessThan(Value_Sample::GetSample(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml_mnist)

#endif
