//==============================================================================
// VType_MenuItem.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_MenuItem_H
#define GURAX_MODULE_WX_VTYPE_MenuItem_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_MenuItem
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_MenuItem : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_MenuItem VTYPE_MenuItem;

//------------------------------------------------------------------------------
// Value_MenuItem
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_MenuItem : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_MenuItem);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_MenuItem");
public:
	class EntityT : public wxMenuItem {
	public:
		using EntitySuper = wxMenuItem;
		using wxMenuItem::wxMenuItem;
	public:
		EntityCore core;
	};
protected:
	wxMenuItem* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_MenuItem() = delete;
	explicit Value_MenuItem(wxMenuItem* pEntity, VType& vtype = VTYPE_MenuItem) :
		Value_Object(vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_MenuItem(const Value_MenuItem& src) = delete;
	Value_MenuItem& operator=(const Value_MenuItem& src) = delete;
	// Move constructor/operator
	Value_MenuItem(Value_MenuItem&& src) noexcept = delete;
	Value_MenuItem& operator=(Value_MenuItem&& src) noexcept = delete;
protected:
	// Destructor
	~Value_MenuItem() = default;
public:
	wxMenuItem* GetEntity() { return _pEntity; }
	const wxMenuItem* GetEntity() const { return _pEntity; }
public:
	static wxMenuItem* GetEntity(Value& value) {
		return dynamic_cast<Value_MenuItem&>(value).GetEntity();
	}
	static const wxMenuItem* GetEntity(const Value& value) {
		return dynamic_cast<const Value_MenuItem&>(value).GetEntity();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntity(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntity(*this) == GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(GetEntity(*this) < GetEntity(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif
