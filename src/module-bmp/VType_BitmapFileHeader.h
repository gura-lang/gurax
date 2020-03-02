//==============================================================================
// VType_BitmapFileHeader.h
//==============================================================================
#ifndef GURAX_MODULE_BMP_VTYPE_BITMAPFILEHEADER_H
#define GURAX_MODULE_BMP_VTYPE_BITMAPFILEHEADER_H
#include <gurax.h>
#include "Info.h"

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// VType_BitmapFileHeader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_BitmapFileHeader : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_BitmapFileHeader VTYPE_BitmapFileHeader;

//------------------------------------------------------------------------------
// Value_BitmapFileHeader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_BitmapFileHeader : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_BitmapFileHeader);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_BitmapFileHeader");
protected:
	RefPtr<Info> _pInfo;
public:
	static VType& vtype;
public:
	// Constructor
	Value_BitmapFileHeader() = delete;
	explicit Value_BitmapFileHeader(Info* pInfo, VType& vtype = VTYPE_BitmapFileHeader) :
		Value_Object(vtype), _pInfo(pInfo) {}
	// Copy constructor/operator
	Value_BitmapFileHeader(const Value_BitmapFileHeader& src) :
		Value_Object(src), _pInfo(src._pInfo->Reference()) {}
	Value_BitmapFileHeader& operator=(const Value_BitmapFileHeader& src) = delete;
	// Move constructor/operator
	Value_BitmapFileHeader(Value_BitmapFileHeader&& src) = delete;
	Value_BitmapFileHeader& operator=(Value_BitmapFileHeader&& src) noexcept = delete;
protected:
	// Destructor
	~Value_BitmapFileHeader() = default;
public:
	Info& GetInfo() { return *_pInfo; }
	const Info& GetInfo() const { return *_pInfo; }
public:
	static Info& GetInfo(Value& value) {
		return dynamic_cast<Value_BitmapFileHeader&>(value).GetInfo();
	}
	static const Info& GetInfo(const Value& value) {
		return dynamic_cast<const Value_BitmapFileHeader&>(value).GetInfo();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetInfo().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetInfo().IsEqualTo(Value_BitmapFileHeader::GetInfo(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetInfo().IsLessThan(Value_BitmapFileHeader::GetInfo(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetInfo().ToString(ss);
	}
};

Gurax_EndModuleScope(bmp)

#endif
