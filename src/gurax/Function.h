//==============================================================================
// Function.h
//==============================================================================
#ifndef GURAX_FUNCTION_H
#define GURAX_FUNCTION_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Function
//------------------------------------------------------------------------------
class Function : public Referable {
public:
	// Constructor
	Function() {}
	// Copy constructor/operator
	Function(const Function& src) = delete;
	Function& operator=(const Function& src) = delete;
	// Move constructor/operator
	Function(Function&& src) = delete;
	Function& operator=(Function&& src) noexcept = delete;
protected:
	// Destructor
	~Function() = default;
public:
	// Referable accessor
	Gurax_DeclareReferable(Function);
};

}

#endif
