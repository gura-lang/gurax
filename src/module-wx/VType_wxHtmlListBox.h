//==============================================================================
// VType_wxHtmlListBox.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXHTMLLISTBOX_H
#define GURAX_MODULE_WX_VTYPE_WXHTMLLISTBOX_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/htmllbox.h>
#include "Util.h"
#include "VType_wxVListBox.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxHtmlListBox
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxHtmlListBox : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxHtmlListBox VTYPE_wxHtmlListBox;

//------------------------------------------------------------------------------
// Value_wxHtmlListBox
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxHtmlListBox : public Value_wxVListBox {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxHtmlListBox);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxHtmlListBox");
protected:
	wxWeakRef<wxHtmlListBox> _pEntity;
public:
	class EntityT : public wxHtmlListBox {
	public:
		using wxHtmlListBox::wxHtmlListBox;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxHtmlListBox() = delete;
	explicit Value_wxHtmlListBox(wxHtmlListBox* pEntity, VType& vtype = VTYPE_wxHtmlListBox) :
		Value_wxVListBox(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxHtmlListBox(const Value_wxHtmlListBox& src) = delete;
	Value_wxHtmlListBox& operator=(const Value_wxHtmlListBox& src) = delete;
	// Move constructor/operator
	Value_wxHtmlListBox(Value_wxHtmlListBox&& src) noexcept = delete;
	Value_wxHtmlListBox& operator=(Value_wxHtmlListBox&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxHtmlListBox() = default;
public:
	wxHtmlListBox& GetEntity() { return *_pEntity; }
	const wxHtmlListBox& GetEntity() const { return *_pEntity; }
	wxHtmlListBox* GetEntityPtr() { return _pEntity.get(); }
	const wxHtmlListBox* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxHtmlListBox& GetEntity(Value& value) {
		return dynamic_cast<Value_wxHtmlListBox&>(value).GetEntity();
	}
	static const wxHtmlListBox& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxHtmlListBox&>(value).GetEntity();
	}
	static wxHtmlListBox* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxHtmlListBox&>(value).GetEntityPtr();
	}
	static const wxHtmlListBox* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxHtmlListBox&>(value).GetEntityPtr();
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
