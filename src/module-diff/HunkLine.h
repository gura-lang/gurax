//==============================================================================
// HunkLine.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_HUNKLINE_H
#define GURAX_MODULE_DIFF_HUNKLINE_H
#include <gurax.h>
#include "VTYPE_EditLine.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// HunkLine
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE HunkLine : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(HunkLine);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("diff.HunkLine");
public:
	class GURAX_DLLDECLARE Picker {
	private:
		RefPtr<DiffLine> _pDiffLine;
		size_t _nLinesCommon;
		size_t _iSesElem;
	public:
		Picker(DiffLine* pDiffLine, size_t nLinesCommon);
		HunkLine* NextHunkLine();
	};
protected:
	RefPtr<DiffLine> _pDiffLine;
	size_t _iSesElemBegin;
	size_t _iSesElemEnd;
	size_t _lineNoOrg;
	size_t _lineNoNew;
	size_t _nLinesOrg;
	size_t _nLinesNew;
public:
	// Constructor
	HunkLine(DiffLine* pDiffLine, size_t iSesElemBegin, size_t iSesElemEnd,
		size_t lineNoOrg, size_t lineNoNew, size_t nLinesOrg, size_t nLinesNew);
	// Copy constructor/operator
	HunkLine(const HunkLine& src) = delete;
	HunkLine& operator=(const HunkLine& src) = delete;
	// Move constructor/operator
	HunkLine(HunkLine&& src) noexcept = delete;
	HunkLine& operator=(HunkLine&& src) noexcept = delete;
protected:
	~HunkLine() = default;
public:
	Iterator* EachEditLine() const {
		return new Iterator_EditLine(_pDiffLine->Reference(), _iSesElemBegin, _iSesElemEnd);
	}
	size_t GetLineNoOrg() const { return _lineNoOrg; }
	size_t GetLineNoNew() const { return _lineNoNew; }
	size_t GetNLinesOrg() const { return _nLinesOrg; }
	size_t GetNLinesNew() const { return _nLinesNew; }
	String MakeRangeString() const;
	void Print(Stream& stream) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const HunkLine& other) const { return this == &other; }
	bool IsEqualTo(const HunkLine& other) const { return IsIdentical(other); }
	bool IsLessThan(const HunkLine& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(diff)

#endif
