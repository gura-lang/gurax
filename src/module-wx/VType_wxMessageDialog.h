//==============================================================================
// VType_wxMessageDialog.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXMESSAGEDIALOG_H
#define GURAX_MODULE_WX_VTYPE_WXMESSAGEDIALOG_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/msgdlg.h>
#include "Util.h"
#include "VType_wxDialog.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxMessageDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxMessageDialog : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxMessageDialog VTYPE_wxMessageDialog;

//------------------------------------------------------------------------------
// Value_wxMessageDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxMessageDialog : public Value_wxDialog {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxMessageDialog);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxMessageDialog");
protected:
	wxWeakRef<wxMessageDialog> _pEntity;
public:
	class EntityT : public wxMessageDialog {
	public:
		using wxMessageDialog::wxMessageDialog;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxMessageDialog() = delete;
	explicit Value_wxMessageDialog(wxMessageDialog* pEntity, VType& vtype = VTYPE_wxMessageDialog) :
		Value_wxDialog(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxMessageDialog(const Value_wxMessageDialog& src) = delete;
	Value_wxMessageDialog& operator=(const Value_wxMessageDialog& src) = delete;
	// Move constructor/operator
	Value_wxMessageDialog(Value_wxMessageDialog&& src) noexcept = delete;
	Value_wxMessageDialog& operator=(Value_wxMessageDialog&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxMessageDialog() = default;
public:
	wxMessageDialog& GetEntity() { return *_pEntity; }
	const wxMessageDialog& GetEntity() const { return *_pEntity; }
	wxMessageDialog* GetEntityPtr() { return _pEntity.get(); }
	const wxMessageDialog* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxMessageDialog& GetEntity(Value& value) {
		return dynamic_cast<Value_wxMessageDialog&>(value).GetEntity();
	}
	static const wxMessageDialog& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxMessageDialog&>(value).GetEntity();
	}
	static wxMessageDialog* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxMessageDialog&>(value).GetEntityPtr();
	}
	static const wxMessageDialog* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxMessageDialog&>(value).GetEntityPtr();
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
