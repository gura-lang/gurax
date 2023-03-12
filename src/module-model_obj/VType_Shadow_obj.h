//==============================================================================
// VType_Shadow_obj.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_SHADOW_OBJ_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_SHADOW_OBJ_H
#include <gurax.h>
#include "Data.h"
#include "Shadow_obj.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Shadow_obj
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Shadow_obj : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Shadow_obj VTYPE_Shadow_obj;

//------------------------------------------------------------------------------
// Value_Shadow_obj
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Shadow_obj : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Shadow_obj);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Shadow_obj");
protected:
	RefPtr<Shadow_obj> _pShadow_obj;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Shadow_obj() = delete;
	explicit Value_Shadow_obj(Shadow_obj* pShadow_obj, VType& vtype = VTYPE_Shadow_obj) :
		Value_Object(vtype), _pShadow_obj(pShadow_obj) {}
	// Copy constructor/operator
	Value_Shadow_obj(const Value_Shadow_obj& src) :
		Value_Object(src), _pShadow_obj(src._pShadow_obj->Reference()) {}
	Value_Shadow_obj& operator=(const Value_Shadow_obj& src) = delete;
	// Move constructor/operator
	Value_Shadow_obj(Value_Shadow_obj&& src) noexcept = delete;
	Value_Shadow_obj& operator=(Value_Shadow_obj&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Shadow_obj() = default;
public:
	Shadow_obj& GetShadow_obj() { return *_pShadow_obj; }
	const Shadow_obj& GetShadow_obj() const { return *_pShadow_obj; }
public:
	static Shadow_obj& GetShadow_obj(Value& value) {
		return dynamic_cast<Value_Shadow_obj&>(value).GetShadow_obj();
	}
	static const Shadow_obj& GetShadow_obj(const Value& value) {
		return dynamic_cast<const Value_Shadow_obj&>(value).GetShadow_obj();
	}
	static Shadow_obj* GetEntityPtr(Value& value) { return &GetShadow_obj(value); }
	static const Shadow_obj* GetEntityPtr(const Value& value) { return &GetShadow_obj(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetShadow_obj().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetShadow_obj().IsEqualTo(Value_Shadow_obj::GetShadow_obj(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetShadow_obj().IsLessThan(Value_Shadow_obj::GetShadow_obj(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
