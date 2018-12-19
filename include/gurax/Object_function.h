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
	class TypeInfoEx : public TypeInfo {
	public:
		// Constructor
		TypeInfoEx() : TypeInfo(&Object::typeInfo) {}
		// Copy constructor/operator
		TypeInfoEx(const TypeInfoEx& src) = delete;
		TypeInfoEx& operator=(const TypeInfoEx& src) = delete;
		// Move constructor/operator
		TypeInfoEx(TypeInfoEx&& src) = delete;
		TypeInfoEx& operator=(TypeInfoEx&& src) noexcept = delete;
		// Destructor
		~TypeInfoEx() = default;
	public:
		virtual Object* Clone(const Object* pObj) const override {
			return new Object_function(*reinterpret_cast<const Object_function*>(pObj));
		}
	};
public:
	static const TypeInfoEx typeInfo;
private:
	RefPtr<Function> _pFunc;
public:
	// Constructor
	Object_function() = delete;
	Object_function(Function *pFunc) : Object(typeInfo), _pFunc(pFunc) {}
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
	// Referable accessor
	Gurax_DeclareReferable(Object_function);
public:
	const Function* GetFunction() const { return _pFunc.get(); }
};

}

#endif
