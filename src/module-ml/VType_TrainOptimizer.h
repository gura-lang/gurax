//==============================================================================
// VType_TrainOptimizer.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_TRAINOPTIMIZER_H
#define GURAX_MODULE_ML_VTYPE_TRAINOPTIMIZER_H
#include <gurax.h>
#include "TrainOptimizer.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_TrainOptimizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_TrainOptimizer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_TrainOptimizer VTYPE_TrainOptimizer;

//------------------------------------------------------------------------------
// Value_TrainOptimizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_TrainOptimizer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_TrainOptimizer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_TrainOptimizer");
protected:
	RefPtr<TrainOptimizer> _pTrainOptimizer;
public:
	static VType& vtype;
public:
	// Constructor
	Value_TrainOptimizer() = delete;
	explicit Value_TrainOptimizer(TrainOptimizer* pTrainOptimizer, VType& vtype = VTYPE_TrainOptimizer) :
		Value_Object(vtype), _pTrainOptimizer(pTrainOptimizer) {}
	// Copy constructor/operator
	Value_TrainOptimizer(const Value_TrainOptimizer& src) :
		Value_Object(src), _pTrainOptimizer(src._pTrainOptimizer->Reference()) {}
	Value_TrainOptimizer& operator=(const Value_TrainOptimizer& src) = delete;
	// Move constructor/operator
	Value_TrainOptimizer(Value_TrainOptimizer&& src) noexcept = delete;
	Value_TrainOptimizer& operator=(Value_TrainOptimizer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_TrainOptimizer() = default;
public:
	TrainOptimizer& GetTrainOptimizer() { return *_pTrainOptimizer; }
	const TrainOptimizer& GetTrainOptimizer() const { return *_pTrainOptimizer; }
public:
	static TrainOptimizer& GetTrainOptimizer(Value& value) {
		return dynamic_cast<Value_TrainOptimizer&>(value).GetTrainOptimizer();
	}
	static const TrainOptimizer& GetTrainOptimizer(const Value& value) {
		return dynamic_cast<const Value_TrainOptimizer&>(value).GetTrainOptimizer();
	}
	static TrainOptimizer* GetEntityPtr(Value& value) { return &GetTrainOptimizer(value); }
	static const TrainOptimizer* GetEntityPtr(const Value& value) { return &GetTrainOptimizer(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetTrainOptimizer().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetTrainOptimizer().IsEqualTo(Value_TrainOptimizer::GetTrainOptimizer(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetTrainOptimizer().IsLessThan(Value_TrainOptimizer::GetTrainOptimizer(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml)

#endif
