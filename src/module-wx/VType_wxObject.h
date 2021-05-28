//==============================================================================
// VType_wxObject.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXOBJECT_H
#define GURAX_MODULE_WX_VTYPE_WXOBJECT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxObject
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxObject : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxObject VTYPE_wxObject;

//------------------------------------------------------------------------------
// Value_wxObject
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxObject : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxObject);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxObject");
protected:
	wxObject _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxObject() = delete;
	explicit Value_wxObject(const wxObject& entity, VType& vtype = VTYPE_wxObject) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxObject(const Value_wxObject& src) = delete;
	Value_wxObject& operator=(const Value_wxObject& src) = delete;
	// Move constructor/operator
	Value_wxObject(Value_wxObject&& src) noexcept = delete;
	Value_wxObject& operator=(Value_wxObject&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxObject() = default;
public:
	wxObject& GetEntity() { return _entity; }
	const wxObject& GetEntity() const { return _entity; }
public:
	static wxObject& GetEntity(Value& value) {
		return dynamic_cast<Value_wxObject&>(value).GetEntity();
	}
	static const wxObject& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxObject&>(value).GetEntity();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(&GetEntity(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntity(*this).IsSameAs(GetEntity(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(&GetEntity(*this) < &GetEntity(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif
