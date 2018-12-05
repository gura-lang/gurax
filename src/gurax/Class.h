//==============================================================================
// Class.h
//==============================================================================
#ifndef GURAX_CLASS_H
#define GURAX_CLASS_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object
//------------------------------------------------------------------------------
class Object : public Referable {
public:
	// Default constructor
	Object() {}
	// Copy constructor/operator
	Object(const Object& src) = delete;
	Object& operator=(const Object& src) = delete;
	// Move constructor/operator
	Object(Object&& src) = delete;
	Object& operator=(Object&& src) noexcept = delete;
protected:
	// Destructor
	~Object() = default;
public:
	Gurax_DeclareReferable(Object);
};

}

#endif
