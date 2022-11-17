//==============================================================================
// SuffixMgr.h
//==============================================================================
#ifndef GURAX_SUFFIXMGR_H
#define GURAX_SUFFIXMGR_H
#include "Referable.h"

//------------------------------------------------------------------------------
// Macros to implement suffix managers
//------------------------------------------------------------------------------
#define Gurax_ImplementSuffixMgr_Eval(mode, symbol) \
class SuffixMgr_##mode##_##symbol : public SuffixMgr { \
public: \
	SuffixMgr_##mode##_##symbol() : SuffixMgr(SuffixMgr::Mode::mode, Symbol::Add(#symbol)) {} \
	virtual Value* Eval(Processor& processor, const char* str) const override; \
}; \
Value* SuffixMgr_##mode##_##symbol::Eval(Processor& processor, const char* str) const

#define Gurax_ImplementSuffixMgr_Compose(mode, symbol) \
class SuffixMgr_##mode##_##symbol : public SuffixMgr { \
public: \
	SuffixMgr_##mode##_##symbol() : SuffixMgr(SuffixMgr::Mode::mode, Symbol::Add(#symbol)) {} \
	virtual void Compose(Composer& composer, const StringReferable& strRef, const Expr* pExpr) const override; \
}; \
void SuffixMgr_##mode##_##symbol::Compose(Composer& composer, const StringReferable& strRef, const Expr* pExpr) const

#define Gurax_AssignSuffixMgr(mode, symbol) \
Basement::Inst.AssignSuffixMgr(new SuffixMgr_##mode##_##symbol())

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
	enum class Mode { Number, String, Binary };
private:
	Mode _mode;
	const Symbol* _pSymbol;
public:
	// Constructor
	SuffixMgr(Mode mode, const Symbol* pSymbol) : _mode(mode), _pSymbol(pSymbol) {}
	// Copy constructor/operator
	SuffixMgr(const SuffixMgr& src) = delete;
	SuffixMgr& operator=(const SuffixMgr& src) = delete;
	// Move constructor/operator
	SuffixMgr(SuffixMgr&& src) = delete;
	SuffixMgr& operator=(SuffixMgr&& src) noexcept = delete;
protected:
	virtual ~SuffixMgr() = default;
public:
	Mode GetMode() const { return _mode; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	virtual Value* Eval(Processor& processor, const char* str) const;
	virtual void Compose(Composer& composer, const StringReferable& strRef, const Expr* pExpr) const;
	static const Symbol* ModeToSymbol(Mode mode);
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
	Map _mapForBinary;
public:
	SuffixMgrMap() {}
protected:
	~SuffixMgrMap() { Clear(); }
public:
	void Clear();
	Map& GetMap(SuffixMgr::Mode mode) {
		return
			(mode == SuffixMgr::Mode::Number)? _mapForNumber :
			(mode == SuffixMgr::Mode::String)? _mapForString :
			_mapForBinary;	// mode == SuffixMgr::Mode::Binary
	}
	const Map& GetMap(SuffixMgr::Mode mode) const {
		return const_cast<SuffixMgrMap*>(this)->GetMap(mode);
	}
	void Assign(SuffixMgr* pSuffixMgr);
	SuffixMgr* Lookup(SuffixMgr::Mode mode, const Symbol* pSymbol) const;
	bool DoesExist(SuffixMgr::Mode mode, const Symbol* pSymbol) const;
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
