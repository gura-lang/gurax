//==============================================================================
// Random.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Random
//------------------------------------------------------------------------------
RefPtr<Random> Random::_pRandomGlobal;

void Random::Bootup(UInt32 seed)
{
	_pRandomGlobal.reset(new Random(seed));
}

void Random::Bootup()
{
	Bootup(std::random_device()());
}

String Random::ToString(const StringStyle& ss) const
{
	return String().Format("Random:seed=0x%08x", GetSeed());
}

}
