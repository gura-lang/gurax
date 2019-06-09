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

void VTypeCustom::AssignPropHandler(Frame& frame, const Symbol* pSymbol, bool listVarFlag,
									const Attribute& attr, RefPtr<Value> pValueInit)
{
	RefPtr<PropHandler> pPropHandler(new PropHandlerCustom(pSymbol, AddProp()));
	PropHandler::Flags flags = PropHandler::Flag::Readable | PropHandler::Flag::Writable;
	if (listVarFlag) flags |= PropHandler::Flag::ListVar;
	if (pValueInit->IsNil() || attr.IsSet(Gurax_Symbol(nil))) flags |= PropHandler::Flag::Nil;
	const VType *pVType = &VTYPE_Any;
	Value* pValue = frame.Lookup(attr.GetDottedSymbol());
	if (pValue && pValue->IsType(VTYPE_VType)) {
		pVType = &dynamic_cast<Value_VType*>(pValue)->GetVTypeThis();
		if (!pValueInit->IsNil()) {
			//pVType->Cast(*pValue, listVarFlag);
		}
	} else {
		pVType = &VTYPE_Nil;
		if (!pValueInit->IsNil()) {
			pVType = &pValueInit->GetVType();
		}
	}
	_pValuesPropInit->push_back(pValueInit.release());
	pPropHandler->Declare(*pVType, flags);
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
