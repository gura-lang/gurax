//==============================================================================
// Object_StringPtr.h
// This object type is designed to be used with Formatter.
//==============================================================================
#ifndef GURAX_OBJECT_STRINGPTR_H
#define GURAX_OBJECT_STRINGPTR_H
#include "Object_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_StringPtr
//------------------------------------------------------------------------------
class VTypeT_StringPtr : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VTypeT_StringPtr VType_StringPtr;

//------------------------------------------------------------------------------
// Object_StringPtr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_StringPtr : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_StringPtr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_StringPtr");
private:
	const char* _str;
public:
	// Constructor
	explicit Object_StringPtr(VType& vtype = VType_StringPtr) :
		Object_StringPtr("", vtype) {}
	explicit Object_StringPtr(const char* str, VType& vtype = VType_StringPtr) :
		Object_Object(vtype), _str(str) {}
	// Copy constructor/operator
	Object_StringPtr(const Object_StringPtr& src) :
		Object_Object(src), _str(src._str) {}
	Object_StringPtr& operator=(const Object_StringPtr& src) = delete;
	// Move constructor/operator
	Object_StringPtr(Object_StringPtr&& src) = delete;
	Object_StringPtr& operator=(Object_StringPtr&& src) noexcept = delete;
protected:
	// Destructor
	~Object_StringPtr() = default;
public:
	const char* GetString() const { return _str; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return String::CalcHash(GetString());
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			String::IsEqualTo(GetString(), dynamic_cast<const Object_StringPtr*>(pObject)->GetString());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			String::IsLessThan(GetString(), dynamic_cast<const Object_StringPtr*>(pObject)->GetString()) :
			GetVType().IsLessThan(pObject->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return _str;
	}
	virtual bool Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const override;
};

}

#endif
