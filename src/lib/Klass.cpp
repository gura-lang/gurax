//==============================================================================
// Klass.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass
//------------------------------------------------------------------------------
Klass::SeqId Klass::_seqIdNext = 1;
Klass Klass::Empty("");

Klass::Klass(const char* name) :
	_seqId(_seqIdNext++), _pHelpProvider(new HelpProvider()), _pKlassInherited(nullptr),
	_pSymbol(Symbol::Add(name)), _flags(0),
	_pFrame(Frame::CreateBranch(nullptr, Frame::CreateSource()))
{
}

void Klass::SetAttrs(Klass& klassInherited, UInt32 flags)
{
	_pKlassInherited = &klassInherited;
	_pFrame->SetLeft(_pKlassInherited->GetFrame().Reference());
	_flags = flags;
}

String Klass::MakeFullName() const
{
	return GetName();
}

DottedSymbol* Klass::MakeDottedSymbol() const
{
	RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol());
	pDottedSymbol->Append(GetSymbol());
	return pDottedSymbol.release();
}

//------------------------------------------------------------------------------
// KlassMap
//------------------------------------------------------------------------------
void KlassMap::Assign(const Symbol* pSymbol, Klass* pKlass)
{
	iterator pPair = find(pSymbol);
	if (pPair == end()) {
		emplace(pSymbol, pKlass);
	} else {
		pPair->second = pKlass;
	}
}

String KlassMap::ToString(const StringStyle& ss) const
{
	String str;
	SymbolList keys = GetKeys().Sort();
	for (const Symbol* pSymbol : keys) {
		const Klass* pKlass = Lookup(pSymbol);
		str += pSymbol->GetName();
		str += " = ";
		str += pKlass->MakeFullName();
		str += "\n";
	}
	return str;
}

}
