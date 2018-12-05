//==============================================================================
// Class_number.h
//==============================================================================
#ifndef GURAX_CLASS_NUMBER_H
#define GURAX_CLASS_NUMBER_H
#include "Class.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_number
//------------------------------------------------------------------------------
class Object_number : public Referable {
private:
	Double _num;
public:
	// Default constructor
	Object_number(Double num = 0.) : _num(num) {}
	// Copy constructor/operator
	Object_number(const Object_number& src) = delete;
	Object_number& operator=(const Object_number& src) = delete;
	// Move constructor/operator
	Object_number(Object_number&& src) = delete;
	Object_number& operator=(Object_number&& src) noexcept = delete;
protected:
	// Destructor
	~Object_number() = default;
public:
	Gurax_DeclareReferable(Object_number);
};

}

#endif
