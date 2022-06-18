//==============================================================================
// VType_wxAccessible.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXACCESSIBLE_H
#define GURAX_MODULE_WX_VTYPE_WXACCESSIBLE_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/accel.h>
#include "Util.h"
#include "VType_wxObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxAccessible
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxAccessible : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxAccessible VTYPE_wxAccessible;

//------------------------------------------------------------------------------
// Value_wxAccessible
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxAccessible : public Value_wxObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAccessible);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAccessible");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxAccessible() = delete;
	explicit Value_wxAccessible(const wxAccessible& entity, VType& vtype = VTYPE_wxAccessible) :
		Value_wxObject(entity, vtype) {}
	// Copy constructor/operator
	Value_wxAccessible(const Value_wxAccessible& src) = delete;
	Value_wxAccessible& operator=(const Value_wxAccessible& src) = delete;
	// Move constructor/operator
	Value_wxAccessible(Value_wxAccessible&& src) noexcept = delete;
	Value_wxAccessible& operator=(Value_wxAccessible&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxAccessible() = default;
public:
	wxAccessible& GetEntity() { return reinterpret_cast<wxAccessible&>(Value_wxObject::GetEntity()); }
	const wxAccessible& GetEntity() const { return reinterpret_cast<const wxAccessible&>(Value_wxObject::GetEntity()); }
	wxAccessible* GetEntityPtr() { return reinterpret_cast<wxAccessible*>(Value_wxObject::GetEntityPtr()); }\
	const wxAccessible* GetEntityPtr() const { return reinterpret_cast<const wxAccessible*>(Value_wxObject::GetEntityPtr()); }
public:
	static wxAccessible& GetEntity(Value& value) {
		return dynamic_cast<Value_wxAccessible&>(value).GetEntity();
	}
	static const wxAccessible& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAccessible&>(value).GetEntity();
	}
	static wxAccessible* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxAccessible&>(value).GetEntityPtr();
	}
	static const wxAccessible* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxAccessible&>(value).GetEntityPtr();
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
