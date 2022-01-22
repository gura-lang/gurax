//==============================================================================
// VType_wxComboBox.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCOMBOBOX_H
#define GURAX_MODULE_WX_VTYPE_WXCOMBOBOX_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/combobox.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxComboBox
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxComboBox : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxComboBox VTYPE_wxComboBox;

//------------------------------------------------------------------------------
// Value_wxComboBox
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxComboBox : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxComboBox);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxComboBox");
protected:
	wxWeakRef<wxComboBox> _pEntity;
public:
	class EntityT : public wxComboBox {
	public:
		using wxComboBox::wxComboBox;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxComboBox() = delete;
	explicit Value_wxComboBox(wxComboBox* pEntity, VType& vtype = VTYPE_wxComboBox) :
		Value_wxControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxComboBox(const Value_wxComboBox& src) = delete;
	Value_wxComboBox& operator=(const Value_wxComboBox& src) = delete;
	// Move constructor/operator
	Value_wxComboBox(Value_wxComboBox&& src) noexcept = delete;
	Value_wxComboBox& operator=(Value_wxComboBox&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxComboBox() = default;
public:
	wxComboBox& GetEntity() { return *_pEntity; }
	const wxComboBox& GetEntity() const { return *_pEntity; }
	wxComboBox* GetEntityPtr() { return _pEntity.get(); }
	const wxComboBox* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxComboBox& GetEntity(Value& value) {
		return dynamic_cast<Value_wxComboBox&>(value).GetEntity();
	}
	static const wxComboBox& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxComboBox&>(value).GetEntity();
	}
	static wxComboBox* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxComboBox&>(value).GetEntityPtr();
	}
	static const wxComboBox* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxComboBox&>(value).GetEntityPtr();
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
