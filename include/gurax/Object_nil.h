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
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
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
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Object* pObject) const override { return IsSameType(pObject); }
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)? false : GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual bool IsGreaterThan(const Object* pObject) const override {
		return IsSameType(pObject)? false : GetKlass().IsGreaterThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle&) const override { return "nil"; }
};

}

#endif
