//==============================================================================
// VType_AppConsole.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_APPCONSOLE_H
#define GURAX_MODULE_WX_VTYPE_APPCONSOLE_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_EvtHandler.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_AppConsole
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_AppConsole : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_AppConsole VTYPE_AppConsole;

//------------------------------------------------------------------------------
// Value_AppConsole
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_AppConsole : public Value_EvtHandler {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_AppConsole);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_AppConsole");
public:
	class EntityT : public wxAppConsole {
	public:
		using EntitySuper = wxAppConsole;
		using wxAppConsole::wxAppConsole;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_AppConsole() = delete;
	explicit Value_AppConsole(wxAppConsole* pEntity, VType& vtype = VTYPE_AppConsole) :
		Value_EvtHandler(pEntity, vtype) {}
	// Copy constructor/operator
	Value_AppConsole(const Value_AppConsole& src) = delete;
	Value_AppConsole& operator=(const Value_AppConsole& src) = delete;
	// Move constructor/operator
	Value_AppConsole(Value_AppConsole&& src) noexcept = delete;
	Value_AppConsole& operator=(Value_AppConsole&& src) noexcept = delete;
protected:
	// Destructor
	~Value_AppConsole() = default;
public:
	wxAppConsole* GetEntity() { return wxDynamicCast(Value_EvtHandler::GetEntity(), wxAppConsole); }
	const wxAppConsole* GetEntity() const { return wxDynamicCast(Value_EvtHandler::GetEntity(), wxAppConsole); }
public:
	static wxAppConsole* GetEntity(Value& value) {
		return dynamic_cast<Value_AppConsole&>(value).GetEntity();
	}
	static const wxAppConsole* GetEntity(const Value& value) {
		return dynamic_cast<const Value_AppConsole&>(value).GetEntity();
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
