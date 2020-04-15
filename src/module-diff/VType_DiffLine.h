//==============================================================================
// VType_DiffLine.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_VTYPE_DIFFLINE_H
#define GURAX_MODULE_DIFF_VTYPE_DIFFLINE_H
#include <gurax.h>
#include "DiffLine.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// VType_DiffLine
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_DiffLine : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_DiffLine VTYPE_DiffLine;

//------------------------------------------------------------------------------
// Value_DiffLine
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_DiffLine : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_DiffLine);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_DiffLine");
protected:
	RefPtr<DiffLine> _pDiffLine;
public:
	static VType& vtype;
public:
	// Constructor
	Value_DiffLine() = delete;
	explicit Value_DiffLine(DiffLine* pDiffLine, VType& vtype = VTYPE_DiffLine) :
		Value_Object(vtype), _pDiffLine(pDiffLine) {}
	// Copy constructor/operator
	Value_DiffLine(const Value_DiffLine& src) :
		Value_Object(src), _pDiffLine(src._pDiffLine->Reference()) {}
	Value_DiffLine& operator=(const Value_DiffLine& src) = delete;
	// Move constructor/operator
	Value_DiffLine(Value_DiffLine&& src) noexcept = delete;
	Value_DiffLine& operator=(Value_DiffLine&& src) noexcept = delete;
protected:
	// Destructor
	~Value_DiffLine() = default;
public:
	DiffLine& GetDiffLine() { return *_pDiffLine; }
	const DiffLine& GetDiffLine() const { return *_pDiffLine; }
public:
	static DiffLine& GetDiffLine(Value& value) {
		return dynamic_cast<Value_DiffLine&>(value).GetDiffLine();
	}
	static const DiffLine& GetDiffLine(const Value& value) {
		return dynamic_cast<const Value_DiffLine&>(value).GetDiffLine();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetDiffLine().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetDiffLine().IsEqualTo(Value_DiffLine::GetDiffLine(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetDiffLine().IsLessThan(Value_DiffLine::GetDiffLine(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetDiffLine().ToString(ss);
	}
};

Gurax_EndModuleScope(diff)

#endif
