//==============================================================================
// VType_HunkLine.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_VTYPE_HUNKLINE_H
#define GURAX_MODULE_DIFF_VTYPE_HUNKLINE_H
#include <gurax.h>
#include "HunkLine.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// VType_HunkLine
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_HunkLine : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_HunkLine VTYPE_HunkLine;

//------------------------------------------------------------------------------
// Value_HunkLine
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_HunkLine : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_HunkLine);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_HunkLine");
protected:
	RefPtr<HunkLine> _pHunkLine;
public:
	static VType& vtype;
public:
	// Constructor
	Value_HunkLine() = delete;
	explicit Value_HunkLine(HunkLine* pHunkLine, VType& vtype = VTYPE_HunkLine) :
		Value_Object(vtype), _pHunkLine(pHunkLine) {}
	// Copy constructor/operator
	Value_HunkLine(const Value_HunkLine& src) :
		Value_Object(src), _pHunkLine(src._pHunkLine->Reference()) {}
	Value_HunkLine& operator=(const Value_HunkLine& src) = delete;
	// Move constructor/operator
	Value_HunkLine(Value_HunkLine&& src) noexcept = delete;
	Value_HunkLine& operator=(Value_HunkLine&& src) noexcept = delete;
protected:
	// Destructor
	~Value_HunkLine() = default;
public:
	HunkLine& GetHunkLine() { return *_pHunkLine; }
	const HunkLine& GetHunkLine() const { return *_pHunkLine; }
public:
	static HunkLine& GetHunkLine(Value& value) {
		return dynamic_cast<Value_HunkLine&>(value).GetHunkLine();
	}
	static const HunkLine& GetHunkLine(const Value& value) {
		return dynamic_cast<const Value_HunkLine&>(value).GetHunkLine();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetHunkLine().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetHunkLine().IsEqualTo(Value_HunkLine::GetHunkLine(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetHunkLine().IsLessThan(Value_HunkLine::GetHunkLine(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetHunkLine().ToString(ss);
	}
};

Gurax_EndModuleScope(diff)

#endif
