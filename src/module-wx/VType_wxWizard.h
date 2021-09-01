//==============================================================================
// VType_wxWizard.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXWIZARD_H
#define GURAX_MODULE_WX_VTYPE_WXWIZARD_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/wizard.h>
#include "Util.h"
#include "VType_wxDialog.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxWizard
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxWizard : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxWizard VTYPE_wxWizard;

//------------------------------------------------------------------------------
// Value_wxWizard
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxWizard : public Value_wxDialog {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxWizard);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxWizard");
protected:
	wxWeakRef<wxWizard> _pEntity;
public:
	class EntityT : public wxWizard {
	public:
		using wxWizard::wxWizard;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxWizard() = delete;
	explicit Value_wxWizard(wxWizard* pEntity, VType& vtype = VTYPE_wxWizard) :
		Value_wxDialog(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxWizard(const Value_wxWizard& src) = delete;
	Value_wxWizard& operator=(const Value_wxWizard& src) = delete;
	// Move constructor/operator
	Value_wxWizard(Value_wxWizard&& src) noexcept = delete;
	Value_wxWizard& operator=(Value_wxWizard&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxWizard() = default;
public:
	wxWizard& GetEntity() { return *_pEntity; }
	const wxWizard& GetEntity() const { return *_pEntity; }
	wxWizard* GetEntityPtr() { return _pEntity.get(); }
	const wxWizard* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxWizard& GetEntity(Value& value) {
		return dynamic_cast<Value_wxWizard&>(value).GetEntity();
	}
	static const wxWizard& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxWizard&>(value).GetEntity();
	}
	static wxWizard* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxWizard&>(value).GetEntityPtr();
	}
	static const wxWizard* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxWizard&>(value).GetEntityPtr();
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