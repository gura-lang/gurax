//==============================================================================
// VType_wxEvtHandler.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXEVTHANDLER_H
#define GURAX_MODULE_WX_VTYPE_WXEVTHANDLER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxEvtHandler
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxEvtHandler : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxEvtHandler VTYPE_wxEvtHandler;

//------------------------------------------------------------------------------
// Value_wxEvtHandler
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxEvtHandler : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxEvtHandler);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxEvtHandler");
protected:
	wxWeakRef<wxEvtHandler> _pEntity;
public:
	class EntityT : public wxEvtHandler {
	public:
		using wxEvtHandler::wxEvtHandler;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxEvtHandler() = delete;
	explicit Value_wxEvtHandler(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxEvtHandler) :
		Value_Object(vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxEvtHandler(const Value_wxEvtHandler& src) = delete;
	Value_wxEvtHandler& operator=(const Value_wxEvtHandler& src) = delete;
	// Move constructor/operator
	Value_wxEvtHandler(Value_wxEvtHandler&& src) noexcept = delete;
	Value_wxEvtHandler& operator=(Value_wxEvtHandler&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxEvtHandler() = default;
public:
	wxEvtHandler& GetEntity() { return *_pEntity; }
	const wxEvtHandler& GetEntity() const { return *_pEntity; }
	wxEvtHandler* GetEntityPtr() { return _pEntity.get(); }
	const wxEvtHandler* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxEvtHandler& GetEntity(Value& value) {
		return dynamic_cast<Value_wxEvtHandler&>(value).GetEntity();
	}
	static const wxEvtHandler& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxEvtHandler&>(value).GetEntity();
	}
	static wxEvtHandler* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxEvtHandler&>(value).GetEntityPtr();
	}
	static const wxEvtHandler* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxEvtHandler&>(value).GetEntityPtr();
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