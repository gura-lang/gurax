//==============================================================================
// VType_C_interp.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_C_INTERP_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_C_INTERP_H
#include <gurax.h>
#include "C_interp.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_C_interp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_C_interp : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_C_interp VTYPE_C_interp;

//------------------------------------------------------------------------------
// Value_C_interp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_C_interp : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_C_interp);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_C_interp");
protected:
	RefPtr<C_interp> _pC_interp;
public:
	static VType& vtype;
public:
	// Constructor
	Value_C_interp() = delete;
	explicit Value_C_interp(C_interp* pC_interp, VType& vtype = VTYPE_C_interp) :
		Value_Object(vtype), _pC_interp(pC_interp) {}
	// Copy constructor/operator
	Value_C_interp(const Value_C_interp& src) :
		Value_Object(src), _pC_interp(src._pC_interp->Reference()) {}
	Value_C_interp& operator=(const Value_C_interp& src) = delete;
	// Move constructor/operator
	Value_C_interp(Value_C_interp&& src) noexcept = delete;
	Value_C_interp& operator=(Value_C_interp&& src) noexcept = delete;
protected:
	// Destructor
	~Value_C_interp() = default;
public:
	C_interp& GetC_interp() { return *_pC_interp; }
	const C_interp& GetC_interp() const { return *_pC_interp; }
public:
	static C_interp& GetC_interp(Value& value) {
		return dynamic_cast<Value_C_interp&>(value).GetC_interp();
	}
	static const C_interp& GetC_interp(const Value& value) {
		return dynamic_cast<const Value_C_interp&>(value).GetC_interp();
	}
	static C_interp* GetEntityPtr(Value& value) { return &GetC_interp(value); }
	static const C_interp* GetEntityPtr(const Value& value) { return &GetC_interp(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetC_interp().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetC_interp().IsEqualTo(Value_C_interp::GetC_interp(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetC_interp().IsLessThan(Value_C_interp::GetC_interp(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
