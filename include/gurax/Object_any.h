//==============================================================================
// Object_any.h
//==============================================================================
#ifndef GURAX_OBJECT_ANY_H
#define GURAX_OBJECT_ANY_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_any
//------------------------------------------------------------------------------
class KlassT_any : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_any Klass_any;

//------------------------------------------------------------------------------
// Object_any
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_any : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_any);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_any");
public:
	// Constructor
	Object_any() : Object(Klass_any) {}
	// Copy constructor/operator
	Object_any(const Object_any& src) = delete;
	Object_any& operator=(const Object_any& src) = delete;
	// Move constructor/operator
	Object_any(Object_any&& src) = delete;
	Object_any& operator=(Object_any&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Object_any() = default;
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
