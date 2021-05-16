//==============================================================================
// VType_EvtHandler.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_EVTHANDLER_H
#define GURAX_MODULE_WX_VTYPE_EVTHANDLER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_EvtHandler
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_EvtHandler : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_EvtHandler VTYPE_EvtHandler;

//------------------------------------------------------------------------------
// Value_EvtHandler
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_EvtHandler : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_EvtHandler);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_EvtHandler");
public:
	class EntityT : public wxEvtHandler {
	public:
		using EntitySuper = wxEvtHandler;
		using wxEvtHandler::wxEvtHandler;
	public:
		EntityCore core;
	};
protected:
	wxWeakRef<wxEvtHandler> _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_EvtHandler() = delete;
	explicit Value_EvtHandler(wxEvtHandler* pEntity, VType& vtype = VTYPE_EvtHandler) :
		Value_Object(vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_EvtHandler(const Value_EvtHandler& src) = delete;
	Value_EvtHandler& operator=(const Value_EvtHandler& src) = delete;
	// Move constructor/operator
	Value_EvtHandler(Value_EvtHandler&& src) noexcept = delete;
	Value_EvtHandler& operator=(Value_EvtHandler&& src) noexcept = delete;
protected:
	// Destructor
	~Value_EvtHandler() = default;
public:
	wxEvtHandler* GetEntity() { return _pEntity.get(); }
	const wxEvtHandler* GetEntity() const { return _pEntity.get(); }
public:
	static wxEvtHandler* GetEntity(Value& value) {
		return dynamic_cast<Value_EvtHandler&>(value).GetEntity();
	}
	static const wxEvtHandler* GetEntity(const Value& value) {
		return dynamic_cast<const Value_EvtHandler&>(value).GetEntity();
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
