//==============================================================================
// VType_Stat.h
//==============================================================================
#ifndef GURAX_VTYPE_STAT_H
#define GURAX_VTYPE_STAT_H
#include "VType_Object.h"
#include "Stat.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Stat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Stat : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Stat VTYPE_Stat;

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
	RefPtr<Stat> _pStat;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Stat() = delete;
	explicit Value_Stat(Stat* pStat, VType& vtype = VTYPE_Stat) :
		Value_Object(vtype), _pStat(pStat) {}
	// Copy constructor/operator
	Value_Stat(const Value_Stat& src) :
		Value_Object(src), _pStat(src._pStat->Reference()) {}
	Value_Stat& operator=(const Value_Stat& src) = delete;
	// Move constructor/operator
	Value_Stat(Value_Stat&& src) = delete;
	Value_Stat& operator=(Value_Stat&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Stat() = default;
public:
	Stat& GetStat() { return *_pStat; }
	const Stat& GetStat() const { return *_pStat; }
public:
	static Stat& GetStat(Value& value) {
		return dynamic_cast<Value_Stat&>(value).GetStat();
	}
	static const Stat& GetStat(const Value& value) {
		return dynamic_cast<const Value_Stat&>(value).GetStat();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetStat().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetStat().IsEqualTo(Value_Stat::GetStat(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetStat().IsLessThan(Value_Stat::GetStat(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringFormatter(const StringStyle& ss) const override;
	virtual String ToStringDetail(const StringStyle& ss) const override;
};

}

#endif
