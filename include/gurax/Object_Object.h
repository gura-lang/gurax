//==============================================================================
// Object_Object.h
//==============================================================================
#ifndef GURAX_OBJECT_OBJECT_H
#define GURAX_OBJECT_OBJECT_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Object
//------------------------------------------------------------------------------
class VType_Object : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_Object VTYPE_Object;

//------------------------------------------------------------------------------
// Object_Object
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Object : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Object);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Object");
public:
	// Constructor
	Object_Object() : Object_Object(VTYPE_Object) {}
	explicit Object_Object(VType& vtype) : Object(vtype) {}
	// Copy constructor/operator
	Object_Object(const Object_Object& src) : Object(src) {}
	Object_Object& operator=(const Object_Object& src) = delete;
	// Move constructor/operator
	Object_Object(Object_Object&& src) = delete;
	Object_Object& operator=(Object_Object&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Object_Object() = default;
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Object* pObject) const override { return IsSameType(pObject); }
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)? false : GetVType().IsLessThan(pObject->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return "Object";
	}
};

}

#endif
