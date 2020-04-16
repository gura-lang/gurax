//==============================================================================
// HunkLine.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_HUNKLINE_H
#define GURAX_MODULE_DIFF_HUNKLINE_H
#include <gurax.h>

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
	enum class Format { None, Normal, Context, Unified };
private:
	Format _format;
	size_t _idxSesBegin;
	size_t _idxSesEnd;
	size_t _lineNoOrg;
	size_t _lineNoNew;
	size_t _nLinesOrg;
	size_t _nLinesNew;
public:
	// Constructor
	HunkLine() {}
	// Copy constructor/operator
	HunkLine(const HunkLine& src) = delete;
	HunkLine& operator=(const HunkLine& src) = delete;
	// Move constructor/operator
	HunkLine(HunkLine&& src) noexcept = delete;
	HunkLine& operator=(HunkLine&& src) noexcept = delete;
protected:
	~HunkLine() = default;
public:
	String TextizeRange_Normal() const;
	String TextizeRange_Context() const;
	String TextizeRange_Unified() const;
	bool IsAdd() const { return _nLinesOrg == 0 && _nLinesNew > 0; }
	bool IsDelete() const { return _nLinesOrg > 0 && _nLinesNew == 0; }
	bool IsChange() const { return _nLinesOrg > 0 && _nLinesNew > 0; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const HunkLine& other) const { return this == &other; }
	bool IsEqualTo(const HunkLine& other) const { return IsIdentical(other); }
	bool IsLessThan(const HunkLine& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(diff)

#endif
