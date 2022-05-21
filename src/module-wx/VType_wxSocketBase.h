//==============================================================================
// VType_wxSocketBase.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSOCKETBASE_H
#define GURAX_MODULE_WX_VTYPE_WXSOCKETBASE_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/socket.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSocketBase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSocketBase : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSocketBase VTYPE_wxSocketBase;

//------------------------------------------------------------------------------
// Value_wxSocketBase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSocketBase : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSocketBase);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSocketBase");
protected:
	wxSocketBase* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxSocketBase() = delete;
	explicit Value_wxSocketBase(wxSocketBase* pEntity, VType& vtype = VTYPE_wxSocketBase) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxSocketBase(const wxSocketBase& entity, VType& vtype = VTYPE_wxSocketBase) :
		Value_Object(vtype), _pEntity(const_cast<wxSocketBase*>(&entity)) {}
	// Copy constructor/operator
	Value_wxSocketBase(const Value_wxSocketBase& src) = delete;
	Value_wxSocketBase& operator=(const Value_wxSocketBase& src) = delete;
	// Move constructor/operator
	Value_wxSocketBase(Value_wxSocketBase&& src) noexcept = delete;
	Value_wxSocketBase& operator=(Value_wxSocketBase&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSocketBase() = default;
public:
	wxSocketBase& GetEntity() { return *_pEntity; }
	const wxSocketBase& GetEntity() const { return *_pEntity; }
	wxSocketBase* GetEntityPtr() { return _pEntity; }
	const wxSocketBase* GetEntityPtr() const { return _pEntity; }
public:
	static wxSocketBase& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSocketBase&>(value).GetEntity();
	}
	static const wxSocketBase& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSocketBase&>(value).GetEntity();
	}
	static wxSocketBase* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSocketBase&>(value).GetEntityPtr();
	}
	static const wxSocketBase* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSocketBase&>(value).GetEntityPtr();
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
