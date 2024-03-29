﻿//==============================================================================
// VType_wxPropertyGrid.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPROPERTYGRID_H
#define GURAX_MODULE_WX_VTYPE_WXPROPERTYGRID_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPropertyGrid
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPropertyGrid : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPropertyGrid VTYPE_wxPropertyGrid;

//------------------------------------------------------------------------------
// Value_wxPropertyGrid
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPropertyGrid : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPropertyGrid);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPropertyGrid");
protected:
	wxWeakRef<wxPropertyGrid> _pEntity;
public:
	class EntityT : public wxPropertyGrid {
	public:
		using wxPropertyGrid::wxPropertyGrid;
	public:
		EntityCore core_gurax;
		virtual wxStatusBar* GetStatusBar() override;
		wxStatusBar* public_GetStatusBar() { return wxPropertyGrid::GetStatusBar(); }
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPropertyGrid() = delete;
	explicit Value_wxPropertyGrid(wxPropertyGrid* pEntity, VType& vtype = VTYPE_wxPropertyGrid) :
		Value_wxControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxPropertyGrid(const Value_wxPropertyGrid& src) = delete;
	Value_wxPropertyGrid& operator=(const Value_wxPropertyGrid& src) = delete;
	// Move constructor/operator
	Value_wxPropertyGrid(Value_wxPropertyGrid&& src) noexcept = delete;
	Value_wxPropertyGrid& operator=(Value_wxPropertyGrid&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPropertyGrid() = default;
public:
	wxPropertyGrid& GetEntity() { return *_pEntity; }
	const wxPropertyGrid& GetEntity() const { return *_pEntity; }
	wxPropertyGrid* GetEntityPtr() { return _pEntity.get(); }
	const wxPropertyGrid* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxPropertyGrid& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPropertyGrid&>(value).GetEntity();
	}
	static const wxPropertyGrid& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPropertyGrid&>(value).GetEntity();
	}
	static wxPropertyGrid* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPropertyGrid&>(value).GetEntityPtr();
	}
	static const wxPropertyGrid* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPropertyGrid&>(value).GetEntityPtr();
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
