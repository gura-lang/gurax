//==============================================================================
// VType_Binary.h
//==============================================================================
#ifndef GURAX_VTYPE_BINARY_H
#define GURAX_VTYPE_BINARY_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Binary : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Binary VTYPE_Binary;

//------------------------------------------------------------------------------
// Value_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Binary : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Binary);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Binary");
protected:
	RefPtr<BinaryReferable> _pBinary;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_Binary(VType& vtype = VTYPE_Binary) :
		Value_Binary(new BinaryReferable(), vtype) {}
	explicit Value_Binary(BinaryReferable* pBinary, VType& vtype = VTYPE_Binary) :
		Value_Object(vtype), _pBinary(pBinary) {}
	explicit Value_Binary(Binary binary, VType& vtype = VTYPE_Binary) :
		Value_Binary(new BinaryReferable(std::move(binary)), vtype) {}
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
	BinaryReferable& GetBinaryReferable() { return *_pBinary; }
	const BinaryReferable& GetBinaryReferable() const { return *_pBinary; }
public:
	static Binary& GetBinary(Value& value) {
		return dynamic_cast<Value_Binary&>(value).GetBinary();
	}
	static const Binary& GetBinary(const Value& value) {
		return dynamic_cast<const Value_Binary&>(value).GetBinary();
	}
	static BinaryReferable& GetBinaryReferable(Value& value) {
		return dynamic_cast<Value_Binary&>(value).GetBinaryReferable();
	}
	static const BinaryReferable& GetBinaryReferable(const Value& value) {
		return dynamic_cast<const Value_Binary&>(value).GetBinaryReferable();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override {
		Binary buff = GetBinary();
		buff.SetWritableFlag(true);
		return new Value_Binary(new BinaryReferable(buff));
	}
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
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
