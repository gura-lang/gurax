//==============================================================================
// Object_binary.h
//==============================================================================
#ifndef GURAX_OBJECT_BINARY_H
#define GURAX_OBJECT_BINARY_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_binary : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_binary);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("binary");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	RefPtr<BinaryReferable> _pBinary;
public:
	// Constructor
	explicit Object_binary(BinaryReferable* pBinary) : Object(klass), _pBinary(pBinary) {}
	explicit Object_binary(Binary str) : Object(klass), _pBinary(new BinaryReferable(std::move(str))) {}
	// Copy constructor/operator
	Object_binary(const Object_binary& src) : Object(klass), _pBinary(src._pBinary->Reference()) {}
	Object_binary& operator=(const Object_binary& src) { _pBinary.reset(src._pBinary->Reference()); return *this; }
	// Move constructor/operator
	Object_binary(Object_binary&& src) : Object(klass), _pBinary(src._pBinary->Reference()) {}
	Object_binary& operator=(Object_binary&& src) noexcept { _pBinary.reset(src._pBinary->Reference()); return *this; }
protected:
	// Destructor
	~Object_binary() = default;
public:
	const Binary& GetBinary() const { return _pBinary->GetBinary(); }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return GetBinary().CalcHash(); }
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetBinary().IsEqualTo(dynamic_cast<const Object_binary*>(pObject)->GetBinary());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetBinary().IsLessThan(dynamic_cast<const Object_binary*>(pObject)->GetBinary()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle&) const override { return _pBinary->GetBinary().MakeQuoted(true); }
};

}

#endif
