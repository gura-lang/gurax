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
class GURAX_DLLDECLARE Object_nil : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_nil);
public:
	class TypeInfoEx : public TypeInfo {
	public:
		// Constructor
		TypeInfoEx() : TypeInfo(&Object::typeInfo, "nil") {}
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
	// Constructor
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
};

}

#endif
