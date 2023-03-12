//==============================================================================
// VType_Trace_obj.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_TRACE_OBJ_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_TRACE_OBJ_H
#include <gurax.h>
#include "Data.h"
#include "Trace_obj.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Trace_obj
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Trace_obj : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Trace_obj VTYPE_Trace_obj;

//------------------------------------------------------------------------------
// Value_Trace_obj
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Trace_obj : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Trace_obj);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Trace_obj");
protected:
	RefPtr<Trace_obj> _pTrace_obj;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Trace_obj() = delete;
	explicit Value_Trace_obj(Trace_obj* pTrace_obj, VType& vtype = VTYPE_Trace_obj) :
		Value_Object(vtype), _pTrace_obj(pTrace_obj) {}
	// Copy constructor/operator
	Value_Trace_obj(const Value_Trace_obj& src) :
		Value_Object(src), _pTrace_obj(src._pTrace_obj->Reference()) {}
	Value_Trace_obj& operator=(const Value_Trace_obj& src) = delete;
	// Move constructor/operator
	Value_Trace_obj(Value_Trace_obj&& src) noexcept = delete;
	Value_Trace_obj& operator=(Value_Trace_obj&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Trace_obj() = default;
public:
	Trace_obj& GetTrace_obj() { return *_pTrace_obj; }
	const Trace_obj& GetTrace_obj() const { return *_pTrace_obj; }
public:
	static Trace_obj& GetTrace_obj(Value& value) {
		return dynamic_cast<Value_Trace_obj&>(value).GetTrace_obj();
	}
	static const Trace_obj& GetTrace_obj(const Value& value) {
		return dynamic_cast<const Value_Trace_obj&>(value).GetTrace_obj();
	}
	static Trace_obj* GetEntityPtr(Value& value) { return &GetTrace_obj(value); }
	static const Trace_obj* GetEntityPtr(const Value& value) { return &GetTrace_obj(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetTrace_obj().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetTrace_obj().IsEqualTo(Value_Trace_obj::GetTrace_obj(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetTrace_obj().IsLessThan(Value_Trace_obj::GetTrace_obj(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
