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
	class TypeInfoEx : public TypeInfo {
	public:
		// Constructor
		TypeInfoEx() : TypeInfo(&Object::typeInfo, "string") {}
		// Copy constructor/operator
		TypeInfoEx(const TypeInfoEx& src) = delete;
		TypeInfoEx& operator=(const TypeInfoEx& src) = delete;
		// Move constructor/operator
		TypeInfoEx(TypeInfoEx&& src) = delete;
		TypeInfoEx& operator=(TypeInfoEx&& src) noexcept = delete;
		// Destructor
		~TypeInfoEx() = default;
	};
public:
	static const TypeInfoEx typeInfo;
private:
	RefPtr<StringReferable> _pStr;
public:
	// Constructor
	explicit Object_string(StringReferable* pStr) : Object(typeInfo), _pStr(pStr) {}
	explicit Object_string(String str) : Object(typeInfo), _pStr(new StringReferable(std::move(str))) {}
	// Copy constructor/operator
	Object_string(const Object_string& src) : Object(typeInfo), _pStr(src._pStr->Reference()) {}
	Object_string& operator=(const Object_string& src) { _pStr.reset(src._pStr->Reference()); return *this; }
	// Move constructor/operator
	Object_string(Object_string&& src) : Object(typeInfo), _pStr(src._pStr->Reference()) {}
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
