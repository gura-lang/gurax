//==============================================================================
// VType_Optimizer.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_OPTIMIZER_H
#define GURAX_MODULE_ML_VTYPE_OPTIMIZER_H
#include <gurax.h>
#include "Optimizers.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_Optimizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Optimizer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Optimizer VTYPE_Optimizer;

//------------------------------------------------------------------------------
// Value_Optimizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Optimizer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Optimizer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Optimizer");
protected:
	RefPtr<Optimizer> _pOptimizer;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Optimizer() = delete;
	explicit Value_Optimizer(Optimizer* pOptimizer, VType& vtype = VTYPE_Optimizer) :
		Value_Object(vtype), _pOptimizer(pOptimizer) {}
	// Copy constructor/operator
	Value_Optimizer(const Value_Optimizer& src) :
		Value_Object(src), _pOptimizer(src._pOptimizer->Reference()) {}
	Value_Optimizer& operator=(const Value_Optimizer& src) = delete;
	// Move constructor/operator
	Value_Optimizer(Value_Optimizer&& src) noexcept = delete;
	Value_Optimizer& operator=(Value_Optimizer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Optimizer() = default;
public:
	Optimizer& GetOptimizer() { return *_pOptimizer; }
	const Optimizer& GetOptimizer() const { return *_pOptimizer; }
public:
	static Optimizer& GetOptimizer(Value& value) {
		return dynamic_cast<Value_Optimizer&>(value).GetOptimizer();
	}
	static const Optimizer& GetOptimizer(const Value& value) {
		return dynamic_cast<const Value_Optimizer&>(value).GetOptimizer();
	}
	static Optimizer* GetEntityPtr(Value& value) { return &GetOptimizer(value); }
	static const Optimizer* GetEntityPtr(const Value& value) { return &GetOptimizer(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetOptimizer().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetOptimizer().IsEqualTo(Value_Optimizer::GetOptimizer(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetOptimizer().IsLessThan(Value_Optimizer::GetOptimizer(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	// Virtual functions for runtime process
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag) override;
	virtual bool DoSetProperty(Processor& processor, const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr) override;
};

Gurax_EndModuleScope(ml)

#endif
