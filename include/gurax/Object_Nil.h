//==============================================================================
// Object_Nil.h
//==============================================================================
#ifndef GURAX_OBJECT_NIL_H
#define GURAX_OBJECT_NIL_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_Nil
//------------------------------------------------------------------------------
class KlassT_Nil : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_Nil Klass_Nil;

//------------------------------------------------------------------------------
// Object_Nil
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Nil : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Nil);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Nil");
public:
	// Constructor
	Object_Nil() : Object(Klass_Nil) {}
	// Copy constructor/operator
	Object_Nil(const Object_Nil& src) = delete;
	Object_Nil& operator=(const Object_Nil& src) = delete;
	// Move constructor/operator
	Object_Nil(Object_Nil&& src) = delete;
	Object_Nil& operator=(Object_Nil&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Object_Nil() = default;
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
