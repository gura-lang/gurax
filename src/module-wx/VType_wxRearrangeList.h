//==============================================================================
// VType_wxRearrangeList.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXREARRANGELIST_H
#define GURAX_MODULE_WX_VTYPE_WXREARRANGELIST_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/rearrangectrl.h>
#include "Util.h"
#include "VType_wxCheckListBox.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRearrangeList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRearrangeList : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRearrangeList VTYPE_wxRearrangeList;

//------------------------------------------------------------------------------
// Value_wxRearrangeList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRearrangeList : public Value_wxCheckListBox {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRearrangeList);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRearrangeList");
protected:
	wxWeakRef<wxRearrangeList> _pEntity;
public:
	class EntityT : public wxRearrangeList {
	public:
		using wxRearrangeList::wxRearrangeList;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRearrangeList() = delete;
	explicit Value_wxRearrangeList(wxRearrangeList* pEntity, VType& vtype = VTYPE_wxRearrangeList) :
		Value_wxCheckListBox(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxRearrangeList(const Value_wxRearrangeList& src) = delete;
	Value_wxRearrangeList& operator=(const Value_wxRearrangeList& src) = delete;
	// Move constructor/operator
	Value_wxRearrangeList(Value_wxRearrangeList&& src) noexcept = delete;
	Value_wxRearrangeList& operator=(Value_wxRearrangeList&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRearrangeList() = default;
public:
	wxRearrangeList& GetEntity() { return *_pEntity; }
	const wxRearrangeList& GetEntity() const { return *_pEntity; }
	wxRearrangeList* GetEntityPtr() { return _pEntity.get(); }
	const wxRearrangeList* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxRearrangeList& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRearrangeList&>(value).GetEntity();
	}
	static const wxRearrangeList& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRearrangeList&>(value).GetEntity();
	}
	static wxRearrangeList* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRearrangeList&>(value).GetEntityPtr();
	}
	static const wxRearrangeList* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRearrangeList&>(value).GetEntityPtr();
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