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
	_pFrame(Frame::CreateBranch(nullptr, Frame::CreateSource()))
{
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

Value* VType::DoCastFrom(Value* pValue) const
{
	if (pValue->IsInstanceOf(*this)) return pValue;
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
