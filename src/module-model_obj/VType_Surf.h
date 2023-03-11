//==============================================================================
// VType_Surf.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_SURF_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_SURF_H
#include <gurax.h>
#include "Surf.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Surf
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Surf : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Surf VTYPE_Surf;

//------------------------------------------------------------------------------
// Value_Surf
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Surf : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Surf);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Surf");
protected:
	RefPtr<Surf> _pSurf;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Surf() = delete;
	explicit Value_Surf(Surf* pSurf, VType& vtype = VTYPE_Surf) :
		Value_Object(vtype), _pSurf(pSurf) {}
	// Copy constructor/operator
	Value_Surf(const Value_Surf& src) :
		Value_Object(src), _pSurf(src._pSurf->Reference()) {}
	Value_Surf& operator=(const Value_Surf& src) = delete;
	// Move constructor/operator
	Value_Surf(Value_Surf&& src) noexcept = delete;
	Value_Surf& operator=(Value_Surf&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Surf() = default;
public:
	Surf& GetSurf() { return *_pSurf; }
	const Surf& GetSurf() const { return *_pSurf; }
public:
	static Surf& GetSurf(Value& value) {
		return dynamic_cast<Value_Surf&>(value).GetSurf();
	}
	static const Surf& GetSurf(const Value& value) {
		return dynamic_cast<const Value_Surf&>(value).GetSurf();
	}
	static Surf* GetEntityPtr(Value& value) { return &GetSurf(value); }
	static const Surf* GetEntityPtr(const Value& value) { return &GetSurf(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetSurf().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetSurf().IsEqualTo(Value_Surf::GetSurf(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetSurf().IsLessThan(Value_Surf::GetSurf(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
