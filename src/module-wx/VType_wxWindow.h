//==============================================================================
// VType_wxWindow.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXWINDOW_H
#define GURAX_MODULE_WX_VTYPE_WXWINDOW_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvtHandler.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxWindow : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxWindow VTYPE_wxWindow;

//------------------------------------------------------------------------------
// Value_wxWindow
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxWindow : public Value_wxEvtHandler {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxWindow);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxWindow");
public:
	class EntityT : public wxWindow {
	public:
		using wxWindow::wxWindow;
	public:
		EntityCore core_gurax;
		virtual bool AcceptsFocus() const override {
			static const Symbol* pSymbolFunc = nullptr;
			if (!pSymbolFunc) pSymbolFunc = Symbol::Add("AcceptsFocus");
			do {
				Gurax::Function* pFunc_gurax;
				RefPtr<Gurax::Argument> pArgument_gurax;
				if (!core_gurax.PrepareMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
				// Argument
				// (none)
				// Evaluation
				RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
				if (Error::IsIssued()) {
					Util::ExitMainLoop();
					break;
				}
				// Return Value
				if (!pValueRtn->IsType(VTYPE_Bool)) break;
				return Value_Bool::GetBool(*pValueRtn);
			} while (0);
			return wxWindow::AcceptsFocus();
		}
		virtual bool AcceptsFocusFromKeyboard() const override {
			static const Symbol* pSymbolFunc = nullptr;
			if (!pSymbolFunc) pSymbolFunc = Symbol::Add("AcceptsFocusFromKeyboard");
			do {
				Gurax::Function* pFunc_gurax;
				RefPtr<Gurax::Argument> pArgument_gurax;
				if (!core_gurax.PrepareMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
				// Argument
				// (none)
				// Evaluation
				RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
				if (Error::IsIssued()) {
					Util::ExitMainLoop();
					break;
				}
				// Return Value
				if (!pValueRtn->IsType(VTYPE_Bool)) break;
				return Value_Bool::GetBool(*pValueRtn);
			} while (0);
			return wxWindow::AcceptsFocusFromKeyboard();
		}
		virtual bool AcceptsFocusRecursively() const override {
			static const Symbol* pSymbolFunc = nullptr;
			if (!pSymbolFunc) pSymbolFunc = Symbol::Add("AcceptsFocusRecursively");
			do {
				Gurax::Function* pFunc_gurax;
				RefPtr<Gurax::Argument> pArgument_gurax;
				if (!core_gurax.PrepareMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
				// Argument
				// (none)
				// Evaluation
				RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
				if (Error::IsIssued()) {
					Util::ExitMainLoop();
					break;
				}
				// Return Value
				if (!pValueRtn->IsType(VTYPE_Bool)) break;
				return Value_Bool::GetBool(*pValueRtn);
			} while (0);
			return wxWindow::AcceptsFocusRecursively();
		}
		virtual bool HasFocus() const override {
			static const Symbol* pSymbolFunc = nullptr;
			if (!pSymbolFunc) pSymbolFunc = Symbol::Add("HasFocus");
			do {
				Gurax::Function* pFunc_gurax;
				RefPtr<Gurax::Argument> pArgument_gurax;
				if (!core_gurax.PrepareMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
				// Argument
				// (none)
				// Evaluation
				RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
				if (Error::IsIssued()) {
					Util::ExitMainLoop();
					break;
				}
				// Return Value
				if (!pValueRtn->IsType(VTYPE_Bool)) break;
				return Value_Bool::GetBool(*pValueRtn);
			} while (0);
			return wxWindow::HasFocus();
		}
		virtual void SetCanFocus(bool canFocus) override {
			static const Symbol* pSymbolFunc = nullptr;
			if (!pSymbolFunc) pSymbolFunc = Symbol::Add("SetCanFocus");
			do {
				Gurax::Function* pFunc_gurax;
				RefPtr<Gurax::Argument> pArgument_gurax;
				if (!core_gurax.PrepareMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
				// Argument
				Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
				if (!args_gurax.FeedValue(new Gurax::Value_Bool(canFocus))) break;
				// Evaluation
				RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
				if (Error::IsIssued()) {
					Util::ExitMainLoop();
					break;
				}
				return;
			} while (0);
		}
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxWindow() = delete;
	explicit Value_wxWindow(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxWindow) :
		Value_wxEvtHandler(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxWindow(const Value_wxWindow& src) = delete;
	Value_wxWindow& operator=(const Value_wxWindow& src) = delete;
	// Move constructor/operator
	Value_wxWindow(Value_wxWindow&& src) noexcept = delete;
	Value_wxWindow& operator=(Value_wxWindow&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxWindow() = default;
public:
	wxWindow& GetEntity() {
		return reinterpret_cast<wxWindow&>(Value_wxEvtHandler::GetEntity());
	}
	const wxWindow& GetEntity() const {
		return reinterpret_cast<const wxWindow&>(Value_wxEvtHandler::GetEntity());
	}
	wxWindow* GetEntityPtr() {
		return reinterpret_cast<wxWindow*>(Value_wxEvtHandler::GetEntityPtr());
	}
	const wxWindow* GetEntityPtr() const {
		return reinterpret_cast<const wxWindow*>(Value_wxEvtHandler::GetEntityPtr());
	}
public:
	static wxWindow& GetEntity(Value& value) {
		return dynamic_cast<Value_wxWindow&>(value).GetEntity();
	}
	static const wxWindow& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxWindow&>(value).GetEntity();
	}
	static wxWindow* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxWindow&>(value).GetEntityPtr();
	}
	static const wxWindow* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxWindow&>(value).GetEntityPtr();
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
