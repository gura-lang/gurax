//==============================================================================
// VType_wxHtmlWidgetCell.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXHTMLWIDGETCELL_H
#define GURAX_MODULE_WX_VTYPE_WXHTMLWIDGETCELL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/html/htmlcell.h>
#include "Util.h"
#include "VType_wxHtmlCell.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxHtmlWidgetCell
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxHtmlWidgetCell : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxHtmlWidgetCell VTYPE_wxHtmlWidgetCell;

//------------------------------------------------------------------------------
// Value_wxHtmlWidgetCell
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxHtmlWidgetCell : public Value_wxHtmlCell {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxHtmlWidgetCell);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxHtmlWidgetCell");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxHtmlWidgetCell() = delete;
	explicit Value_wxHtmlWidgetCell(const wxHtmlWidgetCell& entity, VType& vtype = VTYPE_wxHtmlWidgetCell) :
		Value_wxHtmlCell(entity, vtype) {}
	// Copy constructor/operator
	Value_wxHtmlWidgetCell(const Value_wxHtmlWidgetCell& src) = delete;
	Value_wxHtmlWidgetCell& operator=(const Value_wxHtmlWidgetCell& src) = delete;
	// Move constructor/operator
	Value_wxHtmlWidgetCell(Value_wxHtmlWidgetCell&& src) noexcept = delete;
	Value_wxHtmlWidgetCell& operator=(Value_wxHtmlWidgetCell&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxHtmlWidgetCell() = default;
public:
	wxHtmlWidgetCell& GetEntity() { return reinterpret_cast<wxHtmlWidgetCell&>(Value_wxHtmlCell::GetEntity()); }
	const wxHtmlWidgetCell& GetEntity() const { return reinterpret_cast<const wxHtmlWidgetCell&>(Value_wxHtmlCell::GetEntity()); }
	wxHtmlWidgetCell* GetEntityPtr() { return reinterpret_cast<wxHtmlWidgetCell*>(Value_wxHtmlCell::GetEntityPtr()); }\
	const wxHtmlWidgetCell* GetEntityPtr() const { return reinterpret_cast<const wxHtmlWidgetCell*>(Value_wxHtmlCell::GetEntityPtr()); }
public:
	static wxHtmlWidgetCell& GetEntity(Value& value) {
		return dynamic_cast<Value_wxHtmlWidgetCell&>(value).GetEntity();
	}
	static const wxHtmlWidgetCell& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxHtmlWidgetCell&>(value).GetEntity();
	}
	static wxHtmlWidgetCell* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxHtmlWidgetCell&>(value).GetEntityPtr();
	}
	static const wxHtmlWidgetCell* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxHtmlWidgetCell&>(value).GetEntityPtr();
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