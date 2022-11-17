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
class GURAX_DLLDECLARE VType_Error : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Error VTYPE_Error;

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
	static VType& vtype;
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
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetError().IsEqualTo(dynamic_cast<const Value_Error&>(value).GetError());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetError().IsLessThan(dynamic_cast<const Value_Error&>(value).GetError()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
