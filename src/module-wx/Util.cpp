//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// EntityCore
//------------------------------------------------------------------------------
bool EntityCore::PrepareMethod(const Symbol* pSymbolFunc, Function** ppFunc, RefPtr<Argument>& pArgument) const
{
	RefPtr<Value> pValueThis(LockValue());
	if (!pValueThis) return false;
	*ppFunc = &pValueThis->LookupMethod(pSymbolFunc);
	if ((*ppFunc)->IsEmpty()) return false;
	pArgument.reset(new Argument(GetProcessor(), **ppFunc));
	pArgument->SetValueThis(pValueThis.release());
	return true;
}

//------------------------------------------------------------------------------
// EventValueFactory
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// EventUserData
//-----------------------------------------------------------------------------
void EventUserData::Eval(wxEvent& event)
{
	const DeclCallable* pDeclCallable = _pValueFunct->GetDeclCallableWithError();
	if (!pDeclCallable) return;
	RefPtr<Argument> pArg(new Argument(*_pProcessor, pDeclCallable->Reference()));
	ArgFeeder args(*pArg, _pProcessor->GetFrameCur());
	if (!args.FeedValue(_eventValueFactory.CreateValue(event, _pValueUserData.Reference()))) return;
	Value::Delete(_pValueFunct->Eval(*_pProcessor, *pArg));
	if (Error::IsIssued()) Util::ExitMainLoop();
}

//------------------------------------------------------------------------------
// Utility
//------------------------------------------------------------------------------
namespace Util {

void BindMultiEvents(Processor& processor, Argument& argument,
		const wxEventType eventTypes[], size_t n, const EventValueFactory& eventValueFactory)
{
	// Arguments
	ArgPicker args(argument);
	wxEvtHandler* pEvtHandler = args.Pick<Value_wxEvtHandler>().GetEntityPtr();
	int id = args.IsValid()? args.PickNumber<int>() : wxID_ANY;
	Value& valueFunct = args.PickValue();
	// Function body
	for (size_t i = 0; i < n; i++) {
		wxEventType eventType = eventTypes[i];
		pEvtHandler->Bind(eventType, &EventUserData::HandlerFunc, id, -1,
			new EventUserData(processor.Reference(), valueFunct.Reference(), Value::nil(), eventValueFactory));
	}
}

void ExitMainLoop()
{
	wxWindow* window = wxDynamicCast(wxApp::GetInstance(), wxApp)->GetTopWindow();
	if (window) window->Close(true);
	wxApp::GetInstance()->ExitMainLoop();
}

}

Gurax_EndModuleScope(wx)
