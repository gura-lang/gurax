//==============================================================================
// VType.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType
//------------------------------------------------------------------------------
VType::SeqId VType::_seqIdNext = 1;
VType VType::Empty("");

VType::VType(const char* name) :
	_seqId(_seqIdNext++), _pHelpProvider(new HelpProvider()), _pVTypeInherited(nullptr),
	_pSymbol(Symbol::Add(name)), _flags(0),
	_pFrame(Frame::CreateOfBranch(nullptr, Frame::CreateOfValueMap()))
{
}

void VType::PrepareBasic(Frame& frame)
{
	VTYPE_Object.Prepare(frame);
	VTYPE_Any.Prepare(frame);
	VTYPE_ArgSlot.Prepare(frame);
	VTYPE_Argument.Prepare(frame);
	VTYPE_Attribute.Prepare(frame);
	VTYPE_Binary.Prepare(frame);
	VTYPE_Bool.Prepare(frame);
	VTYPE_DateTime.Prepare(frame);
	VTYPE_Dict.Prepare(frame);
	VTYPE_Expr.Prepare(frame);
	VTYPE_Function.Prepare(frame);
	VTYPE_Iterator.Prepare(frame);
	VTYPE_VType.Prepare(frame);
	VTYPE_List.Prepare(frame);
	VTYPE_Member.Prepare(frame);
	VTYPE_Module.Prepare(frame);
	VTYPE_Nil.Prepare(frame);
	VTYPE_Number.Prepare(frame);
	VTYPE_Stream.Prepare(frame);
	VTYPE_String.Prepare(frame);
	VTYPE_StringPtr.Prepare(frame);
	VTYPE_Symbol.Prepare(frame);
	VTYPE_Template.Prepare(frame);
	VTYPE_TimeDelta.Prepare(frame);
	VTYPE_Undefined.Prepare(frame);
}

void VType::SetAttrs(VType& vtypeInherited, UInt32 flags)
{
	_pVTypeInherited = &vtypeInherited;
	_pFrame->SetLeft(_pVTypeInherited->GetFrame().Reference());
	_flags = flags;
}

String VType::MakeFullName() const
{
	return GetName();
}

DottedSymbol* VType::MakeDottedSymbol() const
{
	RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol());
	pDottedSymbol->Append(GetSymbol());
	return pDottedSymbol.release();
}

const PropHandler* VType::LookupPropHandler(const Symbol* pSymbol) const
{
	const PropHandler* pPropHandler = GetPropHandlerMap().Lookup(pSymbol);
	if (!pPropHandler) pPropHandler = GetVTypeInherited().LookupPropHandler(pSymbol);
	return pPropHandler;
}

Value* VType::Cast(const Value& value) const
{
	return DoCastFrom(value);
}

Value* VType::DoCastFrom(const Value& value) const
{
	if (value.IsInstanceOf(*this)) return value.Reference();
	Error::Issue(ErrorType::ValueError, "failed to cast");
	return nullptr;
}

//------------------------------------------------------------------------------
// VTypeMap
//------------------------------------------------------------------------------
void VTypeMap::Assign(const Symbol* pSymbol, VType* pVType)
{
	iterator pPair = find(pSymbol);
	if (pPair == end()) {
		emplace(pSymbol, pVType);
	} else {
		pPair->second = pVType;
	}
}

String VTypeMap::ToString(const StringStyle& ss) const
{
	String str;
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		const VType* pVType = Lookup(pSymbol);
		str += pSymbol->GetName();
		str += " = ";
		str += pVType->MakeFullName();
		str += "\n";
	}
	return str;
}

}
