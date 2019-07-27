//==============================================================================
// SuffixMgr.h
//==============================================================================
#ifndef GURAX_SUFFIXMGR_H
#define GURAX_SUFFIXMGR_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// SuffixMgr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SuffixMgr : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(SuffixMgr);
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	SuffixMgr(const Symbol* pSymbol) : _pSymbol(pSymbol) {}
	// Copy constructor/operator
	SuffixMgr(const SuffixMgr& src) = delete;
	SuffixMgr& operator=(const SuffixMgr& src) = delete;
	// Move constructor/operator
	SuffixMgr(SuffixMgr&& src) = delete;
	SuffixMgr& operator=(SuffixMgr&& src) noexcept = delete;
protected:
	~SuffixMgr() = default;
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const SuffixMgr& suffixMgr) const { return this == &suffixMgr; }
	bool IsEqualTo(const SuffixMgr& suffixMgr) const { return IsIdentical(suffixMgr); }
	bool IsLessThan(const SuffixMgr& suffixMgr) const { return this < &suffixMgr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// SuffixMgrMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SuffixMgrMap :
	public std::unordered_map<const Symbol*, SuffixMgr*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(SuffixMgrMap);
protected:
	~SuffixMgrMap() { Clear(); }
public:
	void Clear();
	void Assign(SuffixMgr* pSuffixMgr);
	SuffixMgr* Lookup(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
