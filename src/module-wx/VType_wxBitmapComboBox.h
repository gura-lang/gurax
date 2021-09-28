//==============================================================================
// VType_wxBitmapComboBox.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXBITMAPCOMBOBOX_H
#define GURAX_MODULE_WX_VTYPE_WXBITMAPCOMBOBOX_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/bmpcbox.h>
#include "Util.h"
#include "VType_wxComboBox.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxBitmapComboBox
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxBitmapComboBox : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxBitmapComboBox VTYPE_wxBitmapComboBox;

//------------------------------------------------------------------------------
// Value_wxBitmapComboBox
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxBitmapComboBox : public Value_wxComboBox {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxBitmapComboBox);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxBitmapComboBox");
protected:
	wxWeakRef<wxBitmapComboBox> _pEntity;
public:
	class EntityT : public wxBitmapComboBox {
	public:
		using wxBitmapComboBox::wxBitmapComboBox;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxBitmapComboBox() = delete;
	explicit Value_wxBitmapComboBox(wxBitmapComboBox* pEntity, VType& vtype = VTYPE_wxBitmapComboBox) :
		Value_wxComboBox(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxBitmapComboBox(const Value_wxBitmapComboBox& src) = delete;
	Value_wxBitmapComboBox& operator=(const Value_wxBitmapComboBox& src) = delete;
	// Move constructor/operator
	Value_wxBitmapComboBox(Value_wxBitmapComboBox&& src) noexcept = delete;
	Value_wxBitmapComboBox& operator=(Value_wxBitmapComboBox&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxBitmapComboBox() = default;
public:
	wxBitmapComboBox& GetEntity() { return *_pEntity; }
	const wxBitmapComboBox& GetEntity() const { return *_pEntity; }
	wxBitmapComboBox* GetEntityPtr() { return _pEntity.get(); }
	const wxBitmapComboBox* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxBitmapComboBox& GetEntity(Value& value) {
		return dynamic_cast<Value_wxBitmapComboBox&>(value).GetEntity();
	}
	static const wxBitmapComboBox& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxBitmapComboBox&>(value).GetEntity();
	}
	static wxBitmapComboBox* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxBitmapComboBox&>(value).GetEntityPtr();
	}
	static const wxBitmapComboBox* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxBitmapComboBox&>(value).GetEntityPtr();
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