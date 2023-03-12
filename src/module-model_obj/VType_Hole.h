//==============================================================================
// VType_Hole.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_HOLE_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_HOLE_H
#include <gurax.h>
#include "Data.h"
#include "Hole.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Hole
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Hole : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Hole VTYPE_Hole;

//------------------------------------------------------------------------------
// Value_Hole
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Hole : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Hole);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Hole");
protected:
	RefPtr<Hole> _pHole;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Hole() = delete;
	explicit Value_Hole(Hole* pHole, VType& vtype = VTYPE_Hole) :
		Value_Object(vtype), _pHole(pHole) {}
	// Copy constructor/operator
	Value_Hole(const Value_Hole& src) :
		Value_Object(src), _pHole(src._pHole->Reference()) {}
	Value_Hole& operator=(const Value_Hole& src) = delete;
	// Move constructor/operator
	Value_Hole(Value_Hole&& src) noexcept = delete;
	Value_Hole& operator=(Value_Hole&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Hole() = default;
public:
	Hole& GetHole() { return *_pHole; }
	const Hole& GetHole() const { return *_pHole; }
public:
	static Hole& GetHole(Value& value) {
		return dynamic_cast<Value_Hole&>(value).GetHole();
	}
	static const Hole& GetHole(const Value& value) {
		return dynamic_cast<const Value_Hole&>(value).GetHole();
	}
	static Hole* GetEntityPtr(Value& value) { return &GetHole(value); }
	static const Hole* GetEntityPtr(const Value& value) { return &GetHole(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetHole().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetHole().IsEqualTo(Value_Hole::GetHole(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetHole().IsLessThan(Value_Hole::GetHole(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
