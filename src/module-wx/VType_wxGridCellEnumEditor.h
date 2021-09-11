//==============================================================================
// VType_wxGridCellEnumEditor.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDCELLENUMEDITOR_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDCELLENUMEDITOR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"
#include "VType_wxGridCellChoiceEditor.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridCellEnumEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridCellEnumEditor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridCellEnumEditor VTYPE_wxGridCellEnumEditor;

//------------------------------------------------------------------------------
// Value_wxGridCellEnumEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridCellEnumEditor : public Value_wxGridCellChoiceEditor {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridCellEnumEditor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridCellEnumEditor");
protected:
	wxGridCellEnumEditor& _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridCellEnumEditor() = delete;
	explicit Value_wxGridCellEnumEditor(const wxGridCellEnumEditor& entity, VType& vtype = VTYPE_wxGridCellEnumEditor) :
		Value_wxGridCellChoiceEditor(entity, vtype), _entity(const_cast<wxGridCellEnumEditor&>(entity)) {}
	// Copy constructor/operator
	Value_wxGridCellEnumEditor(const Value_wxGridCellEnumEditor& src) = delete;
	Value_wxGridCellEnumEditor& operator=(const Value_wxGridCellEnumEditor& src) = delete;
	// Move constructor/operator
	Value_wxGridCellEnumEditor(Value_wxGridCellEnumEditor&& src) noexcept = delete;
	Value_wxGridCellEnumEditor& operator=(Value_wxGridCellEnumEditor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridCellEnumEditor() = default;
public:
	wxGridCellEnumEditor& GetEntity() { return _entity; }
	const wxGridCellEnumEditor& GetEntity() const { return _entity; }
	wxGridCellEnumEditor* GetEntityPtr() { return &_entity; }
	const wxGridCellEnumEditor* GetEntityPtr() const { return &_entity; }
public:
	static wxGridCellEnumEditor& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridCellEnumEditor&>(value).GetEntity();
	}
	static const wxGridCellEnumEditor& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridCellEnumEditor&>(value).GetEntity();
	}
	static wxGridCellEnumEditor* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridCellEnumEditor&>(value).GetEntityPtr();
	}
	static const wxGridCellEnumEditor* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridCellEnumEditor&>(value).GetEntityPtr();
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
