//==============================================================================
// VType_wxHtmlHelpDialog.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXHTMLHELPDIALOG_H
#define GURAX_MODULE_WX_VTYPE_WXHTMLHELPDIALOG_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/html/helpdlg.h>
#include "Util.h"
#include "VType_wxDialog.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxHtmlHelpDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxHtmlHelpDialog : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxHtmlHelpDialog VTYPE_wxHtmlHelpDialog;

//------------------------------------------------------------------------------
// Value_wxHtmlHelpDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxHtmlHelpDialog : public Value_wxDialog {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxHtmlHelpDialog);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxHtmlHelpDialog");
protected:
	wxWeakRef<wxHtmlHelpDialog> _pEntity;
public:
	class EntityT : public wxHtmlHelpDialog {
	public:
		using wxHtmlHelpDialog::wxHtmlHelpDialog;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxHtmlHelpDialog() = delete;
	explicit Value_wxHtmlHelpDialog(wxHtmlHelpDialog* pEntity, VType& vtype = VTYPE_wxHtmlHelpDialog) :
		Value_wxDialog(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxHtmlHelpDialog(const Value_wxHtmlHelpDialog& src) = delete;
	Value_wxHtmlHelpDialog& operator=(const Value_wxHtmlHelpDialog& src) = delete;
	// Move constructor/operator
	Value_wxHtmlHelpDialog(Value_wxHtmlHelpDialog&& src) noexcept = delete;
	Value_wxHtmlHelpDialog& operator=(Value_wxHtmlHelpDialog&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxHtmlHelpDialog() = default;
public:
	wxHtmlHelpDialog& GetEntity() { return *_pEntity; }
	const wxHtmlHelpDialog& GetEntity() const { return *_pEntity; }
	wxHtmlHelpDialog* GetEntityPtr() { return _pEntity.get(); }
	const wxHtmlHelpDialog* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxHtmlHelpDialog& GetEntity(Value& value) {
		return dynamic_cast<Value_wxHtmlHelpDialog&>(value).GetEntity();
	}
	static const wxHtmlHelpDialog& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxHtmlHelpDialog&>(value).GetEntity();
	}
	static wxHtmlHelpDialog* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxHtmlHelpDialog&>(value).GetEntityPtr();
	}
	static const wxHtmlHelpDialog* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxHtmlHelpDialog&>(value).GetEntityPtr();
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
