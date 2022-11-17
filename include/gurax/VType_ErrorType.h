//==============================================================================
// VType_ErrorType.h
//==============================================================================
#ifndef GURAX_VTYPE_ERRORTYPE_H
#define GURAX_VTYPE_ERRORTYPE_H
#include "VType_Object.h"
#include "Error.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_ErrorType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_ErrorType : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_ErrorType VTYPE_ErrorType;

//------------------------------------------------------------------------------
// Value_ErrorType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_ErrorType : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_ErrorType);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_ErrorType");
protected:
	const ErrorType& _errorType;
public:
	static VType& vtype;
public:
	// Constructor
	Value_ErrorType() = delete;
	explicit Value_ErrorType(const ErrorType& errorType, VType& vtype = VTYPE_ErrorType) :
		Value_Object(vtype), _errorType(errorType) {}
	// Copy constructor/operator
	Value_ErrorType(const Value_ErrorType& src) :
		Value_Object(src), _errorType(src._errorType) {}
	Value_ErrorType& operator=(const Value_ErrorType& src) = delete;
	// Move constructor/operator
	Value_ErrorType(Value_ErrorType&& src) = delete;
	Value_ErrorType& operator=(Value_ErrorType&& src) noexcept = delete;
protected:
	// Destructor
	~Value_ErrorType() = default;
public:
	const ErrorType& GetErrorType() const { return _errorType; }
public:
	static const ErrorType& GetErrorType(const Value& value) { return dynamic_cast<const Value_ErrorType&>(value).GetErrorType(); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetErrorType().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetErrorType().IsEqualTo(dynamic_cast<const Value_ErrorType&>(value).GetErrorType());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetErrorType().IsLessThan(dynamic_cast<const Value_ErrorType&>(value).GetErrorType()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
