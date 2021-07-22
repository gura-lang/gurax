//==============================================================================
// VType_wxListItem.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXLISTITEM_H
#define GURAX_MODULE_WX_VTYPE_WXLISTITEM_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "Util.h"
#include "VType_wxObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxListItem
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxListItem : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxListItem VTYPE_wxListItem;

//------------------------------------------------------------------------------
// Value_wxListItem
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxListItem : public Value_wxObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxListItem);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxListItem");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxListItem() = delete;
	explicit Value_wxListItem(const wxObject& entity, VType& vtype = VTYPE_wxListItem) :
		Value_wxObject(entity, vtype) {}
	// Copy constructor/operator
	Value_wxListItem(const Value_wxListItem& src) = delete;
	Value_wxListItem& operator=(const Value_wxListItem& src) = delete;
	// Move constructor/operator
	Value_wxListItem(Value_wxListItem&& src) noexcept = delete;
	Value_wxListItem& operator=(Value_wxListItem&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxListItem() = default;
public:
	wxListItem& GetEntity() {
		return reinterpret_cast<wxListItem&>(Value_wxObject::GetEntity());
	}
	const wxListItem& GetEntity() const {
		return reinterpret_cast<const wxListItem&>(Value_wxObject::GetEntity());
	}
	wxListItem* GetEntityPtr() {
		return reinterpret_cast<wxListItem*>(Value_wxObject::GetEntityPtr());
	}
	const wxListItem* GetEntityPtr() const {
		return reinterpret_cast<const wxListItem*>(Value_wxObject::GetEntityPtr());
	}
public:
	static wxListItem& GetEntity(Value& value) {
		return dynamic_cast<Value_wxListItem&>(value).GetEntity();
	}
	static const wxListItem& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxListItem&>(value).GetEntity();
	}
	static wxListItem* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxListItem&>(value).GetEntityPtr();
	}
	static const wxListItem* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxListItem&>(value).GetEntityPtr();
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
