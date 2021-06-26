//==============================================================================
// VType_wxPoint.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPOINT_H
#define GURAX_MODULE_WX_VTYPE_WXPOINT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPoint
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPoint : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPoint VTYPE_wxPoint;

//------------------------------------------------------------------------------
// Value_wxPoint
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPoint : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPoint);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPoint");
protected:
	wxPoint _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPoint() = delete;
	explicit Value_wxPoint(const wxPoint& entity, VType& vtype = VTYPE_wxPoint) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxPoint(const Value_wxPoint& src) = delete;
	Value_wxPoint& operator=(const Value_wxPoint& src) = delete;
	// Move constructor/operator
	Value_wxPoint(Value_wxPoint&& src) noexcept = delete;
	Value_wxPoint& operator=(Value_wxPoint&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPoint() = default;
public:
	wxPoint& GetEntity() { return _entity; }
	const wxPoint& GetEntity() const { return _entity; }
	wxPoint* GetEntityPtr() { return &_entity; }
	const wxPoint* GetEntityPtr() const { return &_entity; }
public:
	static wxPoint& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPoint&>(value).GetEntity();
	}
	static const wxPoint& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPoint&>(value).GetEntity();
	}
	static wxPoint* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPoint&>(value).GetEntityPtr();
	}
	static const wxPoint* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPoint&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntityPtr(*this) == GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(GetEntityPtr(*this) < GetEntityPtr(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif