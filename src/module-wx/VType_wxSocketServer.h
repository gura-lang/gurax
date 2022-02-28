//==============================================================================
// VType_wxSocketServer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSOCKETSERVER_H
#define GURAX_MODULE_WX_VTYPE_WXSOCKETSERVER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/socket.h>
#include "Util.h"
#include "VType_wxSocketBase.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSocketServer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSocketServer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSocketServer VTYPE_wxSocketServer;

//------------------------------------------------------------------------------
// Value_wxSocketServer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSocketServer : public Value_wxSocketBase {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSocketServer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSocketServer");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxSocketServer() = delete;
	explicit Value_wxSocketServer(const wxSocketServer& entity, VType& vtype = VTYPE_wxSocketServer) :
		Value_wxSocketBase(entity, vtype) {}
	// Copy constructor/operator
	Value_wxSocketServer(const Value_wxSocketServer& src) = delete;
	Value_wxSocketServer& operator=(const Value_wxSocketServer& src) = delete;
	// Move constructor/operator
	Value_wxSocketServer(Value_wxSocketServer&& src) noexcept = delete;
	Value_wxSocketServer& operator=(Value_wxSocketServer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSocketServer() = default;
public:
	wxSocketServer& GetEntity() { return reinterpret_cast<wxSocketServer&>(Value_wxSocketBase::GetEntity()); }
	const wxSocketServer& GetEntity() const { return reinterpret_cast<const wxSocketServer&>(Value_wxSocketBase::GetEntity()); }
	wxSocketServer* GetEntityPtr() { return reinterpret_cast<wxSocketServer*>(Value_wxSocketBase::GetEntityPtr()); }\
	const wxSocketServer* GetEntityPtr() const { return reinterpret_cast<const wxSocketServer*>(Value_wxSocketBase::GetEntityPtr()); }
public:
	static wxSocketServer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSocketServer&>(value).GetEntity();
	}
	static const wxSocketServer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSocketServer&>(value).GetEntity();
	}
	static wxSocketServer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSocketServer&>(value).GetEntityPtr();
	}
	static const wxSocketServer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSocketServer&>(value).GetEntityPtr();
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
