//==============================================================================
// VType_wxGridCellNumberEditor.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDCELLNUMBEREDITOR_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDCELLNUMBEREDITOR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"
#include "VType_wxGridCellTextEditor.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridCellNumberEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridCellNumberEditor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridCellNumberEditor VTYPE_wxGridCellNumberEditor;

//------------------------------------------------------------------------------
// Value_wxGridCellNumberEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridCellNumberEditor : public Value_wxGridCellTextEditor {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridCellNumberEditor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridCellNumberEditor");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridCellNumberEditor() = delete;
	explicit Value_wxGridCellNumberEditor(const wxGridCellNumberEditor& entity, VType& vtype = VTYPE_wxGridCellNumberEditor) :
		Value_wxGridCellTextEditor(entity, vtype) {}
	// Copy constructor/operator
	Value_wxGridCellNumberEditor(const Value_wxGridCellNumberEditor& src) = delete;
	Value_wxGridCellNumberEditor& operator=(const Value_wxGridCellNumberEditor& src) = delete;
	// Move constructor/operator
	Value_wxGridCellNumberEditor(Value_wxGridCellNumberEditor&& src) noexcept = delete;
	Value_wxGridCellNumberEditor& operator=(Value_wxGridCellNumberEditor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridCellNumberEditor() = default;
public:
	wxGridCellNumberEditor& GetEntity() {
		return reinterpret_cast<wxGridCellNumberEditor&>(Value_wxClientDataContainer::GetEntity());
	}
	const wxGridCellNumberEditor& GetEntity() const {
		return reinterpret_cast<const wxGridCellNumberEditor&>(Value_wxClientDataContainer::GetEntity());
	}
	wxGridCellNumberEditor* GetEntityPtr() {
		return reinterpret_cast<wxGridCellNumberEditor*>(Value_wxClientDataContainer::GetEntityPtr());
	}
	const wxGridCellNumberEditor* GetEntityPtr() const {
		return reinterpret_cast<const wxGridCellNumberEditor*>(Value_wxClientDataContainer::GetEntityPtr());
	}
public:
	static wxGridCellNumberEditor& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridCellNumberEditor&>(value).GetEntity();
	}
	static const wxGridCellNumberEditor& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridCellNumberEditor&>(value).GetEntity();
	}
	static wxGridCellNumberEditor* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridCellNumberEditor&>(value).GetEntityPtr();
	}
	static const wxGridCellNumberEditor* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridCellNumberEditor&>(value).GetEntityPtr();
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
