//==============================================================================
// Object_stringptr.h
// This object type is designed to be used with Formatter.
//==============================================================================
#ifndef GURAX_OBJECT_STRINGPTR_H
#define GURAX_OBJECT_STRINGPTR_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_stringptr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_stringptr : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_stringptr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_stringptr");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	const char* _str;
public:
	// Constructor
	explicit Object_stringptr(const char* str) : Object(klass), _str(str) {}
	// Copy constructor/operator
	Object_stringptr(const Object_stringptr& src) : Object(klass), _str(src._str) {}
	Object_stringptr& operator=(const Object_stringptr& src) { _str = src._str; return *this; }
	// Move constructor/operator
	Object_stringptr(Object_stringptr&& src) : Object(klass), _str(src._str) {}
	Object_stringptr& operator=(Object_stringptr&& src) noexcept { _str = src._str; return *this; }
protected:
	// Destructor
	~Object_stringptr() = default;
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
			String::IsEqualTo(GetString(), dynamic_cast<const Object_stringptr*>(pObject)->GetString());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			String::IsLessThan(GetString(), dynamic_cast<const Object_stringptr*>(pObject)->GetString()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return _str;
	}
	virtual bool Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const override;
};

}

#endif
