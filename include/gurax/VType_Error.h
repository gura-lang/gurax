//==============================================================================
// VType_Error.h
//==============================================================================
#ifndef GURAX_VTYPE_ERROR_H
#define GURAX_VTYPE_ERROR_H
#include "VType_Object.h"
#include "Error.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Error
//------------------------------------------------------------------------------
class VType_Error : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Error VTYPE_Error;

//------------------------------------------------------------------------------
// Value_Error
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Error : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Error);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Error");
protected:
	RefPtr<Error> _pError;
public:
	// Constructor
	Value_Error() = delete;
	explicit Value_Error(Error* pError, VType& vtype = VTYPE_Error) :
		Value_Object(vtype), _pError(pError) {}
	// Copy constructor/operator
	Value_Error(const Value_Error& src) :
		Value_Object(src), _pError(src._pError.Reference()) {}
	Value_Error& operator=(const Value_Error& src) = delete;
	// Move constructor/operator
	Value_Error(Value_Error&& src) = delete;
	Value_Error& operator=(Value_Error&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Error() = default;
public:
	const Error& GetError() const { return *_pError; }
public:
	static const Error& GetError(const Value& value) { return dynamic_cast<const Value_Error&>(value).GetError(); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetError().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetError().IsEqualTo(dynamic_cast<const Value_Error*>(pValue)->GetError());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetError().IsLessThan(dynamic_cast<const Value_Error*>(pValue)->GetError()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDigest(const StringStyle& ss) const override;
	virtual String ToStringDetail(const StringStyle& ss) const override;
};

}

#endif
