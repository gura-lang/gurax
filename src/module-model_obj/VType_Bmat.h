//==============================================================================
// VType_Bmat.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_BMAT_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_BMAT_H
#include <gurax.h>
#include "Bmat.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Bmat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Bmat : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Bmat VTYPE_Bmat;

//------------------------------------------------------------------------------
// Value_Bmat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Bmat : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Bmat);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Bmat");
protected:
	RefPtr<Bmat> _pBmat;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Bmat() = delete;
	explicit Value_Bmat(Bmat* pBmat, VType& vtype = VTYPE_Bmat) :
		Value_Object(vtype), _pBmat(pBmat) {}
	// Copy constructor/operator
	Value_Bmat(const Value_Bmat& src) :
		Value_Object(src), _pBmat(src._pBmat->Reference()) {}
	Value_Bmat& operator=(const Value_Bmat& src) = delete;
	// Move constructor/operator
	Value_Bmat(Value_Bmat&& src) noexcept = delete;
	Value_Bmat& operator=(Value_Bmat&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Bmat() = default;
public:
	Bmat& GetBmat() { return *_pBmat; }
	const Bmat& GetBmat() const { return *_pBmat; }
public:
	static Bmat& GetBmat(Value& value) {
		return dynamic_cast<Value_Bmat&>(value).GetBmat();
	}
	static const Bmat& GetBmat(const Value& value) {
		return dynamic_cast<const Value_Bmat&>(value).GetBmat();
	}
	static Bmat* GetEntityPtr(Value& value) { return &GetBmat(value); }
	static const Bmat* GetEntityPtr(const Value& value) { return &GetBmat(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetBmat().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetBmat().IsEqualTo(Value_Bmat::GetBmat(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetBmat().IsLessThan(Value_Bmat::GetBmat(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
