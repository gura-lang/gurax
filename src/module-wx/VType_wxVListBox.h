//==============================================================================
// VType_wxVListBox.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXVLISTBOX_H
#define GURAX_MODULE_WX_VTYPE_WXVLISTBOX_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/vlbox.h>
#include "Util.h"
#include "VType_wxVScrolledWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxVListBox
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxVListBox : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxVListBox VTYPE_wxVListBox;

//------------------------------------------------------------------------------
// Value_wxVListBox
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxVListBox : public Value_wxVScrolledWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxVListBox);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxVListBox");
protected:
	wxWeakRef<wxVListBox> _pEntity;
public:
	class EntityT : public wxVListBox {
	public:
		using wxVListBox::wxVListBox;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxVListBox() = delete;
	explicit Value_wxVListBox(wxVListBox* pEntity, VType& vtype = VTYPE_wxVListBox) :
		Value_wxVScrolledWindow(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxVListBox(const Value_wxVListBox& src) = delete;
	Value_wxVListBox& operator=(const Value_wxVListBox& src) = delete;
	// Move constructor/operator
	Value_wxVListBox(Value_wxVListBox&& src) noexcept = delete;
	Value_wxVListBox& operator=(Value_wxVListBox&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxVListBox() = default;
public:
	wxVListBox& GetEntity() { return *_pEntity; }
	const wxVListBox& GetEntity() const { return *_pEntity; }
	wxVListBox* GetEntityPtr() { return _pEntity.get(); }
	const wxVListBox* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxVListBox& GetEntity(Value& value) {
		return dynamic_cast<Value_wxVListBox&>(value).GetEntity();
	}
	static const wxVListBox& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxVListBox&>(value).GetEntity();
	}
	static wxVListBox* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxVListBox&>(value).GetEntityPtr();
	}
	static const wxVListBox* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxVListBox&>(value).GetEntityPtr();
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
