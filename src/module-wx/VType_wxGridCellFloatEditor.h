﻿//==============================================================================
// VType_wxGridCellFloatEditor.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDCELLFLOATEDITOR_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDCELLFLOATEDITOR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"
#include "VType_wxGridCellTextEditor.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridCellFloatEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridCellFloatEditor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridCellFloatEditor VTYPE_wxGridCellFloatEditor;

//------------------------------------------------------------------------------
// Value_wxGridCellFloatEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridCellFloatEditor : public Value_wxGridCellTextEditor {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridCellFloatEditor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridCellFloatEditor");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridCellFloatEditor() = delete;
	explicit Value_wxGridCellFloatEditor(const wxGridCellFloatEditor& entity, VType& vtype = VTYPE_wxGridCellFloatEditor) :
		Value_wxGridCellTextEditor(entity, vtype) {}
	// Copy constructor/operator
	Value_wxGridCellFloatEditor(const Value_wxGridCellFloatEditor& src) = delete;
	Value_wxGridCellFloatEditor& operator=(const Value_wxGridCellFloatEditor& src) = delete;
	// Move constructor/operator
	Value_wxGridCellFloatEditor(Value_wxGridCellFloatEditor&& src) noexcept = delete;
	Value_wxGridCellFloatEditor& operator=(Value_wxGridCellFloatEditor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridCellFloatEditor() = default;
public:
	wxGridCellFloatEditor& GetEntity() { return reinterpret_cast<wxGridCellFloatEditor&>(Value_wxGridCellTextEditor::GetEntity()); }
	const wxGridCellFloatEditor& GetEntity() const { return reinterpret_cast<const wxGridCellFloatEditor&>(Value_wxGridCellTextEditor::GetEntity()); }
	wxGridCellFloatEditor* GetEntityPtr() { return reinterpret_cast<wxGridCellFloatEditor*>(Value_wxGridCellTextEditor::GetEntityPtr()); }\
	const wxGridCellFloatEditor* GetEntityPtr() const { return reinterpret_cast<const wxGridCellFloatEditor*>(Value_wxGridCellTextEditor::GetEntityPtr()); }
public:
	static wxGridCellFloatEditor& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridCellFloatEditor&>(value).GetEntity();
	}
	static const wxGridCellFloatEditor& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridCellFloatEditor&>(value).GetEntity();
	}
	static wxGridCellFloatEditor* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridCellFloatEditor&>(value).GetEntityPtr();
	}
	static const wxGridCellFloatEditor* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridCellFloatEditor&>(value).GetEntityPtr();
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
