//==============================================================================
// VType_wxWizardPage.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXWIZARDPAGE_H
#define GURAX_MODULE_WX_VTYPE_WXWIZARDPAGE_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/wizard.h>
#include "Util.h"
#include "VType_wxPanel.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxWizardPage
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxWizardPage : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxWizardPage VTYPE_wxWizardPage;

//------------------------------------------------------------------------------
// Value_wxWizardPage
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxWizardPage : public Value_wxPanel {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxWizardPage);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxWizardPage");
protected:
	wxWeakRef<wxWizardPage> _pEntity;
public:
	class EntityT : public wxWizardPage {
	public:
		using wxWizardPage::wxWizardPage;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxWizardPage() = delete;
	explicit Value_wxWizardPage(wxWizardPage* pEntity, VType& vtype = VTYPE_wxWizardPage) :
		Value_wxPanel(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxWizardPage(const Value_wxWizardPage& src) = delete;
	Value_wxWizardPage& operator=(const Value_wxWizardPage& src) = delete;
	// Move constructor/operator
	Value_wxWizardPage(Value_wxWizardPage&& src) noexcept = delete;
	Value_wxWizardPage& operator=(Value_wxWizardPage&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxWizardPage() = default;
public:
	wxWizardPage& GetEntity() { return *_pEntity; }
	const wxWizardPage& GetEntity() const { return *_pEntity; }
	wxWizardPage* GetEntityPtr() { return _pEntity.get(); }
	const wxWizardPage* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxWizardPage& GetEntity(Value& value) {
		return dynamic_cast<Value_wxWizardPage&>(value).GetEntity();
	}
	static const wxWizardPage& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxWizardPage&>(value).GetEntity();
	}
	static wxWizardPage* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxWizardPage&>(value).GetEntityPtr();
	}
	static const wxWizardPage* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxWizardPage&>(value).GetEntityPtr();
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
