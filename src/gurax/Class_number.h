//==============================================================================
// Class_number.h
//==============================================================================
#ifndef GURAX_CLASS_NUMBER_H
#define GURAX_CLASS_NUMBER_H
#include "Class.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Class_number
//------------------------------------------------------------------------------
class Class_number : public Class {
protected:
	static const Class_number _instance;
public:
	// Default constructor
	Class_number() {}
	// Copy constructor/operator
	Class_number(const Class_number& src) = delete;
	Class_number& operator=(const Class_number& src) = delete;
	// Move constructor/operator
	Class_number(Class_number&& src) = delete;
	Class_number& operator=(Class_number&& src) noexcept = delete;
protected:
	// Destructor
	~Class_number() = default;
public:
	static const Class& GetInstance() { return _instance; }
};

//------------------------------------------------------------------------------
// Object_number
//------------------------------------------------------------------------------
class Object_number : public Object {
private:
	Double _num;
public:
	// Default constructor
	Object_number(Double num = 0.) : Object(Class_number::GetInstance()), _num(num) {}
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
public:
	Double GetNumber() const { return _num; }
};

}

#endif
