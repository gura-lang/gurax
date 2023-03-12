//==============================================================================
// VType_Usemtl.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_USEMTL_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_USEMTL_H
#include <gurax.h>
#include "Data.h"
#include "Usemtl.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Usemtl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Usemtl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Usemtl VTYPE_Usemtl;

//------------------------------------------------------------------------------
// Value_Usemtl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Usemtl : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Usemtl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Usemtl");
protected:
	RefPtr<Usemtl> _pUsemtl;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Usemtl() = delete;
	explicit Value_Usemtl(Usemtl* pUsemtl, VType& vtype = VTYPE_Usemtl) :
		Value_Object(vtype), _pUsemtl(pUsemtl) {}
	// Copy constructor/operator
	Value_Usemtl(const Value_Usemtl& src) :
		Value_Object(src), _pUsemtl(src._pUsemtl->Reference()) {}
	Value_Usemtl& operator=(const Value_Usemtl& src) = delete;
	// Move constructor/operator
	Value_Usemtl(Value_Usemtl&& src) noexcept = delete;
	Value_Usemtl& operator=(Value_Usemtl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Usemtl() = default;
public:
	Usemtl& GetUsemtl() { return *_pUsemtl; }
	const Usemtl& GetUsemtl() const { return *_pUsemtl; }
public:
	static Usemtl& GetUsemtl(Value& value) {
		return dynamic_cast<Value_Usemtl&>(value).GetUsemtl();
	}
	static const Usemtl& GetUsemtl(const Value& value) {
		return dynamic_cast<const Value_Usemtl&>(value).GetUsemtl();
	}
	static Usemtl* GetEntityPtr(Value& value) { return &GetUsemtl(value); }
	static const Usemtl* GetEntityPtr(const Value& value) { return &GetUsemtl(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetUsemtl().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetUsemtl().IsEqualTo(Value_Usemtl::GetUsemtl(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetUsemtl().IsLessThan(Value_Usemtl::GetUsemtl(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
