﻿//==============================================================================
// VType_wxPGCell.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPGCELL_H
#define GURAX_MODULE_WX_VTYPE_WXPGCELL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/property.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPGCell
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPGCell : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPGCell VTYPE_wxPGCell;

//------------------------------------------------------------------------------
// Value_wxPGCell
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPGCell : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPGCell);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPGCell");
protected:
	wxPGCell _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPGCell() = delete;
	explicit Value_wxPGCell(const wxPGCell& entity, VType& vtype = VTYPE_wxPGCell) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxPGCell(const Value_wxPGCell& src) = delete;
	Value_wxPGCell& operator=(const Value_wxPGCell& src) = delete;
	// Move constructor/operator
	Value_wxPGCell(Value_wxPGCell&& src) noexcept = delete;
	Value_wxPGCell& operator=(Value_wxPGCell&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPGCell() = default;
public:
	wxPGCell& GetEntity() { return _entity; }
	const wxPGCell& GetEntity() const { return _entity; }
	wxPGCell* GetEntityPtr() { return &_entity; }
	const wxPGCell* GetEntityPtr() const { return &_entity; }
public:
	static wxPGCell& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPGCell&>(value).GetEntity();
	}
	static const wxPGCell& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPGCell&>(value).GetEntity();
	}
	static wxPGCell* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPGCell&>(value).GetEntityPtr();
	}
	static const wxPGCell* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPGCell&>(value).GetEntityPtr();
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
