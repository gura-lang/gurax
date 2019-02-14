//==============================================================================
// Value_DateTime.h
//==============================================================================
#ifndef GURAX_VALUE_DATETIME_H
#define GURAX_VALUE_DATETIME_H
#include "Value_Object.h"
#include "DateTime.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_DateTime
//------------------------------------------------------------------------------
class VType_DateTime : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frame) override;
};

extern VType_DateTime VTYPE_DateTime;

//------------------------------------------------------------------------------
// Value_DateTime
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_DateTime : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_DateTime);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_DateTime");
private:
	RefPtr<DateTime> _pDateTime;
public:
	// Constructor
	explicit Value_DateTime(VType& vtype = VTYPE_DateTime) :
		Value_DateTime(new DateTime(), vtype) {}
	explicit Value_DateTime(DateTime *pDateTime, VType& vtype = VTYPE_DateTime) :
		Value_Object(vtype), _pDateTime(pDateTime) {}
	// Copy constructor/operator
	Value_DateTime(const Value_DateTime& src) :
		Value_Object(src), _pDateTime(src._pDateTime->Reference()) {}
	Value_DateTime& operator=(const Value_DateTime& src) = delete;
	// Move constructor/operator
	Value_DateTime(Value_DateTime&& src) = delete;
	Value_DateTime& operator=(Value_DateTime&& src) noexcept = delete;
protected:
	// Destructor
	~Value_DateTime() = default;
public:
	DateTime& GetDateTime() { return *_pDateTime; }
	const DateTime& GetDateTime() const { return *_pDateTime; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetDateTime().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetDateTime().IsEqualTo(dynamic_cast<const Value_DateTime*>(pValue)->GetDateTime());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetDateTime().IsLessThan(dynamic_cast<const Value_DateTime*>(pValue)->GetDateTime()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetDateTime().ToString(ss);
	}
};

}

#endif
