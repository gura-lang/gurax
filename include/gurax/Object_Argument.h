//==============================================================================
// Object_Argument.h
//==============================================================================
#ifndef GURAX_OBJECT_ARGUMENT_H
#define GURAX_OBJECT_ARGUMENT_H
#include "Object_Object.h"
#include "Argument.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Argument
//------------------------------------------------------------------------------
class VTypeT_Argument : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VTypeT_Argument VType_Argument;

//------------------------------------------------------------------------------
// Object_Argument
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Argument : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Argument);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Argument");
private:
	std::unique_ptr<Argument> _pArgument;
public:
	// Constructor
	Object_Argument() = delete;
	Object_Argument(Argument* pArgument, VType& vtype = VType_Argument) :
		Object_Object(vtype), _pArgument(pArgument) {}
	// Copy constructor/operator
	Object_Argument(const Object_Argument& src) : Object_Object(src), _pArgument(src._pArgument->Clone()) {}
	Object_Argument& operator=(const Object_Argument& src) = delete;
	// Move constructor/operator
	Object_Argument(Object_Argument&& src) = delete;
	Object_Argument& operator=(Object_Argument&& src) noexcept = delete;
protected:
	// Destructor
	~Object_Argument() = default;
public:
	Argument& GetArgument() { return *_pArgument; }
	const Argument& GetArgument() const { return *_pArgument; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetArgument().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetArgument().IsEqualTo(dynamic_cast<const Object_Argument*>(pObject)->GetArgument());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetArgument().IsLessThan(dynamic_cast<const Object_Argument*>(pObject)->GetArgument()) :
			GetVType().IsLessThan(pObject->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetArgument().ToString(ss);
	}
};

}

#endif
