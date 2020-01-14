//==============================================================================
// VType_Stat.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_VTYPE_STAT_H
#define GURAX_MODULE_ZIP_VTYPE_STAT_H
#include <gurax.h>
#include "Stat.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// VType_Stat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Stat : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Stat VTYPE_Stat;

//------------------------------------------------------------------------------
// Value_Stat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Stat : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Stat);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Stat");
protected:
	RefPtr<CentralFileHeader> _pHdr;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Stat() = delete;
	explicit Value_Stat(CentralFileHeader* pHdr, VType& vtype = VTYPE_Stat) :
		Value_Object(vtype), _pHdr(pHdr) {}
	// Copy constructor/operator
	Value_Stat(const Value_Stat& src) :
		Value_Object(src), _pHdr(src._pHdr->Reference()) {}
	Value_Stat& operator=(const Value_Stat& src) = delete;
	// Move constructor/operator
	Value_Stat(Value_Stat&& src) = delete;
	Value_Stat& operator=(Value_Stat&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Stat() = default;
public:
	CentralFileHeader& GetCentralFileHeader() { return *_pHdr; }
	const CentralFileHeader& GetCentralFileHeader() const { return *_pHdr; }
public:
	static CentralFileHeader& GetCentralFileHeader(Value& value) {
		return dynamic_cast<Value_Stat&>(value).GetCentralFileHeader();
	}
	static const CentralFileHeader& GetCentralFileHeader(const Value& value) {
		return dynamic_cast<const Value_Stat&>(value).GetCentralFileHeader();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetCentralFileHeader().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetCentralFileHeader().IsEqualTo(Value_Stat::GetCentralFileHeader(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetCentralFileHeader().IsLessThan(Value_Stat::GetCentralFileHeader(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetCentralFileHeader().ToString(ss);
	}
};

Gurax_EndModuleScope(zip)

#endif
