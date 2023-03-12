//==============================================================================
// VType_Stech.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_STECH_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_STECH_H
#include <gurax.h>
#include "Data.h"
#include "Stech.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Stech
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Stech : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Stech VTYPE_Stech;

//------------------------------------------------------------------------------
// Value_Stech
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Stech : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Stech);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Stech");
protected:
	RefPtr<Stech> _pStech;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Stech() = delete;
	explicit Value_Stech(Stech* pStech, VType& vtype = VTYPE_Stech) :
		Value_Object(vtype), _pStech(pStech) {}
	// Copy constructor/operator
	Value_Stech(const Value_Stech& src) :
		Value_Object(src), _pStech(src._pStech->Reference()) {}
	Value_Stech& operator=(const Value_Stech& src) = delete;
	// Move constructor/operator
	Value_Stech(Value_Stech&& src) noexcept = delete;
	Value_Stech& operator=(Value_Stech&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Stech() = default;
public:
	Stech& GetStech() { return *_pStech; }
	const Stech& GetStech() const { return *_pStech; }
public:
	static Stech& GetStech(Value& value) {
		return dynamic_cast<Value_Stech&>(value).GetStech();
	}
	static const Stech& GetStech(const Value& value) {
		return dynamic_cast<const Value_Stech&>(value).GetStech();
	}
	static Stech* GetEntityPtr(Value& value) { return &GetStech(value); }
	static const Stech* GetEntityPtr(const Value& value) { return &GetStech(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetStech().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetStech().IsEqualTo(Value_Stech::GetStech(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetStech().IsLessThan(Value_Stech::GetStech(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
