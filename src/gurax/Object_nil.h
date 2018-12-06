//==============================================================================
// Object_nil.h
//==============================================================================
#ifndef GURAX_OBJECT_NIL_H
#define GURAX_OBJECT_NIL_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_nil
//------------------------------------------------------------------------------
class Object_nil : public Object {
public:
	class TypeInfoEx : public TypeInfo {
	public:
		// Default constructor
		TypeInfoEx() : TypeInfo(&Object::typeInfo) {}
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
	Object_nil() : Object(typeInfo) {}
	// Copy constructor/operator
	Object_nil(const Object_nil& src) = delete;
	Object_nil& operator=(const Object_nil& src) = delete;
	// Move constructor/operator
	Object_nil(Object_nil&& src) = delete;
	Object_nil& operator=(Object_nil&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Object_nil() = default;
public:
	Gurax_DeclareReferable(Object_nil);
public:
	virtual Object *Clone() const { return Reference(); }
};

}

#endif
