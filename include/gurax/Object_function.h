//==============================================================================
// Object_function.h
//==============================================================================
#ifndef GURAX_OBJECT_FUNCTION_H
#define GURAX_OBJECT_FUNCTION_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_function
//------------------------------------------------------------------------------
class KlassT_function : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_function Klass_function;

//------------------------------------------------------------------------------
// Object_function
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_function : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_function);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_function");
private:
	RefPtr<Function> _pFunction;
public:
	// Constructor
	Object_function() = delete;
	explicit Object_function(Function* pFunction) : Object(Klass_function), _pFunction(pFunction) {}
	// Copy constructor/operator
	Object_function(const Object_function& src) : Object(Klass_function), _pFunction(src._pFunction->Reference()) {}
	Object_function& operator=(const Object_function& src) { _pFunction.reset(src._pFunction->Reference()); return *this; }
	// Move constructor/operator
	Object_function(Object_function&& src) : Object(Klass_function), _pFunction(src._pFunction.release()) {}
	Object_function& operator=(Object_function&& src) noexcept { _pFunction.reset(src._pFunction.release()); return *this; }
protected:
	// Destructor
	~Object_function() = default;
public:
	Function& GetFunction() { return *_pFunction; }
	const Function& GetFunction() const { return *_pFunction; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetFunction().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetFunction().IsEqualTo(dynamic_cast<const Object_function*>(pObject)->GetFunction());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetFunction().IsLessThan(dynamic_cast<const Object_function*>(pObject)->GetFunction()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetFunction().ToString(ss);
	}
};

}

#endif
