//==============================================================================
// VType_IFD.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_VTYPE_IFD_H
#define GURAX_MODULE_JPEG_VTYPE_IFD_H
#include <gurax.h>
#include "IFD.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// VType_IFD
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_IFD : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_IFD VTYPE_IFD;

//------------------------------------------------------------------------------
// Value_IFD
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_IFD : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_IFD);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_IFD");
protected:
	RefPtr<IFD> _pIFD;
public:
	static VType& vtype;
public:
	// Constructor
	Value_IFD() = delete;
	explicit Value_IFD(IFD* pIFD, VType& vtype = VTYPE_IFD) :
		Value_Object(vtype), _pIFD(pIFD) {}
	// Copy constructor/operator
	Value_IFD(const Value_IFD& src) :
		Value_Object(src), _pIFD(src._pIFD->Reference()) {}
	Value_IFD& operator=(const Value_IFD& src) = delete;
	// Move constructor/operator
	Value_IFD(Value_IFD&& src) = delete;
	Value_IFD& operator=(Value_IFD&& src) noexcept = delete;
protected:
	// Destructor
	~Value_IFD() = default;
public:
	IFD& GetIFD() { return *_pIFD; }
	const IFD& GetIFD() const { return *_pIFD; }
public:
	static IFD& GetIFD(Value& value) {
		return dynamic_cast<Value_IFD&>(value).GetIFD();
	}
	static const IFD& GetIFD(const Value& value) {
		return dynamic_cast<const Value_IFD&>(value).GetIFD();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetIFD().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetIFD().IsEqualTo(Value_IFD::GetIFD(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetIFD().IsLessThan(Value_IFD::GetIFD(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetIFD().ToString(ss);
	}
};

Gurax_EndModuleScope(jpeg)

#endif