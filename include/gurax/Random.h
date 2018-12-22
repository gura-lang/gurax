//==============================================================================
// Random.h
//==============================================================================
#ifndef GURAX_RANDOM_H
#define GURAX_RANDOM_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Random
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Random : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Random);
public:
	// Constructor
	Random() {}
	// Copy constructor/operator
	Random(const Random& src) = delete;
	Random& operator=(const Random& src) = delete;
	// Move constructor/operator
	Random(Random&& src) = delete;
	Random& operator=(Random&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Random() = default;
};

}
