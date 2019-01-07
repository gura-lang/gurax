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
	RefPtr<BinaryReferable> _pStr;
public:
	// Constructor
	explicit Object_binary(BinaryReferable* pStr) : Object(klass), _pStr(pStr) {}
	explicit Object_binary(Binary str) : Object(klass), _pStr(new BinaryReferable(std::move(str))) {}
	// Copy constructor/operator
	Object_binary(const Object_binary& src) : Object(klass), _pStr(src._pStr->Reference()) {}
	Object_binary& operator=(const Object_binary& src) { _pStr.reset(src._pStr->Reference()); return *this; }
	// Move constructor/operator
	Object_binary(Object_binary&& src) : Object(klass), _pStr(src._pStr->Reference()) {}
	Object_binary& operator=(Object_binary&& src) noexcept { _pStr.reset(src._pStr->Reference()); return *this; }
protected:
	// Destructor
	~Object_binary() = default;
public:
	const char* GetBinary() const { return _pStr->GetBinary(); }
	const Binary& GetBinarySTL() const { return _pStr->GetBinarySTL(); }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return Binary::CalcHash(GetBinary()); }
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			Binary::IsEqualTo(GetBinary(), dynamic_cast<const Object_binary*>(pObject)->GetBinary());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			Binary::IsLessThan(GetBinary(), dynamic_cast<const Object_binary*>(pObject)->GetBinary()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle&) const override { return _pStr->GetStringSTL().MakeQuoted(true); }
};

}

#endif
