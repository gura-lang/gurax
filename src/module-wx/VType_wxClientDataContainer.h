//==============================================================================
// VType_wxClientDataContainer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCLIENTDATACONTAINER_H
#define GURAX_MODULE_WX_VTYPE_WXCLIENTDATACONTAINER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxClientDataContainer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxClientDataContainer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxClientDataContainer VTYPE_wxClientDataContainer;

//------------------------------------------------------------------------------
// Value_wxClientDataContainer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxClientDataContainer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxClientDataContainer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxClientDataContainer");
protected:
	wxClientDataContainer _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxClientDataContainer() = delete;
	explicit Value_wxClientDataContainer(const wxClientDataContainer& entity, VType& vtype = VTYPE_wxClientDataContainer) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxClientDataContainer(const Value_wxClientDataContainer& src) = delete;
	Value_wxClientDataContainer& operator=(const Value_wxClientDataContainer& src) = delete;
	// Move constructor/operator
	Value_wxClientDataContainer(Value_wxClientDataContainer&& src) noexcept = delete;
	Value_wxClientDataContainer& operator=(Value_wxClientDataContainer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxClientDataContainer() = default;
public:
	wxClientDataContainer& GetEntity() { return _entity; }
	const wxClientDataContainer& GetEntity() const { return _entity; }
	wxClientDataContainer* GetEntityPtr() { return &_entity; }
	const wxClientDataContainer* GetEntityPtr() const { return &_entity; }
public:
	static wxClientDataContainer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxClientDataContainer&>(value).GetEntity();
	}
	static const wxClientDataContainer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxClientDataContainer&>(value).GetEntity();
	}
	static wxClientDataContainer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxClientDataContainer&>(value).GetEntityPtr();
	}
	static const wxClientDataContainer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxClientDataContainer&>(value).GetEntityPtr();
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