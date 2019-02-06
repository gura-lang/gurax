//==============================================================================
// DeclArg.h
//==============================================================================
#ifndef GURAX_DECLARG_H
#define GURAX_DECLARG_H
#include "Attribute.h"
#include "Symbols.h"

namespace Gurax {

class Klass;

//------------------------------------------------------------------------------
// DeclArg
//------------------------------------------------------------------------------
class DeclArg : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DeclArg);
public:
	struct Flag {
		static const UInt32 ListVar			= 1 << 0;	// :listvar
		static const UInt32 Map				= 1 << 1;	// :map
		static const UInt32 NoMap			= 1 << 2;	// :nomap
		static const UInt32 NoCast			= 1 << 3;	// :nocast
		static const UInt32 Nil				= 1 << 4;	// :nil
		static const UInt32 Read			= 1 << 5;	// :r
		static const UInt32 Write			= 1 << 6;	// :w
	};
	enum class OccurPattern {
		Invalid,
		Zero,		// (none)
		Once,		// 1
		ZeroOrOnce,	// ?
		ZeroOrMore,	// *
		OnceOrMore,	// +
	};
	class SymbolAssoc_Flag : public SymbolAssoc<UInt32, 0> {
	public:
		SymbolAssoc_Flag() {
			Assoc(Gurax_Symbol(listvar),		Flag::ListVar);
			Assoc(Gurax_Symbol(map),			Flag::Map);
			Assoc(Gurax_Symbol(nomap),			Flag::NoMap);
			Assoc(Gurax_Symbol(nocast),			Flag::NoCast);
			Assoc(Gurax_Symbol(nil),			Flag::Nil);
			Assoc(Gurax_Symbol(r),				Flag::Read);
			Assoc(Gurax_Symbol(w),				Flag::Write);
		}
		static SymbolAssoc* GetInstance() {
			return _pInstance? _pInstance : (_pInstance = new SymbolAssoc_Flag());
		}
	};
private:
	const Symbol* _pSymbol;
	RefPtr<DottedSymbol> _pDottedSymbol;
	const Klass* _pKlass;
	OccurPattern _occurPattern;
	UInt32 _flags;
	RefPtr<Expr> _pExprDefault;	// this may be nullptr
public:
	// Constructor
	DeclArg(const Symbol* pSymbol, DottedSymbol* pDottedSymbol,
			OccurPattern occurPattern, UInt32 flags, Expr* pExprDefault);
	DeclArg(const Symbol* pSymbol, const Klass& klass,
			OccurPattern occurPattern, UInt32 flags, Expr* pExprDefault);
	// Copy constructor/operator
	DeclArg(const DeclArg& src) = delete;
	DeclArg& operator=(const DeclArg& src) = delete;
	// Move constructor/operator
	DeclArg(DeclArg&& src) = delete;
	DeclArg& operator=(DeclArg&& src) noexcept = delete;
protected:
	// Destructor
	~DeclArg() = default;
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const DottedSymbol& GetDottedSymbol() const { return *_pDottedSymbol; }
	const Klass& GetKlass() const { return *_pKlass; }
	void SetKlass(const Klass* pKlass) { _pKlass = pKlass; }
	const char* GetOccurPatternString() const { return OccurPatternToString(_occurPattern); }
	bool IsOccurOnce() const { return _occurPattern == OccurPattern::Once; }
	bool IsOccurZeroOrOnce() const { return _occurPattern == OccurPattern::ZeroOrOnce; }
	bool IsOccurZeroOrMore() const { return _occurPattern == OccurPattern::ZeroOrMore; }
	bool IsOccurOnceOrMore() const { return _occurPattern == OccurPattern::OnceOrMore; }
	UInt32 GetFlags() const { return _flags; }
	const Expr* GetExprDefault() const { return _pExprDefault.get(); }
	static DeclArg* CreateFromExpr(const Expr* pExpr, bool issueErrorFlag);
	static UInt32 SymbolToFlag(const Symbol* pSymbol) {
		return SymbolAssoc_Flag::GetInstance()->ToValue(pSymbol);
	}
	static const Symbol* FlagToSymbol(UInt32 flag) {
		return SymbolAssoc_Flag::GetInstance()->ToSymbol(flag);
	}
	static String FlagsToString(UInt32 flags);
	static const char* OccurPatternToString(OccurPattern occurPattern);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DeclArg& declArg) const { return this == &declArg; }
	bool IsEqualTo(const DeclArg& declArg) const { return IsIdentical(declArg); }
	bool IsLessThan(const DeclArg& declArg) const { return this < &declArg; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// DeclArgList
//------------------------------------------------------------------------------
class DeclArgList : public std::vector<DeclArg*> {
};

//------------------------------------------------------------------------------
// DeclArgOwner
//------------------------------------------------------------------------------
class DeclArgOwner: public DeclArgList {
public:
	~DeclArgOwner() { Clear(); }
	void Clear() {
		for (DeclArg* pDeclArg : *this) DeclArg::Delete(pDeclArg);
		clear();
	}
};

}

#endif
