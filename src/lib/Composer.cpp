//==============================================================================
// Composer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Composer
//------------------------------------------------------------------------------
Composer::Composer(bool replFlag) : _replFlag(replFlag), _pPUnitFirst(nullptr), _pPUnitLast(nullptr)
{
}

void Composer::Add(PUnit* pPUnit)
{
	if (!_pPUnitFirst) _pPUnitFirst = pPUnit;
	_pPUnitLast = pPUnit;
	if (_replFlag) new PUnit_REPLEnd(); // automatically deleted when a new PUnit is allocated
}

PUnit* Composer::PeekPUnitCont() const
{
	MemoryPool::Global().SwitchChunkPUnit(_replFlag);
	return reinterpret_cast<PUnit*>(MemoryPool::Global().GetChunkPUnit().PeekPointer());
}

void Composer::SetFactory(PUnitFactory* pPUnitFactory)
{
	MemoryPool::Global().SwitchChunkPUnit(_replFlag);
	if (_pPUnitFactory) {
		Add(_pPUnitFactory->Create(false));
	}
	MemoryPool::Global().GetChunkPUnit().Reserve(pPUnitFactory->GetPUnitSize());
	_pPUnitFactory.reset(pPUnitFactory);
}

void Composer::_Flush(bool discardValueFlag)
{
	MemoryPool::Global().SwitchChunkPUnit(_replFlag);
	if (_pPUnitFactory) {
		Add(_pPUnitFactory->Create(discardValueFlag));
		_pPUnitFactory.reset(nullptr);
	}
}

void Composer::ComposeAsSequence(Expr& expr)
{
	expr.SetPUnitFirst(PeekPUnitCont());
	PUnit* pPUnitOfSequenceBegin = PeekPUnitCont();
	Add_SequenceBegin(expr);													// [Any]
	BeginRepeaterBlock(nullptr, nullptr, nullptr);
	expr.ComposeOrNil(*this);													// [Any]
	EndRepeaterBlock();
	pPUnitOfSequenceBegin->SetPUnitSentinel(PeekPUnitCont());
	expr.SetPUnitEnd(PeekPUnitCont());
}

void Composer::Print() const
{
}

void Composer::PrintPUnit(const StringStyle& ss) const
{
	for (const PUnit* pPUnit = GetPUnitFirst(); pPUnit; pPUnit = pPUnit->GetPUnitNext()) {
		if (!pPUnit->IsBridge()) pPUnit->Print(ss);
	}
}

Iterator* Composer::EachPUnit() const
{
	return new Iterator_PUnit(GetPUnitFirst(), nullptr);
}

void Composer::Add_AssignPropSlot(const Symbol* pSymbol, RefPtr<DottedSymbol> pDottedSymbol, PropSlot::Flags flags,
									 const Attribute& attr, bool initializerFlag, const Expr& exprSrc)
{
	auto& symbolAssoc = PropSlot::SymbolAssoc_Flag::GetInstance();
	if (!pDottedSymbol) pDottedSymbol.reset(DottedSymbol::Empty.Reference());
	flags |= PropSlot::Flag::Readable | PropSlot::Flag::Writable;
	const SymbolList& symbols = attr.GetSymbols();
	for (auto ppSymbol = symbols.begin(); ppSymbol != symbols.end(); ppSymbol++) {
		const Symbol* pSymbol = *ppSymbol;
		PropSlot::Flags flagsUpdate = symbolAssoc.ToAssociated(pSymbol);
		if (flagsUpdate == PropSlot::Flag::None) {
			if (pSymbol->IsIdentical(Gurax_Symbol(const_))) {
				flags &= ~PropSlot::Flag::Writable;
			} else if (ppSymbol != symbols.begin()) {
				Error::IssueWith(ErrorType::SyntaxError, exprSrc, "unknown attribute: %s", pSymbol->GetName());
				return;
			}
		} else {
			flags |= flagsUpdate;
		}
	}
	SetFactory(new PUnitFactory_AssignPropSlot(
				   pSymbol, pDottedSymbol.release(), flags, initializerFlag, exprSrc.Reference()));
}

//------------------------------------------------------------------------------
// Composer::RepeaterInfoOwner
//------------------------------------------------------------------------------
void Composer::RepeaterInfoOwner::Clear()
{
	for (RepeaterInfo* pRepeaterInfo : *this) delete pRepeaterInfo;
	clear();
}

//------------------------------------------------------------------------------
// Composer::TryInfoOwner
//------------------------------------------------------------------------------
void Composer::TryInfoOwner::Clear()
{
	for (TryInfo* pTryInfo : *this) delete pTryInfo;
	clear();
}

}
