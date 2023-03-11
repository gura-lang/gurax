//==============================================================================
// VType_Curv.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_CURV_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_CURV_H
#include <gurax.h>
#include "Curv.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Curv
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Curv : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Curv VTYPE_Curv;

//------------------------------------------------------------------------------
// Value_Curv
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Curv : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Curv);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Curv");
protected:
	RefPtr<Curv> _pCurv;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Curv() = delete;
	explicit Value_Curv(Curv* pCurv, VType& vtype = VTYPE_Curv) :
		Value_Object(vtype), _pCurv(pCurv) {}
	// Copy constructor/operator
	Value_Curv(const Value_Curv& src) :
		Value_Object(src), _pCurv(src._pCurv->Reference()) {}
	Value_Curv& operator=(const Value_Curv& src) = delete;
	// Move constructor/operator
	Value_Curv(Value_Curv&& src) noexcept = delete;
	Value_Curv& operator=(Value_Curv&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Curv() = default;
public:
	Curv& GetCurv() { return *_pCurv; }
	const Curv& GetCurv() const { return *_pCurv; }
public:
	static Curv& GetCurv(Value& value) {
		return dynamic_cast<Value_Curv&>(value).GetCurv();
	}
	static const Curv& GetCurv(const Value& value) {
		return dynamic_cast<const Value_Curv&>(value).GetCurv();
	}
	static Curv* GetEntityPtr(Value& value) { return &GetCurv(value); }
	static const Curv* GetEntityPtr(const Value& value) { return &GetCurv(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetCurv().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetCurv().IsEqualTo(Value_Curv::GetCurv(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetCurv().IsLessThan(Value_Curv::GetCurv(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
