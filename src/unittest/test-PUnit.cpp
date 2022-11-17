//==============================================================================
// test-PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_TesterEntry(PUnit)
{
	MemoryPool::ChunkPUnit chunkPUnit(32 * 5, 64 * 2);
	MemoryPool::Global().SetChunkPUnit(&chunkPUnit);
	RefPtr<Expr> pExpr(new Expr_Empty());
	for (int i = 0; i < 20; i++) {
		RefPtr<PUnitFactory> pPUnitFactory(new PUnitFactory_NoOperation(pExpr.Reference()));
		pPUnitFactory->Create(false);
	}
	const PUnit* pPUnitSentinel = chunkPUnit.PeekPUnitCont();
	const PUnit* pPUnit = chunkPUnit.GetPUnitFirst();
	::printf("%s\n", chunkPUnit.ToString().c_str());
	for ( ; pPUnit != pPUnitSentinel; pPUnit = pPUnit->GetPUnitNext()) {
		::printf("%s %s\n", pPUnit->MakeSeqIdString().c_str(), pPUnit->ToString().c_str());
	}
	MemoryPool::Global().SwitchChunkPUnit(false);
}

}
