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
	size_t _iHunk;
public:
	static VType& vtype;
public:
	// Constructor
	Value_HunkLine() = delete;
	explicit Value_HunkLine(DiffLine* pDiffLine, size_t iHunk, VType& vtype = VTYPE_HunkLine) :
		Value_Object(vtype), _pDiffLine(pDiffLine), _iHunk(iHunk) {}
	// Copy constructor/operator
	Value_HunkLine(const Value_HunkLine& src) :
		Value_Object(src), _pDiffLine(src._pDiffLine->Reference()), _iHunk(src._iHunk) {}
	Value_HunkLine& operator=(const Value_HunkLine& src) = delete;
	// Move constructor/operator
	Value_HunkLine(Value_HunkLine&& src) noexcept = delete;
	Value_HunkLine& operator=(Value_HunkLine&& src) noexcept = delete;
protected:
	// Destructor
	~Value_HunkLine() = default;
public:
	DiffLine::Hunk& GetHunk() { return _pDiffLine->GetHunk(_iHunk); }
	const DiffLine::Hunk& GetHunk() const { return _pDiffLine->GetHunk(_iHunk); }
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

//-----------------------------------------------------------------------------
// Iterator_HunkLine
//-----------------------------------------------------------------------------
class Iterator_HunkLine : public Iterator {
private:
	RefPtr<DiffLine> _pDiffLine;
	size_t _iHunk;
public:
	Iterator_HunkLine(DiffLine* pDiffLine);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenDetermined;
	}
	virtual size_t GetLength() const override { return _pDiffLine->GetHunkVec().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(diff)

#endif
