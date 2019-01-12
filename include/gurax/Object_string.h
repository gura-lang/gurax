//==============================================================================
// Object_string.h
//==============================================================================
#ifndef GURAX_OBJECT_STRING_H
#define GURAX_OBJECT_STRING_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_string
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_string : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_string);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_string");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	RefPtr<StringReferable> _pStr;
public:
	// Constructor
	explicit Object_string(StringReferable* pStr) : Object(klass), _pStr(pStr) {}
	explicit Object_string(String str) : Object(klass), _pStr(new StringReferable(std::move(str))) {}
	// Copy constructor/operator
	Object_string(const Object_string& src) : Object(klass), _pStr(src._pStr->Reference()) {}
	Object_string& operator=(const Object_string& src) { _pStr.reset(src._pStr->Reference()); return *this; }
	// Move constructor/operator
	Object_string(Object_string&& src) : Object(klass), _pStr(src._pStr->Reference()) {}
	Object_string& operator=(Object_string&& src) noexcept { _pStr.reset(src._pStr->Reference()); return *this; }
protected:
	// Destructor
	~Object_string() = default;
public:
	const char* GetString() const { return _pStr->GetString(); }
	const String& GetStringSTL() const { return _pStr->GetStringSTL(); }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return String::CalcHash(GetString()); }
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			String::IsEqualTo(GetString(), dynamic_cast<const Object_string*>(pObject)->GetString());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			String::IsLessThan(GetString(), dynamic_cast<const Object_string*>(pObject)->GetString()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle&) const override { return _pStr->GetStringSTL().MakeQuoted(true); }
};

}

#endif
