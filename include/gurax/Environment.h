//==============================================================================
// Environment.h
//==============================================================================
#ifndef GURAX_ENVIRONMENT_H
#define GURAX_ENVIRONMENT_H
#include "Frame.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Environment
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Environment : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Environment);
public:
	// Constructor
	Environment() {}
	// Copy constructor/operator
	Environment(const Environment& src) = delete;
	Environment& operator=(const Environment& src) = delete;
	// Move constructor/operator
	Environment(Environment&& src) = delete;
	Environment& operator=(Environment&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Environment() = default;
};

}

#endif
