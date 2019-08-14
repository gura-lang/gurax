//==============================================================================
// VType_DirRecord.h
//==============================================================================
#ifndef GURAX_VTYPE_DIRRECORD_H
#define GURAX_VTYPE_DIRRECORD_H
#include "VType_Object.h"
#include "DirRecord.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_DirRecord
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_DirRecord : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_DirRecord VTYPE_DirRecord;

//------------------------------------------------------------------------------
// Value_DirRecord
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_DirRecord : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_DirRecord);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_DirRecord");
protected:
	RefPtr<DirRecord> _pDirRecord;
public:
	// Constructor
	Value_DirRecord() = delete;
	Value_DirRecord(DirRecord* pDirRecord, VType& vtype = VTYPE_DirRecord) :
		Value_Object(vtype), _pDirRecord(pDirRecord) {}
	// Copy constructor/operator
	Value_DirRecord(const Value_DirRecord& src) :
		Value_Object(src), _pDirRecord(src._pDirRecord->Reference()) {}
	Value_DirRecord& operator=(const Value_DirRecord& src) = delete;
	// Move constructor/operator
	Value_DirRecord(Value_DirRecord&& src) = delete;
	Value_DirRecord& operator=(Value_DirRecord&& src) noexcept = delete;
protected:
	// Destructor
	~Value_DirRecord() = default;
public:
	DirRecord& GetDirRecord() { return *_pDirRecord; }
	const DirRecord& GetDirRecord() const { return *_pDirRecord; }
public:
	static DirRecord& GetDirRecord(Value& value) {
		return dynamic_cast<Value_DirRecord&>(value).GetDirRecord();
	}
	static const DirRecord& GetDirRecord(const Value& value) {
		return dynamic_cast<const Value_DirRecord&>(value).GetDirRecord();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetDirRecord().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetDirRecord().IsEqualTo(Value_DirRecord::GetDirRecord(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetDirRecord().IsLessThan(Value_DirRecord::GetDirRecord(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetDirRecord().ToString(ss);
	}
};

}

#endif
