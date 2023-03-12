//==============================================================================
// VType_Deg.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_DEG_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_DEG_H
#include <gurax.h>
#include "Data.h"
#include "Deg.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Deg
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Deg : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Deg VTYPE_Deg;

//------------------------------------------------------------------------------
// Value_Deg
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Deg : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Deg);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Deg");
protected:
	RefPtr<Deg> _pDeg;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Deg() = delete;
	explicit Value_Deg(Deg* pDeg, VType& vtype = VTYPE_Deg) :
		Value_Object(vtype), _pDeg(pDeg) {}
	// Copy constructor/operator
	Value_Deg(const Value_Deg& src) :
		Value_Object(src), _pDeg(src._pDeg->Reference()) {}
	Value_Deg& operator=(const Value_Deg& src) = delete;
	// Move constructor/operator
	Value_Deg(Value_Deg&& src) noexcept = delete;
	Value_Deg& operator=(Value_Deg&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Deg() = default;
public:
	Deg& GetDeg() { return *_pDeg; }
	const Deg& GetDeg() const { return *_pDeg; }
public:
	static Deg& GetDeg(Value& value) {
		return dynamic_cast<Value_Deg&>(value).GetDeg();
	}
	static const Deg& GetDeg(const Value& value) {
		return dynamic_cast<const Value_Deg&>(value).GetDeg();
	}
	static Deg* GetEntityPtr(Value& value) { return &GetDeg(value); }
	static const Deg* GetEntityPtr(const Value& value) { return &GetDeg(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetDeg().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetDeg().IsEqualTo(Value_Deg::GetDeg(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetDeg().IsLessThan(Value_Deg::GetDeg(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
