//==============================================================================
// Imp_ListBase.h
//==============================================================================
#ifndef GURAX_IMP_LISTBASE_H
#define GURAX_IMP_LISTBASE_H
#include "Iterator.h"
#include "Random.h"

namespace Gurax {

template<typename T> ListBase<T>& ListBase<T>::Shuffle(Random& random)
{
	std::shuffle(_container.begin(), _container.end(), random.GetEngine());
	return *this;
}

}

#endif
