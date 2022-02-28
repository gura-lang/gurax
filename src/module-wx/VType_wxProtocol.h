//==============================================================================
// VType_wxProtocol.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPROTOCOL_H
#define GURAX_MODULE_WX_VTYPE_WXPROTOCOL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/protocol/protocol.h>
#include "Util.h"
#include "VType_wxSocketClient.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxProtocol
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxProtocol : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxProtocol VTYPE_wxProtocol;

//------------------------------------------------------------------------------
// Value_wxProtocol
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxProtocol : public Value_wxSocketClient {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxProtocol);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxProtocol");
protected:
	wxProtocol* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxProtocol() = delete;
	explicit Value_wxProtocol(wxProtocol* pEntity, VType& vtype = VTYPE_wxProtocol) :
		Value_wxSocketClient(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxProtocol(const Value_wxProtocol& src) = delete;
	Value_wxProtocol& operator=(const Value_wxProtocol& src) = delete;
	// Move constructor/operator
	Value_wxProtocol(Value_wxProtocol&& src) noexcept = delete;
	Value_wxProtocol& operator=(Value_wxProtocol&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxProtocol() = default;
public:
	wxProtocol& GetEntity() { return *_pEntity; }
	const wxProtocol& GetEntity() const { return *_pEntity; }
	wxProtocol* GetEntityPtr() { return _pEntity; }
	const wxProtocol* GetEntityPtr() const { return _pEntity; }
public:
	static wxProtocol& GetEntity(Value& value) {
		return dynamic_cast<Value_wxProtocol&>(value).GetEntity();
	}
	static const wxProtocol& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxProtocol&>(value).GetEntity();
	}
	static wxProtocol* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxProtocol&>(value).GetEntityPtr();
	}
	static const wxProtocol* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxProtocol&>(value).GetEntityPtr();
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
