//==============================================================================
// VType_HunkLine.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_VTYPE_HUNKLINE_H
#define GURAX_MODULE_DIFF_VTYPE_HUNKLINE_H
#include <gurax.h>
#include "DiffLine.h"

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
	RefPtr<DiffLine> _pDiffLine;
	size_t _idxHunk;
public:
	static VType& vtype;
public:
	// Constructor
	Value_HunkLine() = delete;
	explicit Value_HunkLine(DiffLine* pDiffLine, size_t idxHunk, VType& vtype = VTYPE_HunkLine) :
		Value_Object(vtype), _pDiffLine(pDiffLine), _idxHunk(idxHunk) {}
	// Copy constructor/operator
	Value_HunkLine(const Value_HunkLine& src) :
		Value_Object(src), _pDiffLine(src._pDiffLine->Reference()), _idxHunk(src._idxHunk) {}
	Value_HunkLine& operator=(const Value_HunkLine& src) = delete;
	// Move constructor/operator
	Value_HunkLine(Value_HunkLine&& src) noexcept = delete;
	Value_HunkLine& operator=(Value_HunkLine&& src) noexcept = delete;
protected:
	// Destructor
	~Value_HunkLine() = default;
public:
	DiffLine::Hunk& GetHunk() { return _pDiffLine->GetHunk(_idxHunk); }
	const DiffLine::Hunk& GetHunk() const { return _pDiffLine->GetHunk(_idxHunk); }
public:
	static DiffLine::Hunk& GetHunk(Value& value) {
		return dynamic_cast<Value_HunkLine&>(value).GetHunk();
	}
	static const DiffLine::Hunk& GetHunk(const Value& value) {
		return dynamic_cast<const Value_HunkLine&>(value).GetHunk();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
};

Gurax_EndModuleScope(diff)

#endif
