//==============================================================================
// Class.h
//==============================================================================
#ifndef GURAX_CLASS_H
#define GURAX_CLASS_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Class
//------------------------------------------------------------------------------
class Class {
public:
	// Default constructor
	Class() {}
	// Copy constructor/operator
	Class(const Class& src) = delete;
	Class& operator=(const Class& src) = delete;
	// Move constructor/operator
	Class(Class&& src) = delete;
	Class& operator=(Class&& src) noexcept = delete;
protected:
	// Destructor
	~Class() = default;
};

//------------------------------------------------------------------------------
// Object
//------------------------------------------------------------------------------
class Object : public Referable {
protected:
	const Class& _class;
public:
	// Default constructor
	Object() = delete;
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
public:
	Object(const Class& class_) : _class(class_) {}
};

}

#endif
