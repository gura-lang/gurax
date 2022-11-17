//==============================================================================
// Hunk.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_Hunk_H
#define GURAX_MODULE_DIFF_Hunk_H
#include <gurax.h>
#include "VTYPE_Edit.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// Hunk
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Hunk : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Hunk);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("diff.Hunk");
public:
	class GURAX_DLLDECLARE Picker {
	private:
		RefPtr<Diff> _pDiff;
		size_t _nLinesCommon;
		size_t _iSesElem;
	public:
		Picker(Diff* pDiff, size_t nLinesCommon);
		Hunk* NextHunk();
	};
protected:
	RefPtr<Diff> _pDiff;
	size_t _iSesElemBegin;
	size_t _iSesElemEnd;
	size_t _lineNoOrg;
	size_t _lineNoNew;
	size_t _nLinesOrg;
	size_t _nLinesNew;
public:
	// Constructor
	Hunk(Diff* pDiff, size_t iSesElemBegin, size_t iSesElemEnd,
		size_t lineNoOrg, size_t lineNoNew, size_t nLinesOrg, size_t nLinesNew);
	// Copy constructor/operator
	Hunk(const Hunk& src) = delete;
	Hunk& operator=(const Hunk& src) = delete;
	// Move constructor/operator
	Hunk(Hunk&& src) noexcept = delete;
	Hunk& operator=(Hunk&& src) noexcept = delete;
protected:
	~Hunk() = default;
public:
	Iterator* EachEdit() const {
		return new Iterator_Edit(_pDiff->Reference(), _iSesElemBegin, _iSesElemEnd);
	}
	size_t GetLineNoOrg() const { return _lineNoOrg; }
	size_t GetLineNoNew() const { return _lineNoNew; }
	size_t GetNLinesOrg() const { return _nLinesOrg; }
	size_t GetNLinesNew() const { return _nLinesNew; }
	String MakeRangeString() const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Hunk& other) const { return this == &other; }
	bool IsEqualTo(const Hunk& other) const { return IsIdentical(other); }
	bool IsLessThan(const Hunk& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(diff)

#endif
