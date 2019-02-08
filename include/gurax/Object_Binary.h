//==============================================================================
// Object_Binary.h
//==============================================================================
#ifndef GURAX_OBJECT_BINARY_H
#define GURAX_OBJECT_BINARY_H
#include "Object_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_Binary
//------------------------------------------------------------------------------
class KlassT_Binary : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_Binary Klass_Binary;

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
	explicit Object_Binary(BinaryReferable* pBinary, Klass& klass = Klass_Binary) :
		Object_Object(klass), _pBinary(pBinary) {}
	explicit Object_Binary(Binary str, Klass& klass = Klass_Binary) :
		Object_Object(klass), _pBinary(new BinaryReferable(std::move(str))) {}
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
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return String("b").append(_pBinary->GetBinary().MakeQuoted(true));
	}
};

}

#endif
