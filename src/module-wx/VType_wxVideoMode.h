//==============================================================================
// VType_wxVideoMode.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXVIDEOMODE_H
#define GURAX_MODULE_WX_VTYPE_WXVIDEOMODE_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/vidmode.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxVideoMode
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxVideoMode : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxVideoMode VTYPE_wxVideoMode;

//------------------------------------------------------------------------------
// Value_wxVideoMode
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxVideoMode : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxVideoMode);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxVideoMode");
protected:
	wxVideoMode _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxVideoMode() = delete;
	explicit Value_wxVideoMode(const wxVideoMode& entity, VType& vtype = VTYPE_wxVideoMode) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxVideoMode(const Value_wxVideoMode& src) = delete;
	Value_wxVideoMode& operator=(const Value_wxVideoMode& src) = delete;
	// Move constructor/operator
	Value_wxVideoMode(Value_wxVideoMode&& src) noexcept = delete;
	Value_wxVideoMode& operator=(Value_wxVideoMode&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxVideoMode() = default;
public:
	wxVideoMode& GetEntity() { return _entity; }
	const wxVideoMode& GetEntity() const { return _entity; }
	wxVideoMode* GetEntityPtr() { return &_entity; }
	const wxVideoMode* GetEntityPtr() const { return &_entity; }
public:
	static wxVideoMode& GetEntity(Value& value) {
		return dynamic_cast<Value_wxVideoMode&>(value).GetEntity();
	}
	static const wxVideoMode& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxVideoMode&>(value).GetEntity();
	}
	static wxVideoMode* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxVideoMode&>(value).GetEntityPtr();
	}
	static const wxVideoMode* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxVideoMode&>(value).GetEntityPtr();
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