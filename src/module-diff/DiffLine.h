//==============================================================================
// DiffLine.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_DIFFLINE_H
#define GURAX_MODULE_DIFF_DIFFLINE_H
#include <gurax.h>
#include <dtl/dtl.hpp>

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// DiffLine
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DiffLine : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DiffLine);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("diff.DiffLine");
public:
	class Comparator {
	private:
		bool _icaseFlag;
	public:
		void SetICaseFlag(bool icaseFlag) { _icaseFlag = icaseFlag; }
		int impl(const String& str1, const String& str2) const {
			return _icaseFlag? str1.IsEqualToICase(str2) : str1.IsEqualTo(str2);
		}
	};
	using Sequence = std::vector<String>;
	using Lcs = dtl::Lcs<String>;	// Longest Common Subsequence
	using Ses = dtl::Ses<String>;	// Shortest Edit Script
	using Diff = dtl::Diff<String, Sequence, Comparator>;
private:
	Diff _diff;
public:
	// Constructor
	DiffLine(bool icaseFlag) { _diff.cmp.SetICaseFlag(icaseFlag); }
	// Copy constructor/operator
	DiffLine(const DiffLine& src) = delete;
	DiffLine& operator=(const DiffLine& src) = delete;
	// Move constructor/operator
	DiffLine(DiffLine&& src) noexcept = delete;
	DiffLine& operator=(DiffLine&& src) noexcept = delete;
protected:
	~DiffLine() = default;
public:
	Lcs& GetLcs() { return _diff.lcs; }
	Ses& GetSes() { return _diff.ses; }
	bool Compose(const Value& value1, const Value& value2);
public:
	static bool FeedSequence(Sequence& seq, const Value& value);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DiffLine& other) const { return this == &other; }
	bool IsEqualTo(const DiffLine& other) const { return IsIdentical(other); }
	bool IsLessThan(const DiffLine& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(diff)

#endif
