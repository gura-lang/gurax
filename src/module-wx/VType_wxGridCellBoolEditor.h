//==============================================================================
// VType_wxGridCellBoolEditor.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDCELLBOOLEDITOR_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDCELLBOOLEDITOR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"
#include "VType_wxGridCellEditor.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridCellBoolEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridCellBoolEditor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridCellBoolEditor VTYPE_wxGridCellBoolEditor;

//------------------------------------------------------------------------------
// Value_wxGridCellBoolEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridCellBoolEditor : public Value_wxGridCellEditor {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridCellBoolEditor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridCellBoolEditor");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridCellBoolEditor() = delete;
	explicit Value_wxGridCellBoolEditor(const wxGridCellBoolEditor& entity, VType& vtype = VTYPE_wxGridCellBoolEditor) :
		Value_wxGridCellEditor(entity, vtype) {}
	// Copy constructor/operator
	Value_wxGridCellBoolEditor(const Value_wxGridCellBoolEditor& src) = delete;
	Value_wxGridCellBoolEditor& operator=(const Value_wxGridCellBoolEditor& src) = delete;
	// Move constructor/operator
	Value_wxGridCellBoolEditor(Value_wxGridCellBoolEditor&& src) noexcept = delete;
	Value_wxGridCellBoolEditor& operator=(Value_wxGridCellBoolEditor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridCellBoolEditor() = default;
public:
	wxGridCellBoolEditor& GetEntity() {
		return reinterpret_cast<wxGridCellBoolEditor&>(Value_wxClientDataContainer::GetEntity());
	}
	const wxGridCellBoolEditor& GetEntity() const {
		return reinterpret_cast<const wxGridCellBoolEditor&>(Value_wxClientDataContainer::GetEntity());
	}
	wxGridCellBoolEditor* GetEntityPtr() {
		return reinterpret_cast<wxGridCellBoolEditor*>(Value_wxClientDataContainer::GetEntityPtr());
	}
	const wxGridCellBoolEditor* GetEntityPtr() const {
		return reinterpret_cast<const wxGridCellBoolEditor*>(Value_wxClientDataContainer::GetEntityPtr());
	}
public:
	static wxGridCellBoolEditor& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridCellBoolEditor&>(value).GetEntity();
	}
	static const wxGridCellBoolEditor& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridCellBoolEditor&>(value).GetEntity();
	}
	static wxGridCellBoolEditor* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridCellBoolEditor&>(value).GetEntityPtr();
	}
	static const wxGridCellBoolEditor* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridCellBoolEditor&>(value).GetEntityPtr();
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
