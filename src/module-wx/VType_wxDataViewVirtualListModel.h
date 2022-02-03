//==============================================================================
// VType_wxDataViewVirtualListModel.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXDATAVIEWVIRTUALLISTMODEL_H
#define GURAX_MODULE_WX_VTYPE_WXDATAVIEWVIRTUALLISTMODEL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dataview.h>
#include "Util.h"
#include "VType_wxDataViewListModel.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxDataViewVirtualListModel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxDataViewVirtualListModel : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxDataViewVirtualListModel VTYPE_wxDataViewVirtualListModel;

//------------------------------------------------------------------------------
// Value_wxDataViewVirtualListModel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxDataViewVirtualListModel : public Value_wxDataViewListModel {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxDataViewVirtualListModel);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxDataViewVirtualListModel");
protected:
	wxDataViewVirtualListModel* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxDataViewVirtualListModel() = delete;
	explicit Value_wxDataViewVirtualListModel(wxDataViewVirtualListModel* pEntity, VType& vtype = VTYPE_wxDataViewVirtualListModel) :
		Value_wxDataViewListModel(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxDataViewVirtualListModel(const Value_wxDataViewVirtualListModel& src) = delete;
	Value_wxDataViewVirtualListModel& operator=(const Value_wxDataViewVirtualListModel& src) = delete;
	// Move constructor/operator
	Value_wxDataViewVirtualListModel(Value_wxDataViewVirtualListModel&& src) noexcept = delete;
	Value_wxDataViewVirtualListModel& operator=(Value_wxDataViewVirtualListModel&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxDataViewVirtualListModel() = default;
public:
	wxDataViewVirtualListModel& GetEntity() { return *_pEntity; }
	const wxDataViewVirtualListModel& GetEntity() const { return *_pEntity; }
	wxDataViewVirtualListModel* GetEntityPtr() { return _pEntity; }
	const wxDataViewVirtualListModel* GetEntityPtr() const { return _pEntity; }
public:
	static wxDataViewVirtualListModel& GetEntity(Value& value) {
		return dynamic_cast<Value_wxDataViewVirtualListModel&>(value).GetEntity();
	}
	static const wxDataViewVirtualListModel& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxDataViewVirtualListModel&>(value).GetEntity();
	}
	static wxDataViewVirtualListModel* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxDataViewVirtualListModel&>(value).GetEntityPtr();
	}
	static const wxDataViewVirtualListModel* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxDataViewVirtualListModel&>(value).GetEntityPtr();
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