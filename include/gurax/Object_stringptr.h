//==============================================================================
// Object_StringPtr.h
// This object type is designed to be used with Formatter.
//==============================================================================
#ifndef GURAX_OBJECT_STRINGPTR_H
#define GURAX_OBJECT_STRINGPTR_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_StringPtr
//------------------------------------------------------------------------------
class KlassT_StringPtr : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_StringPtr Klass_StringPtr;

//------------------------------------------------------------------------------
// Object_StringPtr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_StringPtr : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_StringPtr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_StringPtr");
private:
	const char* _str;
public:
	// Constructor
	explicit Object_StringPtr(const char* str) : Object(Klass_StringPtr), _str(str) {}
	// Copy constructor/operator
	Object_StringPtr(const Object_StringPtr& src) : Object(Klass_StringPtr), _str(src._str) {}
	Object_StringPtr& operator=(const Object_StringPtr& src) { _str = src._str; return *this; }
	// Move constructor/operator
	Object_StringPtr(Object_StringPtr&& src) : Object(Klass_StringPtr), _str(src._str) {}
	Object_StringPtr& operator=(Object_StringPtr&& src) noexcept { _str = src._str; return *this; }
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
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return _str;
	}
	virtual bool Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const override;
};

}

#endif
