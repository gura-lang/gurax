//==============================================================================
// VType_StatEx.h
//==============================================================================
#ifndef GURAX_MODULE_FS_VTYPE_STATEX_H
#define GURAX_MODULE_FS_VTYPE_STATEX_H
#include <gurax.h>
#include "PathExtension.h"

Gurax_BeginModuleScope(fs)

//------------------------------------------------------------------------------
// VType_StatEx
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_StatEx : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_StatEx VTYPE_StatEx;

//------------------------------------------------------------------------------
// Value_StatEx
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_StatEx : public Value_Stat {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_StatEx);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_StatEx");
public:
	static VType& vtype;
public:
	// Constructor
	Value_StatEx() = delete;
	Value_StatEx(StatEx* pStatEx, VType& vtype = VTYPE_StatEx) : Value_Stat(pStatEx, vtype) {}
	// Copy constructor/operator
	Value_StatEx(const Value_StatEx& src) : Value_Stat(src) {}
	Value_StatEx& operator=(const Value_StatEx& src) = delete;
	// Move constructor/operator
	Value_StatEx(Value_StatEx&& src) = delete;
	Value_StatEx& operator=(Value_StatEx&& src) noexcept = delete;
protected:
	// Destructor
	~Value_StatEx() = default;
public:
	StatEx& GetStatEx() { return dynamic_cast<StatEx&>(GetStat()); }
	const StatEx& GetStatEx() const { return dynamic_cast<const StatEx&>(GetStat()); }
public:
	static StatEx& GetStatEx(Value& value) {
		return dynamic_cast<Value_StatEx&>(value).GetStatEx();
	}
	static const StatEx& GetStatEx(const Value& value) {
		return dynamic_cast<const Value_StatEx&>(value).GetStatEx();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetStatEx().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetStatEx().IsEqualTo(Value_StatEx::GetStatEx(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetStatEx().IsLessThan(Value_StatEx::GetStatEx(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
};

Gurax_EndModuleScope(fs)

#endif
