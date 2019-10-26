//==============================================================================
// SuffixMgr.h
//==============================================================================
#ifndef GURAX_SUFFIXMGR_H
#define GURAX_SUFFIXMGR_H
#include "Referable.h"

//------------------------------------------------------------------------------
// Macros to implement suffix managers
//------------------------------------------------------------------------------
#define Gurax_ImplementSuffixMgr_Eval(target, symbol) \
class SuffixMgr_##target##_##symbol : public SuffixMgr { \
public: \
	SuffixMgr_##target##_##symbol() : SuffixMgr(SuffixMgr::Target::target, Symbol::Add(#symbol)) {} \
	virtual Value* Eval(Processor& processor, const char* str) const override; \
}; \
Value* SuffixMgr_##target##_##symbol::Eval(Processor& processor, const char* str) const

#define Gurax_ImplementSuffixMgr_Compose(target, symbol) \
class SuffixMgr_##target##_##symbol : public SuffixMgr { \
public: \
	SuffixMgr_##target##_##symbol() : SuffixMgr(SuffixMgr::Target::target, Symbol::Add(#symbol)) {} \
	virtual void Compose(Composer& composer, const StringReferable& strRef, const Expr* pExpr) const override; \
}; \
void SuffixMgr_##target##_##symbol::Compose(Composer& composer, const StringReferable& strRef, const Expr* pExpr) const

#define Gurax_AssignSuffixMgr(target, symbol) \
Basement::Inst.AssignSuffixMgr(new SuffixMgr_##target##_##symbol())

namespace Gurax {

class Composer;

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
	virtual Value* Eval(Processor& processor, const char* str) const;
	virtual void Compose(Composer& composer, const StringReferable& strRef, const Expr* pExpr) const;
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
class GURAX_DLLDECLARE SuffixMgrMap : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(SuffixMgrMap);
public:
	using Map = std::unordered_map<const Symbol*, SuffixMgr*,
								   Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
private:
	Map _mapForNumber;
	Map _mapForString;
public:
	SuffixMgrMap() {}
protected:
	~SuffixMgrMap() { Clear(); }
public:
	void Clear();
	Map& GetMap(SuffixMgr::Target target) {
		return (target == SuffixMgr::Target::Number)? _mapForNumber : _mapForString;
	}
	const Map& GetMap(SuffixMgr::Target target) const {
		return (target == SuffixMgr::Target::Number)? _mapForNumber : _mapForString;
	}
	void Assign(SuffixMgr* pSuffixMgr);
	SuffixMgr* Lookup(SuffixMgr::Target target, const Symbol* pSymbol) const;
	bool DoesExist(SuffixMgr::Target target, const Symbol* pSymbol) const;
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
