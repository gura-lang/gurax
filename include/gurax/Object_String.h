//==============================================================================
// Object_String.h
//==============================================================================
#ifndef GURAX_OBJECT_STRING_H
#define GURAX_OBJECT_STRING_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_String
//------------------------------------------------------------------------------
class KlassT_String : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_String Klass_String;

//------------------------------------------------------------------------------
// Object_String
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_String : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_String);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_String");
private:
	RefPtr<StringReferable> _pStr;
public:
	// Constructor
	explicit Object_String(StringReferable* pStr) : Object(Klass_String), _pStr(pStr) {}
	explicit Object_String(String str) : Object(Klass_String), _pStr(new StringReferable(std::move(str))) {}
	// Copy constructor/operator
	Object_String(const Object_String& src) : Object(Klass_String), _pStr(src._pStr->Reference()) {}
	Object_String& operator=(const Object_String& src) { _pStr.reset(src._pStr->Reference()); return *this; }
	// Move constructor/operator
	Object_String(Object_String&& src) : Object(Klass_String), _pStr(src._pStr->Reference()) {}
	Object_String& operator=(Object_String&& src) noexcept { _pStr.reset(src._pStr->Reference()); return *this; }
protected:
	// Destructor
	~Object_String() = default;
public:
	const char* GetString() const { return _pStr->GetString(); }
	const String& GetStringSTL() const { return _pStr->GetStringSTL(); }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return String::CalcHash(GetString());
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			String::IsEqualTo(GetString(), dynamic_cast<const Object_String*>(pObject)->GetString());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			String::IsLessThan(GetString(), dynamic_cast<const Object_String*>(pObject)->GetString()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return _pStr->GetStringSTL().MakeQuoted(true);
	}
	virtual bool Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const override;
};

}

#endif
