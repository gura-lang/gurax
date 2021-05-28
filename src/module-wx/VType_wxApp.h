//==============================================================================
// VType_wxApp.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXAPP_H
#define GURAX_MODULE_WX_VTYPE_WXAPP_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxAppConsole.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxApp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxApp : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxApp VTYPE_wxApp;

//------------------------------------------------------------------------------
// Value_wxApp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxApp : public Value_wxAppConsole {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxApp);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxApp");
public:
	class EntityT : public wxApp {
	public:
		using wxApp::wxApp;
	public:
		EntityCore core;
	public:
		virtual bool OnInit() override;
		virtual bool SafeYield(wxWindow* win, bool onlyIfNeeded) override;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxApp() = delete;
	explicit Value_wxApp(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxApp) :
		Value_wxAppConsole(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxApp(const Value_wxApp& src) = delete;
	Value_wxApp& operator=(const Value_wxApp& src) = delete;
	// Move constructor/operator
	Value_wxApp(Value_wxApp&& src) noexcept = delete;
	Value_wxApp& operator=(Value_wxApp&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxApp() = default;
public:
	wxApp* GetEntity() {
		return reinterpret_cast<wxApp*>(Value_wxEvtHandler::GetEntity());
	}
	const wxApp* GetEntity() const {
		return reinterpret_cast<const wxApp*>(Value_wxEvtHandler::GetEntity());
	}
public:
	static wxApp* GetEntity(Value& value) {
		return dynamic_cast<Value_wxApp&>(value).GetEntity();
	}
	static const wxApp* GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxApp&>(value).GetEntity();
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
