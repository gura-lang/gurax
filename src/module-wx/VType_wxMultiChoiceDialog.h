//==============================================================================
// VType_wxMultiChoiceDialog.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXMULTICHOICEDIALOG_H
#define GURAX_MODULE_WX_VTYPE_WXMULTICHOICEDIALOG_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/choicdlg.h>
#include "Util.h"
#include "VType_wxDialog.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxMultiChoiceDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxMultiChoiceDialog : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxMultiChoiceDialog VTYPE_wxMultiChoiceDialog;

//------------------------------------------------------------------------------
// Value_wxMultiChoiceDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxMultiChoiceDialog : public Value_wxDialog {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxMultiChoiceDialog);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxMultiChoiceDialog");
protected:
	wxWeakRef<wxMultiChoiceDialog> _pEntity;
public:
	class EntityT : public wxMultiChoiceDialog {
	public:
		using wxMultiChoiceDialog::wxMultiChoiceDialog;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxMultiChoiceDialog() = delete;
	explicit Value_wxMultiChoiceDialog(wxMultiChoiceDialog* pEntity, VType& vtype = VTYPE_wxMultiChoiceDialog) :
		Value_wxDialog(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxMultiChoiceDialog(const Value_wxMultiChoiceDialog& src) = delete;
	Value_wxMultiChoiceDialog& operator=(const Value_wxMultiChoiceDialog& src) = delete;
	// Move constructor/operator
	Value_wxMultiChoiceDialog(Value_wxMultiChoiceDialog&& src) noexcept = delete;
	Value_wxMultiChoiceDialog& operator=(Value_wxMultiChoiceDialog&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxMultiChoiceDialog() = default;
public:
	wxMultiChoiceDialog& GetEntity() { return *_pEntity; }
	const wxMultiChoiceDialog& GetEntity() const { return *_pEntity; }
	wxMultiChoiceDialog* GetEntityPtr() { return _pEntity.get(); }
	const wxMultiChoiceDialog* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxMultiChoiceDialog& GetEntity(Value& value) {
		return dynamic_cast<Value_wxMultiChoiceDialog&>(value).GetEntity();
	}
	static const wxMultiChoiceDialog& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxMultiChoiceDialog&>(value).GetEntity();
	}
	static wxMultiChoiceDialog* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxMultiChoiceDialog&>(value).GetEntityPtr();
	}
	static const wxMultiChoiceDialog* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxMultiChoiceDialog&>(value).GetEntityPtr();
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