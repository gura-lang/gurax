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
class GURAX_DLLDECLARE Object_undefined : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_undefined);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("undefined");
	// Class declaration
	class KlassEx : public Klass {
	public:
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
public:
	// Constructor
	Object_undefined() : Object(klass) {}
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
	virtual Object* Clone() const override { return Reference(); }
	virtual String ToString() const override { return "undefined"; }
	virtual String GenSource() const override { return ToString(); }
};

}

#endif
