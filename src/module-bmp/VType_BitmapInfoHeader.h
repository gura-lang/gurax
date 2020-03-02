//==============================================================================
// VType_BitmapInfoHeader.h
//==============================================================================
#ifndef GURAX_MODULE_BMP_VTYPE_BITMAPINFOHEADER_H
#define GURAX_MODULE_BMP_VTYPE_BITMAPINFOHEADER_H
#include <gurax.h>
#include "Info.h"

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// VType_BitmapInfoHeader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_BitmapInfoHeader : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_BitmapInfoHeader VTYPE_BitmapInfoHeader;

//------------------------------------------------------------------------------
// Value_BitmapInfoHeader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_BitmapInfoHeader : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_BitmapInfoHeader);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_BitmapInfoHeader");
protected:
	RefPtr<Info> _pInfo;
public:
	static VType& vtype;
public:
	// Constructor
	Value_BitmapInfoHeader() = delete;
	explicit Value_BitmapInfoHeader(Info* pInfo, VType& vtype = VTYPE_BitmapInfoHeader) :
		Value_Object(vtype), _pInfo(pInfo) {}
	// Copy constructor/operator
	Value_BitmapInfoHeader(const Value_BitmapInfoHeader& src) :
		Value_Object(src), _pInfo(src._pInfo->Reference()) {}
	Value_BitmapInfoHeader& operator=(const Value_BitmapInfoHeader& src) = delete;
	// Move constructor/operator
	Value_BitmapInfoHeader(Value_BitmapInfoHeader&& src) = delete;
	Value_BitmapInfoHeader& operator=(Value_BitmapInfoHeader&& src) noexcept = delete;
protected:
	// Destructor
	~Value_BitmapInfoHeader() = default;
public:
	Info& GetInfo() { return *_pInfo; }
	const Info& GetInfo() const { return *_pInfo; }
public:
	static Info& GetInfo(Value& value) {
		return dynamic_cast<Value_BitmapInfoHeader&>(value).GetInfo();
	}
	static const Info& GetInfo(const Value& value) {
		return dynamic_cast<const Value_BitmapInfoHeader&>(value).GetInfo();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetInfo().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetInfo().IsEqualTo(Value_BitmapInfoHeader::GetInfo(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetInfo().IsLessThan(Value_BitmapInfoHeader::GetInfo(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetInfo().ToString(ss);
	}
};

Gurax_EndModuleScope(bmp)

#endif
