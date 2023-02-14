//==============================================================================
// VType_Solid.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_STL_VTYPE_SOLID_H
#define GURAX_MODULE_MODEL_STL_VTYPE_SOLID_H
#include <gurax.h>
#include "Solid.h"

Gurax_BeginModuleScope(model_stl)

//------------------------------------------------------------------------------
// VType_Solid
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Solid : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Solid VTYPE_Solid;

//------------------------------------------------------------------------------
// Value_Solid
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Solid : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Solid);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Solid");
protected:
	RefPtr<Solid> _pSolid;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Solid() = delete;
	explicit Value_Solid(Solid* pSolid, VType& vtype = VTYPE_Solid) :
		Value_Object(vtype), _pSolid(pSolid) {}
	// Copy constructor/operator
	Value_Solid(const Value_Solid& src) :
		Value_Object(src), _pSolid(src._pSolid->Reference()) {}
	Value_Solid& operator=(const Value_Solid& src) = delete;
	// Move constructor/operator
	Value_Solid(Value_Solid&& src) noexcept = delete;
	Value_Solid& operator=(Value_Solid&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Solid() = default;
public:
	Solid& GetSolid() { return *_pSolid; }
	const Solid& GetSolid() const { return *_pSolid; }
public:
	static Solid& GetSolid(Value& value) {
		return dynamic_cast<Value_Solid&>(value).GetSolid();
	}
	static const Solid& GetSolid(const Value& value) {
		return dynamic_cast<const Value_Solid&>(value).GetSolid();
	}
	static Solid* GetEntityPtr(Value& value) { return &GetSolid(value); }
	static const Solid* GetEntityPtr(const Value& value) { return &GetSolid(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetSolid().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetSolid().IsEqualTo(Value_Solid::GetSolid(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetSolid().IsLessThan(Value_Solid::GetSolid(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_stl)

#endif
