//==============================================================================
// VType_Cstype.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_CSTYPE_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_CSTYPE_H
#include <gurax.h>
#include "Cstype.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Cstype
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Cstype : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Cstype VTYPE_Cstype;

//------------------------------------------------------------------------------
// Value_Cstype
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Cstype : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Cstype);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Cstype");
protected:
	RefPtr<Cstype> _pCstype;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Cstype() = delete;
	explicit Value_Cstype(Cstype* pCstype, VType& vtype = VTYPE_Cstype) :
		Value_Object(vtype), _pCstype(pCstype) {}
	// Copy constructor/operator
	Value_Cstype(const Value_Cstype& src) :
		Value_Object(src), _pCstype(src._pCstype->Reference()) {}
	Value_Cstype& operator=(const Value_Cstype& src) = delete;
	// Move constructor/operator
	Value_Cstype(Value_Cstype&& src) noexcept = delete;
	Value_Cstype& operator=(Value_Cstype&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Cstype() = default;
public:
	Cstype& GetCstype() { return *_pCstype; }
	const Cstype& GetCstype() const { return *_pCstype; }
public:
	static Cstype& GetCstype(Value& value) {
		return dynamic_cast<Value_Cstype&>(value).GetCstype();
	}
	static const Cstype& GetCstype(const Value& value) {
		return dynamic_cast<const Value_Cstype&>(value).GetCstype();
	}
	static Cstype* GetEntityPtr(Value& value) { return &GetCstype(value); }
	static const Cstype* GetEntityPtr(const Value& value) { return &GetCstype(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetCstype().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetCstype().IsEqualTo(Value_Cstype::GetCstype(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetCstype().IsLessThan(Value_Cstype::GetCstype(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
