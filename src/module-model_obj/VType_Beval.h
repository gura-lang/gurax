//==============================================================================
// VType_Beval.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_BEVAL_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_BEVAL_H
#include <gurax.h>
#include "Data.h"
#include "Beval.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Beval
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Beval : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Beval VTYPE_Beval;

//------------------------------------------------------------------------------
// Value_Beval
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Beval : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Beval);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Beval");
protected:
	RefPtr<Beval> _pBeval;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Beval() = delete;
	explicit Value_Beval(Beval* pBeval, VType& vtype = VTYPE_Beval) :
		Value_Object(vtype), _pBeval(pBeval) {}
	// Copy constructor/operator
	Value_Beval(const Value_Beval& src) :
		Value_Object(src), _pBeval(src._pBeval->Reference()) {}
	Value_Beval& operator=(const Value_Beval& src) = delete;
	// Move constructor/operator
	Value_Beval(Value_Beval&& src) noexcept = delete;
	Value_Beval& operator=(Value_Beval&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Beval() = default;
public:
	Beval& GetBeval() { return *_pBeval; }
	const Beval& GetBeval() const { return *_pBeval; }
public:
	static Beval& GetBeval(Value& value) {
		return dynamic_cast<Value_Beval&>(value).GetBeval();
	}
	static const Beval& GetBeval(const Value& value) {
		return dynamic_cast<const Value_Beval&>(value).GetBeval();
	}
	static Beval* GetEntityPtr(Value& value) { return &GetBeval(value); }
	static const Beval* GetEntityPtr(const Value& value) { return &GetBeval(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetBeval().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetBeval().IsEqualTo(Value_Beval::GetBeval(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetBeval().IsLessThan(Value_Beval::GetBeval(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
