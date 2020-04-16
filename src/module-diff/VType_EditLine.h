//==============================================================================
// VType_EditLine.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_VTYPE_EDITLINE_H
#define GURAX_MODULE_DIFF_VTYPE_EDITLINE_H
#include <gurax.h>
#include "DiffLine.h"

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
	RefPtr<DiffLine> _pDiffLine;
	const DiffLine::SesElem& _sesElem;
public:
	static VType& vtype;
public:
	// Constructor
	Value_EditLine() = delete;
	explicit Value_EditLine(DiffLine* pDiffLine, const DiffLine::SesElem& sesElem, VType& vtype = VTYPE_EditLine) :
		Value_Object(vtype), _pDiffLine(pDiffLine), _sesElem(sesElem) {}
	// Copy constructor/operator
	Value_EditLine(const Value_EditLine& src) :
		Value_Object(src), _pDiffLine(src._pDiffLine->Reference()), _sesElem(src._sesElem) {}
	Value_EditLine& operator=(const Value_EditLine& src) = delete;
	// Move constructor/operator
	Value_EditLine(Value_EditLine&& src) noexcept = delete;
	Value_EditLine& operator=(Value_EditLine&& src) noexcept = delete;
protected:
	// Destructor
	~Value_EditLine() = default;
public:
	const DiffLine::SesElem& GetSesElem() const { return _sesElem; }
public:
	static const DiffLine::SesElem& GetSesElem(const Value& value) {
		return dynamic_cast<const Value_EditLine&>(value).GetSesElem();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
};

Gurax_EndModuleScope(diff)

#endif
