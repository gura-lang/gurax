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
	String str;
	str.Format("Random:seed=%08x", GetSeed());
	return str;
}

}
