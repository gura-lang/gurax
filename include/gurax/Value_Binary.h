//==============================================================================
// Value_Binary.h
//==============================================================================
#ifndef GURAX_VALUE_BINARY_H
#define GURAX_VALUE_BINARY_H
#include "Value_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Binary
//------------------------------------------------------------------------------
class VType_Binary : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_Binary VTYPE_Binary;

//------------------------------------------------------------------------------
// Value_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Binary : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Binary);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Binary");
private:
	RefPtr<BinaryReferable> _pBinary;
public:
	// Constructor
	explicit Value_Binary(VType& vtype = VTYPE_Binary) :
		Value_Binary(new BinaryReferable(), vtype) {}
	explicit Value_Binary(BinaryReferable* pBinary, VType& vtype = VTYPE_Binary) :
		Value_Object(vtype), _pBinary(pBinary) {}
	explicit Value_Binary(Binary str, VType& vtype = VTYPE_Binary) :
		Value_Binary(new BinaryReferable(std::move(str)), vtype) {}
	// Copy constructor/operator
	Value_Binary(const Value_Binary& src) = delete;
	Value_Binary& operator=(const Value_Binary& src) = delete;
	// Move constructor/operator
	Value_Binary(Value_Binary&& src) = delete;
	Value_Binary& operator=(Value_Binary&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Binary() = default;
public:
	Binary& GetBinary() { return _pBinary->GetBinary(); }
	const Binary& GetBinary() const { return _pBinary->GetBinary(); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetBinary().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetBinary().IsEqualTo(dynamic_cast<const Value_Binary*>(pValue)->GetBinary());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetBinary().IsLessThan(dynamic_cast<const Value_Binary*>(pValue)->GetBinary()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return String("b").append(_pBinary->GetBinary().MakeQuoted(true));
	}
};

}

#endif
