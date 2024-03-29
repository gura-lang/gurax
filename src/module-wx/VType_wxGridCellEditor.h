﻿//==============================================================================
// VType_wxGridCellEditor.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDCELLEDITOR_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDCELLEDITOR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"
#include "VType_wxClientDataContainer.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridCellEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridCellEditor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridCellEditor VTYPE_wxGridCellEditor;

//------------------------------------------------------------------------------
// Value_wxGridCellEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridCellEditor : public Value_wxClientDataContainer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridCellEditor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridCellEditor");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridCellEditor() = delete;
	explicit Value_wxGridCellEditor(const wxGridCellEditor& entity, VType& vtype = VTYPE_wxGridCellEditor) :
		Value_wxClientDataContainer(entity, vtype) {}
	// Copy constructor/operator
	Value_wxGridCellEditor(const Value_wxGridCellEditor& src) = delete;
	Value_wxGridCellEditor& operator=(const Value_wxGridCellEditor& src) = delete;
	// Move constructor/operator
	Value_wxGridCellEditor(Value_wxGridCellEditor&& src) noexcept = delete;
	Value_wxGridCellEditor& operator=(Value_wxGridCellEditor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridCellEditor() = default;
public:
	wxGridCellEditor& GetEntity() { return reinterpret_cast<wxGridCellEditor&>(Value_wxClientDataContainer::GetEntity()); }
	const wxGridCellEditor& GetEntity() const { return reinterpret_cast<const wxGridCellEditor&>(Value_wxClientDataContainer::GetEntity()); }
	wxGridCellEditor* GetEntityPtr() { return reinterpret_cast<wxGridCellEditor*>(Value_wxClientDataContainer::GetEntityPtr()); }\
	const wxGridCellEditor* GetEntityPtr() const { return reinterpret_cast<const wxGridCellEditor*>(Value_wxClientDataContainer::GetEntityPtr()); }
public:
	static wxGridCellEditor& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridCellEditor&>(value).GetEntity();
	}
	static const wxGridCellEditor& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridCellEditor&>(value).GetEntity();
	}
	static wxGridCellEditor* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridCellEditor&>(value).GetEntityPtr();
	}
	static const wxGridCellEditor* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridCellEditor&>(value).GetEntityPtr();
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
