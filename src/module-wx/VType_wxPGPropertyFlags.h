//==============================================================================
// VType_wxPGPropertyFlags.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPGPROPERTYFLAGS_H
#define GURAX_MODULE_WX_VTYPE_WXPGPROPERTYFLAGS_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/property.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPGPropertyFlags
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPGPropertyFlags : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPGPropertyFlags VTYPE_wxPGPropertyFlags;

//------------------------------------------------------------------------------
// Value_wxPGPropertyFlags
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPGPropertyFlags : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPGPropertyFlags);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPGPropertyFlags");
protected:
	wxPGPropertyFlags _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPGPropertyFlags() = delete;
	explicit Value_wxPGPropertyFlags(const wxPGPropertyFlags& entity, VType& vtype = VTYPE_wxPGPropertyFlags) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxPGPropertyFlags(const Value_wxPGPropertyFlags& src) = delete;
	Value_wxPGPropertyFlags& operator=(const Value_wxPGPropertyFlags& src) = delete;
	// Move constructor/operator
	Value_wxPGPropertyFlags(Value_wxPGPropertyFlags&& src) noexcept = delete;
	Value_wxPGPropertyFlags& operator=(Value_wxPGPropertyFlags&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPGPropertyFlags() = default;
public:
	wxPGPropertyFlags& GetEntity() { return _entity; }
	const wxPGPropertyFlags& GetEntity() const { return _entity; }
	wxPGPropertyFlags* GetEntityPtr() { return &_entity; }
	const wxPGPropertyFlags* GetEntityPtr() const { return &_entity; }
public:
	static wxPGPropertyFlags& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPGPropertyFlags&>(value).GetEntity();
	}
	static const wxPGPropertyFlags& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPGPropertyFlags&>(value).GetEntity();
	}
	static wxPGPropertyFlags* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPGPropertyFlags&>(value).GetEntityPtr();
	}
	static const wxPGPropertyFlags* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPGPropertyFlags&>(value).GetEntityPtr();
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
