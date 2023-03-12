//==============================================================================
// VType_Ctech.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_CTECH_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_CTECH_H
#include <gurax.h>
#include "Data.h"
#include "Ctech.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Ctech
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Ctech : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Ctech VTYPE_Ctech;

//------------------------------------------------------------------------------
// Value_Ctech
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Ctech : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Ctech);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Ctech");
protected:
	RefPtr<Ctech> _pCtech;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Ctech() = delete;
	explicit Value_Ctech(Ctech* pCtech, VType& vtype = VTYPE_Ctech) :
		Value_Object(vtype), _pCtech(pCtech) {}
	// Copy constructor/operator
	Value_Ctech(const Value_Ctech& src) :
		Value_Object(src), _pCtech(src._pCtech->Reference()) {}
	Value_Ctech& operator=(const Value_Ctech& src) = delete;
	// Move constructor/operator
	Value_Ctech(Value_Ctech&& src) noexcept = delete;
	Value_Ctech& operator=(Value_Ctech&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Ctech() = default;
public:
	Ctech& GetCtech() { return *_pCtech; }
	const Ctech& GetCtech() const { return *_pCtech; }
public:
	static Ctech& GetCtech(Value& value) {
		return dynamic_cast<Value_Ctech&>(value).GetCtech();
	}
	static const Ctech& GetCtech(const Value& value) {
		return dynamic_cast<const Value_Ctech&>(value).GetCtech();
	}
	static Ctech* GetEntityPtr(Value& value) { return &GetCtech(value); }
	static const Ctech* GetEntityPtr(const Value& value) { return &GetCtech(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetCtech().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetCtech().IsEqualTo(Value_Ctech::GetCtech(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetCtech().IsLessThan(Value_Ctech::GetCtech(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
