//==============================================================================
// Object_nil.h
//==============================================================================
#ifndef GURAX_OBJECT_NIL_H
#define GURAX_OBJECT_NIL_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_nil
//------------------------------------------------------------------------------
class KlassT_nil : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_nil Klass_nil;

//------------------------------------------------------------------------------
// Object_nil
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_nil : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_nil);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_nil");
public:
	// Constructor
	Object_nil() : Object(Klass_nil) {}
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
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Object* pObject) const override { return IsSameType(pObject); }
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)? false : GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return "nil";
	}
};

}

#endif
