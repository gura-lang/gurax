//==============================================================================
// VType_wxEventLoopBase.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXEVENTLOOPBASE_H
#define GURAX_MODULE_WX_VTYPE_WXEVENTLOOPBASE_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/evtloop.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxEventLoopBase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxEventLoopBase : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxEventLoopBase VTYPE_wxEventLoopBase;

//------------------------------------------------------------------------------
// Value_wxEventLoopBase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxEventLoopBase : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxEventLoopBase);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxEventLoopBase");
protected:
	wxEventLoopBase* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxEventLoopBase() = delete;
	explicit Value_wxEventLoopBase(wxEventLoopBase* pEntity, VType& vtype = VTYPE_wxEventLoopBase) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxEventLoopBase(const wxEventLoopBase& entity, VType& vtype = VTYPE_wxEventLoopBase) :
		Value_Object(vtype), _pEntity(const_cast<wxEventLoopBase*>(&entity)) {}
	// Copy constructor/operator
	Value_wxEventLoopBase(const Value_wxEventLoopBase& src) = delete;
	Value_wxEventLoopBase& operator=(const Value_wxEventLoopBase& src) = delete;
	// Move constructor/operator
	Value_wxEventLoopBase(Value_wxEventLoopBase&& src) noexcept = delete;
	Value_wxEventLoopBase& operator=(Value_wxEventLoopBase&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxEventLoopBase() = default;
public:
	wxEventLoopBase& GetEntity() { return *_pEntity; }
	const wxEventLoopBase& GetEntity() const { return *_pEntity; }
	wxEventLoopBase* GetEntityPtr() { return _pEntity; }
	const wxEventLoopBase* GetEntityPtr() const { return _pEntity; }
public:
	static wxEventLoopBase& GetEntity(Value& value) {
		return dynamic_cast<Value_wxEventLoopBase&>(value).GetEntity();
	}
	static const wxEventLoopBase& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxEventLoopBase&>(value).GetEntity();
	}
	static wxEventLoopBase* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxEventLoopBase&>(value).GetEntityPtr();
	}
	static const wxEventLoopBase* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxEventLoopBase&>(value).GetEntityPtr();
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
