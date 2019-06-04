//==============================================================================
// Composer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Composer
//------------------------------------------------------------------------------
Composer::Composer(bool replFlag) :
	_replFlag(replFlag), _pPUnitFirst(nullptr), _pPUnitLast(nullptr)
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
	PUnit* pPUnitOfBeginSequence = PeekPUnitCont();
	Add_BeginSequence(&expr);								// [Any]
	BeginRepeaterBlock(nullptr, nullptr, nullptr);
	expr.ComposeOrNil(*this);								// [Any]
	EndRepeaterBlock();
	pPUnitOfBeginSequence->SetPUnitSentinel(PeekPUnitCont());
	Add_Return(&expr);
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

//------------------------------------------------------------------------------
// Composer::RepeaterInfoOwner
//------------------------------------------------------------------------------
void Composer::RepeaterInfoOwner::Clear()
{
	for (RepeaterInfo* pRepeaterInfo : *this) delete pRepeaterInfo;
	clear();
}

}
