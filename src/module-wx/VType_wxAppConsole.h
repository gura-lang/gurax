//==============================================================================
// VType_wxAppConsole.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXAPPCONSOLE_H
#define GURAX_MODULE_WX_VTYPE_WXAPPCONSOLE_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvtHandler.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxAppConsole
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxAppConsole : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxAppConsole VTYPE_wxAppConsole;

//------------------------------------------------------------------------------
// Value_wxAppConsole
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxAppConsole : public Value_wxEvtHandler {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAppConsole);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAppConsole");
public:
	class EntityT : public wxAppConsole {
	public:
		using wxAppConsole::wxAppConsole;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxAppConsole() = delete;
	explicit Value_wxAppConsole(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxAppConsole) :
		Value_wxEvtHandler(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxAppConsole(const Value_wxAppConsole& src) = delete;
	Value_wxAppConsole& operator=(const Value_wxAppConsole& src) = delete;
	// Move constructor/operator
	Value_wxAppConsole(Value_wxAppConsole&& src) noexcept = delete;
	Value_wxAppConsole& operator=(Value_wxAppConsole&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxAppConsole() = default;
public:
	wxAppConsole& GetEntity() {
		return reinterpret_cast<wxAppConsole&>(Value_wxEvtHandler::GetEntity());
	}
	const wxAppConsole& GetEntity() const {
		return reinterpret_cast<const wxAppConsole&>(Value_wxEvtHandler::GetEntity());
	}
	wxAppConsole* GetEntityPtr() {
		return reinterpret_cast<wxAppConsole*>(Value_wxEvtHandler::GetEntityPtr());
	}
	const wxAppConsole* GetEntityPtr() const {
		return reinterpret_cast<const wxAppConsole*>(Value_wxEvtHandler::GetEntityPtr());
	}
public:
	static wxAppConsole& GetEntity(Value& value) {
		return dynamic_cast<Value_wxAppConsole&>(value).GetEntity();
	}
	static const wxAppConsole& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAppConsole&>(value).GetEntity();
	}
	static wxAppConsole* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxAppConsole&>(value).GetEntityPtr();
	}
	static const wxAppConsole* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxAppConsole&>(value).GetEntityPtr();
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
