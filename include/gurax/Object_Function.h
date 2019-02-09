//==============================================================================
// Object_Function.h
//==============================================================================
#ifndef GURAX_OBJECT_FUNCTION_H
#define GURAX_OBJECT_FUNCTION_H
#include "Object_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Function
//------------------------------------------------------------------------------
class VTypeT_Function : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VTypeT_Function VType_Function;

//------------------------------------------------------------------------------
// Object_Function
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Function : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Function);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Function");
private:
	RefPtr<Function> _pFunction;
public:
	// Constructor
	Object_Function() = delete;
	explicit Object_Function(Function* pFunction, VType& vtype = VType_Function) :
		Object_Object(vtype), _pFunction(pFunction) {}
	// Copy constructor/operator
	Object_Function(const Object_Function& src) :
		Object_Object(src), _pFunction(src._pFunction->Reference()) {}
	Object_Function& operator=(const Object_Function& src) = delete;
	// Move constructor/operator
	Object_Function(Object_Function&& src) = delete;
	Object_Function& operator=(Object_Function&& src) noexcept = delete;
protected:
	// Destructor
	~Object_Function() = default;
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
			GetFunction().IsEqualTo(dynamic_cast<const Object_Function*>(pObject)->GetFunction());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetFunction().IsLessThan(dynamic_cast<const Object_Function*>(pObject)->GetFunction()) :
			GetVType().IsLessThan(pObject->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetFunction().ToString(ss);
	}
};

}

#endif
