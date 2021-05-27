//==============================================================================
// VType_Window.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WINDOW_H
#define GURAX_MODULE_WX_VTYPE_WINDOW_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvtHandler.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_Window
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Window : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Window VTYPE_Window;

//------------------------------------------------------------------------------
// Value_Window
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Window : public Value_wxEvtHandler {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Window);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Window");
public:
	class EntityT : public wxWindow {
	public:
		using EntitySuper = wxWindow;
		using wxWindow::wxWindow;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_Window() = delete;
	explicit Value_Window(wxWindow* pEntity, VType& vtype = VTYPE_Window) :
		Value_wxEvtHandler(pEntity, vtype) {}
	// Copy constructor/operator
	Value_Window(const Value_Window& src) = delete;
	Value_Window& operator=(const Value_Window& src) = delete;
	// Move constructor/operator
	Value_Window(Value_Window&& src) noexcept = delete;
	Value_Window& operator=(Value_Window&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Window() = default;
public:
	wxWindow* GetEntity() { return wxDynamicCast(Value_wxEvtHandler::GetEntity(), wxWindow); }
	const wxWindow* GetEntity() const { return wxDynamicCast(Value_wxEvtHandler::GetEntity(), wxWindow); }
public:
	static wxWindow* GetEntity(Value& value) {
		return dynamic_cast<Value_Window&>(value).GetEntity();
	}
	static const wxWindow* GetEntity(const Value& value) {
		return dynamic_cast<const Value_Window&>(value).GetEntity();
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
