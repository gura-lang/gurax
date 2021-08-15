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
// ClientData
//-----------------------------------------------------------------------------
std::vector<wxClientData*> ClientData::Create(const ValueList& values)
{
	std::vector<wxClientData*> rtn;
	rtn.reserve(values.size());
	for (const Value* pValue : values) rtn.push_back(new ClientData(pValue->Reference()));
	return rtn;
}

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

EventTypeMap eventTypeMap;

wxArrayString CreateArrayString(const ValueList& values)
{
	wxArrayString rtn;
	rtn.reserve(values.size());
	for (const Value* pValue : values) rtn.push_back(Value_String::GetString(*pValue));
	return rtn;
}

wxArrayShort CreateArrayShort(const ValueList& values)
{
	wxArrayShort rtn;
	rtn.reserve(values.size());
	for (const Value* pValue : values) rtn.push_back(Value_Number::GetNumber<Short>(*pValue));
	return rtn;
}

wxArrayInt CreateArrayInt(const ValueList& values)
{
	wxArrayInt rtn;
	rtn.reserve(values.size());
	for (const Value* pValue : values) rtn.push_back(Value_Number::GetNumber<Int>(*pValue));
	return rtn;
}

wxArrayDouble CreateArrayDouble(const ValueList& values)
{
	wxArrayDouble rtn;
	rtn.reserve(values.size());
	for (const Value* pValue : values) rtn.push_back(Value_Number::GetNumber<Double>(*pValue));
	return rtn;
}

wxArrayLong CreateArrayLong(const ValueList& values)
{
	wxArrayLong rtn;
	rtn.reserve(values.size());
	for (const Value* pValue : values) rtn.push_back(Value_Number::GetNumber<Long>(*pValue));
	return rtn;
}

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

const Value& LookupEventType(wxEventType eventType)
{
	auto iter = eventTypeMap.find(eventType);
	if (iter == eventTypeMap.end()) return Value::C_nil();
	return *iter->second;
}

void ExitMainLoop()
{
	wxWindow* window = wxDynamicCast(wxApp::GetInstance(), wxApp)->GetTopWindow();
	if (window) window->Close(true);
	wxApp::GetInstance()->ExitMainLoop();
}

}

Gurax_EndModuleScope(wx)
