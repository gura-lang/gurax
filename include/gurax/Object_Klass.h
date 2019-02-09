//==============================================================================
// Object_VType.h
//==============================================================================
#ifndef GURAX_OBJECT_KLASS_H
#define GURAX_OBJECT_KLASS_H
#include "Object_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_VType
//------------------------------------------------------------------------------
class VType_VType : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_VType VTYPE_VType;

//------------------------------------------------------------------------------
// Object_VType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_VType : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_VType);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_VType");
private:
	VType* _pVTypeThis;
public:
	// Constructor
	Object_VType() = delete;
	explicit Object_VType(VType& vtypeThis, VType& vtype = VTYPE_VType) :
		Object_Object(vtype), _pVTypeThis(&vtypeThis) {}
	// Copy constructor/operator
	Object_VType(const Object_VType& src) :
		Object_Object(src), _pVTypeThis(src._pVTypeThis) {}
	Object_VType& operator=(const Object_VType& src) = delete;
	// Move constructor/operator
	Object_VType(Object_VType&& src) = delete;
	Object_VType& operator=(Object_VType&& src) noexcept = delete;
protected:
	// Destructor
	~Object_VType() = default;
public:
	VType& GetVTypeThis() { return *_pVTypeThis; }
	const VType& GetVTypeThis() const { return *_pVTypeThis; }
public:
	// Virtual vtypes of Object
	virtual Frame* ProvideFrame() override { return &GetVTypeThis().GetFrame(); }
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetVTypeThis().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetVTypeThis().IsEqualTo(dynamic_cast<const Object_VType*>(pObject)->GetVTypeThis());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetVTypeThis().IsLessThan(dynamic_cast<const Object_VType*>(pObject)->GetVTypeThis()) :
			GetVType().IsLessThan(pObject->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetVTypeThis().ToString(ss);
	}
};

}

#endif
