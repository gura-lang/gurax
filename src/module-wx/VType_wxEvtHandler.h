//==============================================================================
// VType_wxEvtHandler.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXEVTHANDLER_H
#define GURAX_MODULE_WX_VTYPE_WXEVTHANDLER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxTrackable.h"

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
class GURAX_DLLDECLARE Value_wxEvtHandler : public Value_wxTrackable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxEvtHandler);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxEvtHandler");
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
	explicit Value_wxEvtHandler(wxTrackable* pEntity, VType& vtype = VTYPE_wxEvtHandler) :
		Value_wxTrackable(pEntity, vtype) {}
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
	wxEvtHandler* GetEntity() {
		return reinterpret_cast<wxEvtHandler*>(Value_wxTrackable::GetEntity());
	}
	const wxEvtHandler* GetEntity() const {
		return reinterpret_cast<const wxEvtHandler*>(Value_wxTrackable::GetEntity());
	}
public:
	static wxEvtHandler* GetEntity(Value& value) {
		return dynamic_cast<Value_wxEvtHandler&>(value).GetEntity();
	}
	static const wxEvtHandler* GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxEvtHandler&>(value).GetEntity();
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
