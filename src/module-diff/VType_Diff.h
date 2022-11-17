//==============================================================================
// VType_Diff.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_VTYPE_DIFF_H
#define GURAX_MODULE_DIFF_VTYPE_DIFF_H
#include <gurax.h>
#include "Diff.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// VType_Diff
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Diff : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Diff VTYPE_Diff;

//------------------------------------------------------------------------------
// Value_Diff
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Diff : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Diff);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Diff");
protected:
	RefPtr<Diff> _pDiff;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Diff() = delete;
	explicit Value_Diff(Diff* pDiff, VType& vtype = VTYPE_Diff) :
		Value_Object(vtype), _pDiff(pDiff) {}
	// Copy constructor/operator
	Value_Diff(const Value_Diff& src) :
		Value_Object(src), _pDiff(src._pDiff->Reference()) {}
	Value_Diff& operator=(const Value_Diff& src) = delete;
	// Move constructor/operator
	Value_Diff(Value_Diff&& src) noexcept = delete;
	Value_Diff& operator=(Value_Diff&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Diff() = default;
public:
	Diff& GetDiff() { return *_pDiff; }
	const Diff& GetDiff() const { return *_pDiff; }
public:
	static Diff& GetDiff(Value& value) {
		return dynamic_cast<Value_Diff&>(value).GetDiff();
	}
	static const Diff& GetDiff(const Value& value) {
		return dynamic_cast<const Value_Diff&>(value).GetDiff();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetDiff().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetDiff().IsEqualTo(Value_Diff::GetDiff(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetDiff().IsLessThan(Value_Diff::GetDiff(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(diff)

#endif
