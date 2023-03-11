//==============================================================================
// VType_Parm.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_PARM_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_PARM_H
#include <gurax.h>
#include "Parm.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Parm
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Parm : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Parm VTYPE_Parm;

//------------------------------------------------------------------------------
// Value_Parm
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Parm : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Parm);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Parm");
protected:
	RefPtr<Parm> _pParm;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Parm() = delete;
	explicit Value_Parm(Parm* pParm, VType& vtype = VTYPE_Parm) :
		Value_Object(vtype), _pParm(pParm) {}
	// Copy constructor/operator
	Value_Parm(const Value_Parm& src) :
		Value_Object(src), _pParm(src._pParm->Reference()) {}
	Value_Parm& operator=(const Value_Parm& src) = delete;
	// Move constructor/operator
	Value_Parm(Value_Parm&& src) noexcept = delete;
	Value_Parm& operator=(Value_Parm&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Parm() = default;
public:
	Parm& GetParm() { return *_pParm; }
	const Parm& GetParm() const { return *_pParm; }
public:
	static Parm& GetParm(Value& value) {
		return dynamic_cast<Value_Parm&>(value).GetParm();
	}
	static const Parm& GetParm(const Value& value) {
		return dynamic_cast<const Value_Parm&>(value).GetParm();
	}
	static Parm* GetEntityPtr(Value& value) { return &GetParm(value); }
	static const Parm* GetEntityPtr(const Value& value) { return &GetParm(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetParm().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetParm().IsEqualTo(Value_Parm::GetParm(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetParm().IsLessThan(Value_Parm::GetParm(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
