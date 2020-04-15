//==============================================================================
// VType_EditLine.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_VTYPE_EDITLINE_H
#define GURAX_MODULE_DIFF_VTYPE_EDITLINE_H
#include <gurax.h>
#include "EditLine.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// VType_EditLine
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_EditLine : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_EditLine VTYPE_EditLine;

//------------------------------------------------------------------------------
// Value_EditLine
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_EditLine : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_EditLine);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_EditLine");
protected:
	RefPtr<EditLine> _pEditLine;
public:
	static VType& vtype;
public:
	// Constructor
	Value_EditLine() = delete;
	explicit Value_EditLine(EditLine* pEditLine, VType& vtype = VTYPE_EditLine) :
		Value_Object(vtype), _pEditLine(pEditLine) {}
	// Copy constructor/operator
	Value_EditLine(const Value_EditLine& src) :
		Value_Object(src), _pEditLine(src._pEditLine->Reference()) {}
	Value_EditLine& operator=(const Value_EditLine& src) = delete;
	// Move constructor/operator
	Value_EditLine(Value_EditLine&& src) noexcept = delete;
	Value_EditLine& operator=(Value_EditLine&& src) noexcept = delete;
protected:
	// Destructor
	~Value_EditLine() = default;
public:
	EditLine& GetEditLine() { return *_pEditLine; }
	const EditLine& GetEditLine() const { return *_pEditLine; }
public:
	static EditLine& GetEditLine(Value& value) {
		return dynamic_cast<Value_EditLine&>(value).GetEditLine();
	}
	static const EditLine& GetEditLine(const Value& value) {
		return dynamic_cast<const Value_EditLine&>(value).GetEditLine();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetEditLine().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetEditLine().IsEqualTo(Value_EditLine::GetEditLine(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetEditLine().IsLessThan(Value_EditLine::GetEditLine(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetEditLine().ToString(ss);
	}
};

Gurax_EndModuleScope(diff)

#endif
