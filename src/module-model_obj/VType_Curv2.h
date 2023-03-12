//==============================================================================
// VType_Curv2.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_CURV2_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_CURV2_H
#include <gurax.h>
#include "Data.h"
#include "Curv2.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Curv2
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Curv2 : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Curv2 VTYPE_Curv2;

//------------------------------------------------------------------------------
// Value_Curv2
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Curv2 : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Curv2);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Curv2");
protected:
	RefPtr<Curv2> _pCurv2;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Curv2() = delete;
	explicit Value_Curv2(Curv2* pCurv2, VType& vtype = VTYPE_Curv2) :
		Value_Object(vtype), _pCurv2(pCurv2) {}
	// Copy constructor/operator
	Value_Curv2(const Value_Curv2& src) :
		Value_Object(src), _pCurv2(src._pCurv2->Reference()) {}
	Value_Curv2& operator=(const Value_Curv2& src) = delete;
	// Move constructor/operator
	Value_Curv2(Value_Curv2&& src) noexcept = delete;
	Value_Curv2& operator=(Value_Curv2&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Curv2() = default;
public:
	Curv2& GetCurv2() { return *_pCurv2; }
	const Curv2& GetCurv2() const { return *_pCurv2; }
public:
	static Curv2& GetCurv2(Value& value) {
		return dynamic_cast<Value_Curv2&>(value).GetCurv2();
	}
	static const Curv2& GetCurv2(const Value& value) {
		return dynamic_cast<const Value_Curv2&>(value).GetCurv2();
	}
	static Curv2* GetEntityPtr(Value& value) { return &GetCurv2(value); }
	static const Curv2* GetEntityPtr(const Value& value) { return &GetCurv2(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetCurv2().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetCurv2().IsEqualTo(Value_Curv2::GetCurv2(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetCurv2().IsLessThan(Value_Curv2::GetCurv2(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
