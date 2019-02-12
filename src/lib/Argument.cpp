//==============================================================================
// Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
Argument::Argument(DeclCaller* pDeclCaller, Attribute* pAttr) :
	_pDeclCaller(pDeclCaller), _pAttr(pAttr), _pArgSlotCur(nullptr)
{
	ArgSlot* pArgSlotLast = nullptr;
	const DeclArgOwner &declArgOwner = _pDeclCaller->GetDeclArgOwner();
	for (const DeclArg* pDeclArg : declArgOwner) {
		ArgSlot* pArgSlot = nullptr;
		if (pDeclArg->IsOccurZeroOrMore() || pDeclArg->IsOccurOnceOrMore()) {
			pArgSlot = new ArgSlot_List(pDeclArg->Reference());
		} else {
			pArgSlot = new ArgSlot_Value(pDeclArg->Reference());
		}
		if (pArgSlotLast) {
			pArgSlotLast->SetNext(pArgSlot);
		} else {
			_pArgSlotTop.reset(pArgSlot);
		}
		pArgSlotLast = pArgSlot;
	}
	_pArgSlotCur = _pArgSlotTop.get();
}

String Argument::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

}
