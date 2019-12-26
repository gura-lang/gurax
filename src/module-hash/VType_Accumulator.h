//==============================================================================
// VType_Accumulator.h
//==============================================================================
#ifndef GURAX_MODULE_HASH_VTYPE_ACCUMULATOR_H
#define GURAX_MODULE_HASH_VTYPE_ACCUMULATOR_H
#include <gurax.h>
#include "Accumulator.h"

Gurax_BeginModuleScope(hash)

//------------------------------------------------------------------------------
// VType_Accumulator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Accumulator : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Accumulator VTYPE_Accumulator;

//------------------------------------------------------------------------------
// Value_Accumulator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Accumulator : public Value_Stream {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Accumulator);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Accumulator");
protected:
	RefPtr<Stream> _pAccumulator;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Accumulator() = delete;
	explicit Value_Accumulator(Accumulator* pAccumulator, VType& vtype = VTYPE_Accumulator) :
		Value_Stream(pAccumulator, vtype) {}
	// Copy constructor/operator
	Value_Accumulator(const Value_Accumulator& src) : Value_Stream(src) {}
	Value_Accumulator& operator=(const Value_Accumulator& src) = delete;
	// Move constructor/operator
	Value_Accumulator(Value_Accumulator&& src) = delete;
	Value_Accumulator& operator=(Value_Accumulator&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Accumulator() = default;
public:
	Accumulator& GetAccumulator() { return dynamic_cast<Accumulator&>(GetStream()); }
	const Accumulator& GetAccumulator() const { return dynamic_cast<const Accumulator&>(GetStream()); }
public:
	static Accumulator& GetAccumulator(Value& value) {
		return dynamic_cast<Value_Accumulator&>(value).GetAccumulator();
	}
	static const Accumulator& GetAccumulator(const Value& value) {
		return dynamic_cast<const Value_Accumulator&>(value).GetAccumulator();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetAccumulator().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetAccumulator().IsEqualTo(Value_Accumulator::GetAccumulator(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetAccumulator().IsLessThan(Value_Accumulator::GetAccumulator(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetAccumulator().ToString(ss);
	}
};

Gurax_EndModuleScope(hash)

#endif
