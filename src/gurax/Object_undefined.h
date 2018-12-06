//==============================================================================
// Object_undefined.h
//==============================================================================
#ifndef GURAX_OBJECT_UNDEFINED_H
#define GURAX_OBJECT_UNDEFINED_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_undefined
//------------------------------------------------------------------------------
class Object_undefined : public Object {
public:
	class TypeInfoEx : public TypeInfo {
	public:
		// Default constructor
		TypeInfoEx() {}
		// Copy constructor/operator
		TypeInfoEx(const TypeInfoEx& src) = delete;
		TypeInfoEx& operator=(const TypeInfoEx& src) = delete;
		// Move constructor/operator
		TypeInfoEx(TypeInfoEx&& src) = delete;
		TypeInfoEx& operator=(TypeInfoEx&& src) noexcept = delete;
		// Destructor
		~TypeInfoEx() = default;
	};
public:
	static const TypeInfoEx typeInfo;
public:
	// Default constructor
	Object_undefined() : Object(typeInfo) {}
	// Copy constructor/operator
	Object_undefined(const Object_undefined& src) = delete;
	Object_undefined& operator=(const Object_undefined& src) = delete;
	// Move constructor/operator
	Object_undefined(Object_undefined&& src) = delete;
	Object_undefined& operator=(Object_undefined&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Object_undefined() = default;
public:
	Gurax_DeclareReferable(Object_undefined);
public:
	virtual Object *Clone() const { return Reference(); }
};

}

#endif
