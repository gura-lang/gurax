//==============================================================================
// Object_Binary.h
//==============================================================================
#ifndef GURAX_OBJECT_BINARY_H
#define GURAX_OBJECT_BINARY_H
#include "Object_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Binary
//------------------------------------------------------------------------------
class VTypeT_Binary : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VTypeT_Binary VType_Binary;

//------------------------------------------------------------------------------
// Object_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Binary : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Binary);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Binary");
private:
	RefPtr<BinaryReferable> _pBinary;
public:
	// Constructor
	explicit Object_Binary(VType& vtype = VType_Binary) :
		Object_Binary(new BinaryReferable(), vtype) {}
	explicit Object_Binary(BinaryReferable* pBinary, VType& vtype = VType_Binary) :
		Object_Object(vtype), _pBinary(pBinary) {}
	explicit Object_Binary(Binary str, VType& vtype = VType_Binary) :
		Object_Binary(new BinaryReferable(std::move(str)), vtype) {}
	// Copy constructor/operator
	Object_Binary(const Object_Binary& src) = delete;
	Object_Binary& operator=(const Object_Binary& src) = delete;
	// Move constructor/operator
	Object_Binary(Object_Binary&& src) = delete;
	Object_Binary& operator=(Object_Binary&& src) noexcept = delete;
protected:
	// Destructor
	~Object_Binary() = default;
public:
	Binary& GetBinary() { return _pBinary->GetBinary(); }
	const Binary& GetBinary() const { return _pBinary->GetBinary(); }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetBinary().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetBinary().IsEqualTo(dynamic_cast<const Object_Binary*>(pObject)->GetBinary());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetBinary().IsLessThan(dynamic_cast<const Object_Binary*>(pObject)->GetBinary()) :
			GetVType().IsLessThan(pObject->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return String("b").append(_pBinary->GetBinary().MakeQuoted(true));
	}
};

}

#endif
