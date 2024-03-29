﻿//==============================================================================
// VType_wxItemContainer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXITEMCONTAINER_H
#define GURAX_MODULE_WX_VTYPE_WXITEMCONTAINER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxItemContainer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxItemContainer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxItemContainer VTYPE_wxItemContainer;

//------------------------------------------------------------------------------
// Value_wxItemContainer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxItemContainer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxItemContainer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxItemContainer");
protected:
	wxItemContainer* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxItemContainer() = delete;
	explicit Value_wxItemContainer(wxItemContainer* pEntity, VType& vtype = VTYPE_wxItemContainer) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxItemContainer(const wxItemContainer& entity, VType& vtype = VTYPE_wxItemContainer) :
		Value_Object(vtype), _pEntity(const_cast<wxItemContainer*>(&entity)) {}
	// Copy constructor/operator
	Value_wxItemContainer(const Value_wxItemContainer& src) = delete;
	Value_wxItemContainer& operator=(const Value_wxItemContainer& src) = delete;
	// Move constructor/operator
	Value_wxItemContainer(Value_wxItemContainer&& src) noexcept = delete;
	Value_wxItemContainer& operator=(Value_wxItemContainer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxItemContainer() = default;
public:
	wxItemContainer& GetEntity() { return *_pEntity; }
	const wxItemContainer& GetEntity() const { return *_pEntity; }
	wxItemContainer* GetEntityPtr() { return _pEntity; }
	const wxItemContainer* GetEntityPtr() const { return _pEntity; }
public:
	static wxItemContainer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxItemContainer&>(value).GetEntity();
	}
	static const wxItemContainer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxItemContainer&>(value).GetEntity();
	}
	static wxItemContainer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxItemContainer&>(value).GetEntityPtr();
	}
	static const wxItemContainer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxItemContainer&>(value).GetEntityPtr();
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
