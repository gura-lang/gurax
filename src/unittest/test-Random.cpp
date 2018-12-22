//==============================================================================
// test-Random.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Gurax_TesterEntry(Random)
{
	RefPtr<Random> pRandom(new Random(0));
	pRandom->Reset();
	for (int i = 0; i < 10; ++i) ::printf("%3d", pRandom->Range<>(100));
	::printf("\n");
	pRandom->Reset();
	for (int i = 0; i < 10; ++i) ::printf("%3d", pRandom->Range<>(100));
	::printf("\n");
	pRandom->Reset();
	for (int i = 0; i < 10; ++i) ::printf("%8.4f", pRandom->Uniform<>());
	::printf("\n");
	pRandom->Reset();
	for (int i = 0; i < 10; ++i) ::printf("%8.4f", pRandom->Uniform<>());
	::printf("\n");
	pRandom->Reset();
	for (int i = 0; i < 10; ++i) ::printf("%8.4f", pRandom->Normal<>());
	::printf("\n");
	pRandom->Reset();
	for (int i = 0; i < 10; ++i) ::printf("%8.4f", pRandom->Normal<>());
	::printf("\n");
}

}
