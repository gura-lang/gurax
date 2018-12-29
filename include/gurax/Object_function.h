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
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	RefPtr<Function> _pFunc;
public:
	// Constructor
	Object_function() = delete;
	explicit Object_function(Function *pFunc) : Object(klass), _pFunc(pFunc) {}
	// Copy constructor/operator
	Object_function(const Object_function& src) : Object(klass), _pFunc(src._pFunc->Reference()) {}
	Object_function& operator=(const Object_function& src) { _pFunc.reset(src._pFunc->Reference()); return *this; }
	// Move constructor/operator
	Object_function(Object_function&& src) : Object(klass), _pFunc(src._pFunc.release()) {}
	Object_function& operator=(Object_function&& src) noexcept { _pFunc.reset(src._pFunc.release()); return *this; }
protected:
	// Destructor
	~Object_function() = default;
public:
	const Function* GetFunction() const { return _pFunc.get(); }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return reinterpret_cast<size_t>(this); }
	virtual bool IsEqualTo(const Object* pObject) const override { return IsIdentical(pObject); }
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetFunction()->IsLessThan(dynamic_cast<const Object_function*>(pObject)->GetFunction()) :
			GetKlass().IsLessThan(pObject->GetKlass());
		
	}
	virtual String ToString() const override { return _pFunc->ToString(); }
};

}

#endif
