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
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("nil");
public:
	class KlassEx : public Klass {
	public:
		// Constructor
		KlassEx() : Klass(&Object::klass, "nil") {}
	};
public:
	static KlassEx klass;
public:
	// Constructor
	Object_nil() : Object(klass) {}
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
	virtual Object* Clone() const override { return Reference(); }
	virtual String ToString() const override { return "nil"; }
	virtual String GenSource() const override { return ToString(); }
};

}

#endif
