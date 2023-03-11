//==============================================================================
// VType_Spoint.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_SPOINT_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_SPOINT_H
#include <gurax.h>
#include "Spoint.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Spoint
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Spoint : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Spoint VTYPE_Spoint;

//------------------------------------------------------------------------------
// Value_Spoint
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Spoint : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Spoint);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Spoint");
protected:
	RefPtr<Spoint> _pSpoint;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Spoint() = delete;
	explicit Value_Spoint(Spoint* pSpoint, VType& vtype = VTYPE_Spoint) :
		Value_Object(vtype), _pSpoint(pSpoint) {}
	// Copy constructor/operator
	Value_Spoint(const Value_Spoint& src) :
		Value_Object(src), _pSpoint(src._pSpoint->Reference()) {}
	Value_Spoint& operator=(const Value_Spoint& src) = delete;
	// Move constructor/operator
	Value_Spoint(Value_Spoint&& src) noexcept = delete;
	Value_Spoint& operator=(Value_Spoint&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Spoint() = default;
public:
	Spoint& GetSpoint() { return *_pSpoint; }
	const Spoint& GetSpoint() const { return *_pSpoint; }
public:
	static Spoint& GetSpoint(Value& value) {
		return dynamic_cast<Value_Spoint&>(value).GetSpoint();
	}
	static const Spoint& GetSpoint(const Value& value) {
		return dynamic_cast<const Value_Spoint&>(value).GetSpoint();
	}
	static Spoint* GetEntityPtr(Value& value) { return &GetSpoint(value); }
	static const Spoint* GetEntityPtr(const Value& value) { return &GetSpoint(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetSpoint().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetSpoint().IsEqualTo(Value_Spoint::GetSpoint(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetSpoint().IsLessThan(Value_Spoint::GetSpoint(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
