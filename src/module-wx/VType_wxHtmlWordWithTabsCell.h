﻿//==============================================================================
// VType_wxHtmlWordWithTabsCell.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXHTMLWORDWITHTABSCELL_H
#define GURAX_MODULE_WX_VTYPE_WXHTMLWORDWITHTABSCELL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/html/htmlcell.h>
#include "Util.h"
#include "VType_wxHtmlWordCell.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxHtmlWordWithTabsCell
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxHtmlWordWithTabsCell : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxHtmlWordWithTabsCell VTYPE_wxHtmlWordWithTabsCell;

//------------------------------------------------------------------------------
// Value_wxHtmlWordWithTabsCell
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxHtmlWordWithTabsCell : public Value_wxHtmlWordCell {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxHtmlWordWithTabsCell);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxHtmlWordWithTabsCell");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxHtmlWordWithTabsCell() = delete;
	explicit Value_wxHtmlWordWithTabsCell(const wxHtmlWordWithTabsCell& entity, VType& vtype = VTYPE_wxHtmlWordWithTabsCell) :
		Value_wxHtmlWordCell(entity, vtype) {}
	// Copy constructor/operator
	Value_wxHtmlWordWithTabsCell(const Value_wxHtmlWordWithTabsCell& src) = delete;
	Value_wxHtmlWordWithTabsCell& operator=(const Value_wxHtmlWordWithTabsCell& src) = delete;
	// Move constructor/operator
	Value_wxHtmlWordWithTabsCell(Value_wxHtmlWordWithTabsCell&& src) noexcept = delete;
	Value_wxHtmlWordWithTabsCell& operator=(Value_wxHtmlWordWithTabsCell&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxHtmlWordWithTabsCell() = default;
public:
	wxHtmlWordWithTabsCell& GetEntity() { return reinterpret_cast<wxHtmlWordWithTabsCell&>(Value_wxHtmlWordCell::GetEntity()); }
	const wxHtmlWordWithTabsCell& GetEntity() const { return reinterpret_cast<const wxHtmlWordWithTabsCell&>(Value_wxHtmlWordCell::GetEntity()); }
	wxHtmlWordWithTabsCell* GetEntityPtr() { return reinterpret_cast<wxHtmlWordWithTabsCell*>(Value_wxHtmlWordCell::GetEntityPtr()); }\
	const wxHtmlWordWithTabsCell* GetEntityPtr() const { return reinterpret_cast<const wxHtmlWordWithTabsCell*>(Value_wxHtmlWordCell::GetEntityPtr()); }
public:
	static wxHtmlWordWithTabsCell& GetEntity(Value& value) {
		return dynamic_cast<Value_wxHtmlWordWithTabsCell&>(value).GetEntity();
	}
	static const wxHtmlWordWithTabsCell& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxHtmlWordWithTabsCell&>(value).GetEntity();
	}
	static wxHtmlWordWithTabsCell* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxHtmlWordWithTabsCell&>(value).GetEntityPtr();
	}
	static const wxHtmlWordWithTabsCell* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxHtmlWordWithTabsCell&>(value).GetEntityPtr();
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
