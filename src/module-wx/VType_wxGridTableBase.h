//==============================================================================
// VType_wxGridTableBase.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDTABLEBASE_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDTABLEBASE_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"
#include "VType_wxObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridTableBase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridTableBase : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridTableBase VTYPE_wxGridTableBase;

//------------------------------------------------------------------------------
// Value_wxGridTableBase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridTableBase : public Value_wxObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridTableBase);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridTableBase");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridTableBase() = delete;
	explicit Value_wxGridTableBase(const wxGridTableBase& entity, VType& vtype = VTYPE_wxGridTableBase) :
		Value_wxObject(entity, vtype) {}
	// Copy constructor/operator
	Value_wxGridTableBase(const Value_wxGridTableBase& src) = delete;
	Value_wxGridTableBase& operator=(const Value_wxGridTableBase& src) = delete;
	// Move constructor/operator
	Value_wxGridTableBase(Value_wxGridTableBase&& src) noexcept = delete;
	Value_wxGridTableBase& operator=(Value_wxGridTableBase&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridTableBase() = default;
public:
	wxGridTableBase& GetEntity() { return reinterpret_cast<wxGridTableBase&>(Value_wxObject::GetEntity()); }
	const wxGridTableBase& GetEntity() const { return reinterpret_cast<const wxGridTableBase&>(Value_wxObject::GetEntity()); }
	wxGridTableBase* GetEntityPtr() { return reinterpret_cast<wxGridTableBase*>(Value_wxObject::GetEntityPtr()); }\
	const wxGridTableBase* GetEntityPtr() const { return reinterpret_cast<const wxGridTableBase*>(Value_wxObject::GetEntityPtr()); }
public:
	static wxGridTableBase& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridTableBase&>(value).GetEntity();
	}
	static const wxGridTableBase& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridTableBase&>(value).GetEntity();
	}
	static wxGridTableBase* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridTableBase&>(value).GetEntityPtr();
	}
	static const wxGridTableBase* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridTableBase&>(value).GetEntityPtr();
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