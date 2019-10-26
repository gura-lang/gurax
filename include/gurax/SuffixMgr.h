//==============================================================================
// SuffixMgr.h
//==============================================================================
#ifndef GURAX_SUFFIXMGR_H
#define GURAX_SUFFIXMGR_H
#include "Referable.h"

//------------------------------------------------------------------------------
// Macros to implement suffix managers
//------------------------------------------------------------------------------
#define Gurax_ImplementSuffixMgr(target, symbol) \
class SuffixMgr_##target##_##symbol : public SuffixMgr { \
public: \
	SuffixMgr_##target##_##symbol() : SuffixMgr(SuffixMgr::Target::target, Symbol::Add(#symbol)) {} \
	virtual Value* Eval(Processor& processor, const char* str) const override; \
}; \
Value* SuffixMgr_##target##_##symbol::Eval(Processor& processor, const char* str) const

#define Gurax_AssignSuffixMgr(target, symbol) \
Basement::Inst.AssignSuffixMgr_##target(new SuffixMgr_##target##_##symbol())

namespace Gurax {

//------------------------------------------------------------------------------
// SuffixMgr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SuffixMgr : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(SuffixMgr);
public:
	enum class Target { Number, String };
private:
	Target _target;
	const Symbol* _pSymbol;
public:
	// Constructor
	SuffixMgr(Target target, const Symbol* pSymbol) : _target(target), _pSymbol(pSymbol) {}
	// Copy constructor/operator
	SuffixMgr(const SuffixMgr& src) = delete;
	SuffixMgr& operator=(const SuffixMgr& src) = delete;
	// Move constructor/operator
	SuffixMgr(SuffixMgr&& src) = delete;
	SuffixMgr& operator=(SuffixMgr&& src) noexcept = delete;
protected:
	virtual ~SuffixMgr() = default;
public:
	Target GetTarget() const { return _target; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	virtual Value* Eval(Processor& processor, const char* str) const = 0;
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
