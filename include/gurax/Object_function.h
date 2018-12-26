//==============================================================================
// Object_function.h
//==============================================================================
#ifndef GURAX_OBJECT_FUNCTION_H
#define GURAX_OBJECT_FUNCTION_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_function
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_function : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_function);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("function");
public:
	class TypeInfoEx : public TypeInfo {
	public:
		// Constructor
		TypeInfoEx() : TypeInfo(&Object::typeInfo, "function") {}
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
	RefPtr<Function> _pFunc;
public:
	// Constructor
	Object_function() = delete;
	explicit Object_function(Function *pFunc) : Object(typeInfo), _pFunc(pFunc) {}
	// Copy constructor/operator
	Object_function(const Object_function& src) : Object(typeInfo), _pFunc(src._pFunc->Reference()) {}
	Object_function& operator=(const Object_function& src) { _pFunc.reset(src._pFunc->Reference()); return *this; }
	// Move constructor/operator
	Object_function(Object_function&& src) : Object(typeInfo), _pFunc(src._pFunc.release()) {}
	Object_function& operator=(Object_function&& src) noexcept { _pFunc.reset(src._pFunc.release()); return *this; }
protected:
	// Destructor
	~Object_function() = default;
public:
	const Function* GetFunction() const { return _pFunc.get(); }
	virtual Object* Clone() const override { return Reference(); }
};

}

#endif
