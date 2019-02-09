//==============================================================================
// Object_Bool.h
//==============================================================================
#ifndef GURAX_OBJECT_BOOL_H
#define GURAX_OBJECT_BOOL_H
#include "Object_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Bool
//------------------------------------------------------------------------------
class VType_Bool : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_Bool VTYPE_Bool;

//------------------------------------------------------------------------------
// Object_Bool
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Bool : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Bool);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Bool");
private:
	bool _flag;
public:
	// Constructor
	explicit Object_Bool(VType& vtype = VTYPE_Bool) :
		Object_Bool(false, vtype) {}
	explicit Object_Bool(bool flag, VType& vtype = VTYPE_Bool) :
		Object_Object(vtype), _flag(flag) {}
	// Copy constructor/operator
	Object_Bool(const Object_Bool& src) :
		Object_Object(src), _flag(src._flag) {}
	Object_Bool& operator=(const Object_Bool& src) = delete;
	// Move constructor/operator
	Object_Bool(Object_Bool&& src) = delete;
	Object_Bool& operator=(Object_Bool&& src) noexcept = delete;
protected:
	// Destructor
	~Object_Bool() = default;
public:
	bool GetBool() const { return _flag; } // override Object::GetBool()
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return static_cast<size_t>(GetBool());
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) && GetBool() == dynamic_cast<const Object_Bool*>(pObject)->GetBool();
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetBool() < dynamic_cast<const Object_Bool*>(pObject)->GetBool() :
			GetVType().IsLessThan(pObject->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return _flag? "true" : "false";
	}
};

}

#endif
