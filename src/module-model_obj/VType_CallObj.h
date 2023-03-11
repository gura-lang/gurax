//==============================================================================
// VType_CallObj.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_CALLOBJ_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_CALLOBJ_H
#include <gurax.h>
#include "CallObj.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_CallObj
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_CallObj : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_CallObj VTYPE_CallObj;

//------------------------------------------------------------------------------
// Value_CallObj
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_CallObj : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_CallObj);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_CallObj");
protected:
	RefPtr<CallObj> _pCallObj;
public:
	static VType& vtype;
public:
	// Constructor
	Value_CallObj() = delete;
	explicit Value_CallObj(CallObj* pCallObj, VType& vtype = VTYPE_CallObj) :
		Value_Object(vtype), _pCallObj(pCallObj) {}
	// Copy constructor/operator
	Value_CallObj(const Value_CallObj& src) :
		Value_Object(src), _pCallObj(src._pCallObj->Reference()) {}
	Value_CallObj& operator=(const Value_CallObj& src) = delete;
	// Move constructor/operator
	Value_CallObj(Value_CallObj&& src) noexcept = delete;
	Value_CallObj& operator=(Value_CallObj&& src) noexcept = delete;
protected:
	// Destructor
	~Value_CallObj() = default;
public:
	CallObj& GetCallObj() { return *_pCallObj; }
	const CallObj& GetCallObj() const { return *_pCallObj; }
public:
	static CallObj& GetCallObj(Value& value) {
		return dynamic_cast<Value_CallObj&>(value).GetCallObj();
	}
	static const CallObj& GetCallObj(const Value& value) {
		return dynamic_cast<const Value_CallObj&>(value).GetCallObj();
	}
	static CallObj* GetEntityPtr(Value& value) { return &GetCallObj(value); }
	static const CallObj* GetEntityPtr(const Value& value) { return &GetCallObj(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetCallObj().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetCallObj().IsEqualTo(Value_CallObj::GetCallObj(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetCallObj().IsLessThan(Value_CallObj::GetCallObj(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
