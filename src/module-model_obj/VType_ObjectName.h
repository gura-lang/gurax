//==============================================================================
// VType_ObjectName.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_OBJECTNAME_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_OBJECTNAME_H
#include <gurax.h>
#include "ObjectName.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_ObjectName
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_ObjectName : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_ObjectName VTYPE_ObjectName;

//------------------------------------------------------------------------------
// Value_ObjectName
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_ObjectName : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_ObjectName);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_ObjectName");
protected:
	RefPtr<ObjectName> _pObjectName;
public:
	static VType& vtype;
public:
	// Constructor
	Value_ObjectName() = delete;
	explicit Value_ObjectName(ObjectName* pObjectName, VType& vtype = VTYPE_ObjectName) :
		Value_Object(vtype), _pObjectName(pObjectName) {}
	// Copy constructor/operator
	Value_ObjectName(const Value_ObjectName& src) :
		Value_Object(src), _pObjectName(src._pObjectName->Reference()) {}
	Value_ObjectName& operator=(const Value_ObjectName& src) = delete;
	// Move constructor/operator
	Value_ObjectName(Value_ObjectName&& src) noexcept = delete;
	Value_ObjectName& operator=(Value_ObjectName&& src) noexcept = delete;
protected:
	// Destructor
	~Value_ObjectName() = default;
public:
	ObjectName& GetObjectName() { return *_pObjectName; }
	const ObjectName& GetObjectName() const { return *_pObjectName; }
public:
	static ObjectName& GetObjectName(Value& value) {
		return dynamic_cast<Value_ObjectName&>(value).GetObjectName();
	}
	static const ObjectName& GetObjectName(const Value& value) {
		return dynamic_cast<const Value_ObjectName&>(value).GetObjectName();
	}
	static ObjectName* GetEntityPtr(Value& value) { return &GetObjectName(value); }
	static const ObjectName* GetEntityPtr(const Value& value) { return &GetObjectName(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetObjectName().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetObjectName().IsEqualTo(Value_ObjectName::GetObjectName(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetObjectName().IsLessThan(Value_ObjectName::GetObjectName(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
