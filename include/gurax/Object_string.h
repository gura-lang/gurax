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
	Gurax_MemoryPoolAllocator("string");
public:
	class KlassEx : public Klass {
	public:
		// Constructor
		KlassEx() : Klass(&Object::klass, "string") {}
	public:
		virtual void DoPrepare() override;
	};
public:
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
	virtual Object* Clone() const override { return Reference(); }
	virtual String ToString() const override { return _pStr->GetStringSTL().MakeQuoted(true); }
	virtual String GenSource() const override { return ToString(); }
};

}

#endif
