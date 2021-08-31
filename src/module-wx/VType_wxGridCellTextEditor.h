//==============================================================================
// VType_wxGridCellTextEditor.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDCELLTEXTEDITOR_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDCELLTEXTEDITOR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"
#include "VType_wxGridCellEditor.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridCellTextEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridCellTextEditor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridCellTextEditor VTYPE_wxGridCellTextEditor;

//------------------------------------------------------------------------------
// Value_wxGridCellTextEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridCellTextEditor : public Value_wxGridCellEditor {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridCellTextEditor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridCellTextEditor");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridCellTextEditor() = delete;
	explicit Value_wxGridCellTextEditor(const wxGridCellTextEditor& entity, VType& vtype = VTYPE_wxGridCellTextEditor) :
		Value_wxGridCellEditor(entity, vtype) {}
	// Copy constructor/operator
	Value_wxGridCellTextEditor(const Value_wxGridCellTextEditor& src) = delete;
	Value_wxGridCellTextEditor& operator=(const Value_wxGridCellTextEditor& src) = delete;
	// Move constructor/operator
	Value_wxGridCellTextEditor(Value_wxGridCellTextEditor&& src) noexcept = delete;
	Value_wxGridCellTextEditor& operator=(Value_wxGridCellTextEditor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridCellTextEditor() = default;
public:
	wxGridCellTextEditor& GetEntity() {
		return reinterpret_cast<wxGridCellTextEditor&>(Value_wxClientDataContainer::GetEntity());
	}
	const wxGridCellTextEditor& GetEntity() const {
		return reinterpret_cast<const wxGridCellTextEditor&>(Value_wxClientDataContainer::GetEntity());
	}
	wxGridCellTextEditor* GetEntityPtr() {
		return reinterpret_cast<wxGridCellTextEditor*>(Value_wxClientDataContainer::GetEntityPtr());
	}
	const wxGridCellTextEditor* GetEntityPtr() const {
		return reinterpret_cast<const wxGridCellTextEditor*>(Value_wxClientDataContainer::GetEntityPtr());
	}
public:
	static wxGridCellTextEditor& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridCellTextEditor&>(value).GetEntity();
	}
	static const wxGridCellTextEditor& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridCellTextEditor&>(value).GetEntity();
	}
	static wxGridCellTextEditor* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridCellTextEditor&>(value).GetEntityPtr();
	}
	static const wxGridCellTextEditor* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridCellTextEditor&>(value).GetEntityPtr();
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
