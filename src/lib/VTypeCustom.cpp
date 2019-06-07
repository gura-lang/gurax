//==============================================================================
// VTypeCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VTypeCustom
//------------------------------------------------------------------------------
void VTypeCustom::AssignFunction(Function* pFunction)
{
	const Symbol* pSymbol = pFunction->GetSymbol();
	if (pSymbol->IsIdentical(Gurax_Symbol(__init__))) {
		pFunction->DeclareBlock(Gurax_Symbol(block), DeclBlock::Occur::ZeroOrOnce);
		SetConstructor(new Constructor(*this, pFunction));
	} else {
		GetFrame().Assign(pSymbol, new Value_Function(pFunction));
	}
}

void VTypeCustom::AssignProperty(const Symbol* pSymbol, const Attribute& attr, Value* pValueInit)
{
	RefPtr<PropHandler> pPropHandler(new PropHandlerCustom(pSymbol, AddProp()));
	pPropHandler->Declare(VTYPE_Any, PropHandler::Flag::Readable | PropHandler::Flag::Writable);
	Assign(pPropHandler.release());
}

Value* VTypeCustom::DoCastFrom(const Value& value) const
{
	return value.Reference();
}

//------------------------------------------------------------------------------
// ValueCustom
//------------------------------------------------------------------------------
void ValueCustom::SetCustomProp(size_t iProp, Value* pValue)
{
	ValueOwner::iterator ppValue = _pValuesProp->begin() + iProp;
	Value::Delete(*ppValue);
	*ppValue = pValue;
}

String ValueCustom::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ">";
	return str;
}

String ValueCustom::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

}
