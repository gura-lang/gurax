//==============================================================================
// VType_Step.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_STEP_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_STEP_H
#include <gurax.h>
#include "Step.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Step
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Step : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Step VTYPE_Step;

//------------------------------------------------------------------------------
// Value_Step
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Step : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Step);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Step");
protected:
	RefPtr<Step> _pStep;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Step() = delete;
	explicit Value_Step(Step* pStep, VType& vtype = VTYPE_Step) :
		Value_Object(vtype), _pStep(pStep) {}
	// Copy constructor/operator
	Value_Step(const Value_Step& src) :
		Value_Object(src), _pStep(src._pStep->Reference()) {}
	Value_Step& operator=(const Value_Step& src) = delete;
	// Move constructor/operator
	Value_Step(Value_Step&& src) noexcept = delete;
	Value_Step& operator=(Value_Step&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Step() = default;
public:
	Step& GetStep() { return *_pStep; }
	const Step& GetStep() const { return *_pStep; }
public:
	static Step& GetStep(Value& value) {
		return dynamic_cast<Value_Step&>(value).GetStep();
	}
	static const Step& GetStep(const Value& value) {
		return dynamic_cast<const Value_Step&>(value).GetStep();
	}
	static Step* GetEntityPtr(Value& value) { return &GetStep(value); }
	static const Step* GetEntityPtr(const Value& value) { return &GetStep(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetStep().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetStep().IsEqualTo(Value_Step::GetStep(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetStep().IsLessThan(Value_Step::GetStep(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
