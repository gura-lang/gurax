//==============================================================================
// VType_wxColourDialog.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCOLOURDIALOG_H
#define GURAX_MODULE_WX_VTYPE_WXCOLOURDIALOG_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/colordlg.h>
#include "Util.h"
#include "VType_wxDialog.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxColourDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxColourDialog : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxColourDialog VTYPE_wxColourDialog;

//------------------------------------------------------------------------------
// Value_wxColourDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxColourDialog : public Value_wxDialog {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxColourDialog);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxColourDialog");
protected:
	wxWeakRef<wxColourDialog> _pEntity;
public:
	class EntityT : public wxColourDialog {
	public:
		using wxColourDialog::wxColourDialog;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxColourDialog() = delete;
	explicit Value_wxColourDialog(wxColourDialog* pEntity, VType& vtype = VTYPE_wxColourDialog) :
		Value_wxDialog(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxColourDialog(const Value_wxColourDialog& src) = delete;
	Value_wxColourDialog& operator=(const Value_wxColourDialog& src) = delete;
	// Move constructor/operator
	Value_wxColourDialog(Value_wxColourDialog&& src) noexcept = delete;
	Value_wxColourDialog& operator=(Value_wxColourDialog&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxColourDialog() = default;
public:
	wxColourDialog& GetEntity() { return *_pEntity; }
	const wxColourDialog& GetEntity() const { return *_pEntity; }
	wxColourDialog* GetEntityPtr() { return _pEntity.get(); }
	const wxColourDialog* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxColourDialog& GetEntity(Value& value) {
		return dynamic_cast<Value_wxColourDialog&>(value).GetEntity();
	}
	static const wxColourDialog& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxColourDialog&>(value).GetEntity();
	}
	static wxColourDialog* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxColourDialog&>(value).GetEntityPtr();
	}
	static const wxColourDialog* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxColourDialog&>(value).GetEntityPtr();
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
