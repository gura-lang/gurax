//==============================================================================
// VType_wxAppConsole_HandCode.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

bool Value_wxAppConsole::EntityT::OnInit()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnInit");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) return false;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			//Util::ExitMainLoop();
			//break;
			return false;
		}
		// Return Value
		if (!pValueRtn->IsInstanceOf(VTYPE_Bool)) {
			Error::IssueWith(ErrorType::TypeError, pFunc_gurax->GetDeclCallable().GetExprSrc(),
				"the function OnInit is expected to return a value of %s or its derived class",
				VTYPE_Bool.MakeFullName().c_str());
			//Util::ExitMainLoop();
			//break;
			return false;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_OnInit();
}

Gurax_EndModuleScope(wx)
