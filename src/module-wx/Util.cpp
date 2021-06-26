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
// Utility
//------------------------------------------------------------------------------
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

Gurax_EndModuleScope(wx)
