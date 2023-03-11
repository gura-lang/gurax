//==============================================================================
// VType_D_interp.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_D_INTERP_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_D_INTERP_H
#include <gurax.h>
#include "D_interp.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_D_interp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_D_interp : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_D_interp VTYPE_D_interp;

//------------------------------------------------------------------------------
// Value_D_interp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_D_interp : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_D_interp);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_D_interp");
protected:
	RefPtr<D_interp> _pD_interp;
public:
	static VType& vtype;
public:
	// Constructor
	Value_D_interp() = delete;
	explicit Value_D_interp(D_interp* pD_interp, VType& vtype = VTYPE_D_interp) :
		Value_Object(vtype), _pD_interp(pD_interp) {}
	// Copy constructor/operator
	Value_D_interp(const Value_D_interp& src) :
		Value_Object(src), _pD_interp(src._pD_interp->Reference()) {}
	Value_D_interp& operator=(const Value_D_interp& src) = delete;
	// Move constructor/operator
	Value_D_interp(Value_D_interp&& src) noexcept = delete;
	Value_D_interp& operator=(Value_D_interp&& src) noexcept = delete;
protected:
	// Destructor
	~Value_D_interp() = default;
public:
	D_interp& GetD_interp() { return *_pD_interp; }
	const D_interp& GetD_interp() const { return *_pD_interp; }
public:
	static D_interp& GetD_interp(Value& value) {
		return dynamic_cast<Value_D_interp&>(value).GetD_interp();
	}
	static const D_interp& GetD_interp(const Value& value) {
		return dynamic_cast<const Value_D_interp&>(value).GetD_interp();
	}
	static D_interp* GetEntityPtr(Value& value) { return &GetD_interp(value); }
	static const D_interp* GetEntityPtr(const Value& value) { return &GetD_interp(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetD_interp().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetD_interp().IsEqualTo(Value_D_interp::GetD_interp(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetD_interp().IsLessThan(Value_D_interp::GetD_interp(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
