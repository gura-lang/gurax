//==============================================================================
// Object_Any.h
//==============================================================================
#ifndef GURAX_OBJECT_ANY_H
#define GURAX_OBJECT_ANY_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_Any
//------------------------------------------------------------------------------
class KlassT_Any : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_Any Klass_Any;

//------------------------------------------------------------------------------
// Object_Any
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Any : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Any);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Any");
public:
	// Constructor
	Object_Any() : Object(Klass_Any) {}
	// Copy constructor/operator
	Object_Any(const Object_Any& src) = delete;
	Object_Any& operator=(const Object_Any& src) = delete;
	// Move constructor/operator
	Object_Any(Object_Any&& src) = delete;
	Object_Any& operator=(Object_Any&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Object_Any() = default;
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Object* pObject) const override { return IsSameType(pObject); }
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)? false : GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return "any";
	}
};

}

#endif
