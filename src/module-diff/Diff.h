//==============================================================================
// Diff.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_DIFF_H
#define GURAX_MODULE_DIFF_DIFF_H
#include <gurax.h>
#include <dtl/dtl.hpp>

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// Diff
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Diff : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Diff);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("diff.Diff");
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
	using Context = dtl::Diff<String, Sequence, Comparator>;
	using Lcs = dtl::Lcs<String>;	// Longest Common Subsequence
	using Ses = dtl::Ses<String>;	// Shortest Edit Script
	using SesElem = Ses::sesElem;
	using LcsElemVec = Lcs::elemVec;
	using SesElemVec = Ses::sesElemVec;
private:
	Context _context;
public:
	// Constructor
	Diff(bool icaseFlag) { _context.cmp.SetICaseFlag(icaseFlag); }
	// Copy constructor/operator
	Diff(const Diff& src) = delete;
	Diff& operator=(const Diff& src) = delete;
	// Move constructor/operator
	Diff(Diff&& src) noexcept = delete;
	Diff& operator=(Diff&& src) noexcept = delete;
protected:
	~Diff() = default;
public:
	Int64 GetDistance() const { return _context.editDistance; }
	Lcs& GetLcs() { return _context.lcs; }
	Ses& GetSes() { return _context.ses; }
	LcsElemVec& GetLcsElems() { return GetLcs().sequence; }
	SesElemVec& GetSesElems() { return GetSes().sequence; }
	bool Compose(Value& value1, Value& value2);
public:
	static bool FeedValue(Sequence& seq, Value& value);
	static void FeedString(Sequence& seq, const char* src);
	static bool FeedStream(Sequence& seq, Stream& src);
	static bool FeedIterator(Sequence& seq, Iterator& iter);
	static void FeedList(Sequence& seq, const ValueList& valList);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Diff& other) const { return this == &other; }
	bool IsEqualTo(const Diff& other) const { return IsIdentical(other); }
	bool IsLessThan(const Diff& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(diff)

#endif
