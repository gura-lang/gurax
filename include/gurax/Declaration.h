//==============================================================================
// Declaration.h
//==============================================================================
#ifndef GURAX_DECLARATION_H
#define GURAX_DECLARATION_H
#include "Attribute.h"
#include "Symbols.h"
#include "Object_undefined.h"

namespace Gurax {

class ExprLink;
class Expr_Caller;

//------------------------------------------------------------------------------
// Declaration
//------------------------------------------------------------------------------
class Declaration : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Declaration);
public:
	struct FlagArg {
		static const UInt32 ListVar			= 1 << 0;	// :listvar
		static const UInt32 Map				= 1 << 1;	// :map
		static const UInt32 NoMap			= 1 << 2;	// :nomap
		static const UInt32 NoCast			= 1 << 3;	// :nocast
		static const UInt32 Nil				= 1 << 4;	// :nil
		static const UInt32 Read			= 1 << 5;	// :r
		static const UInt32 Write			= 1 << 6;	// :w
	};
	struct FlagFunc {
		static const UInt32 Map				= 1 << 0;	// :map
		static const UInt32 NoMap			= 1 << 1;	// :nomap
		static const UInt32 Closure			= 1 << 2;	// :closure
		static const UInt32 CutExtraArgs	= 1 << 3;	// :cut_extra_args
		static const UInt32 DynamicScope	= 1 << 4;	// :dynamic_scope
		static const UInt32 EndMarker		= 1 << 5;	// :end_marker
		static const UInt32 Flat			= 1 << 6;	// :flat
		static const UInt32 Fork			= 1 << 7;	// :fork
		static const UInt32 Finalizer		= 1 << 8;	// :finalizer
		static const UInt32 Leader			= 1 << 9;	// :leader
		static const UInt32 Trailer			= 1 << 10;	// :trailer
		static const UInt32 SymbolFunc		= 1 << 11;	// :symbol_func
		static const UInt32 NoNamed			= 1 << 12;	// :nonamed
		static const UInt32 Public			= 1 << 13;	// :public
		static const UInt32 Private			= 1 << 14;	// :private
		static const UInt32 Privileged		= 1 << 15;	// :privileged
	};
	enum class OccurPattern {
		Invalid,
		Zero,		// (none)
		Once,		// 1
		ZeroOrOnce,	// ?
		ZeroOrMore,	// *
		OnceOrMore,	// +
	};
	class SymbolAssoc_FlagArg : public SymbolAssoc<UInt32, 0> {
	public:
		SymbolAssoc_FlagArg() {
			Assoc(Gurax_Symbol(listvar),		FlagArg::ListVar);
			Assoc(Gurax_Symbol(map),			FlagArg::Map);
			Assoc(Gurax_Symbol(nomap),			FlagArg::NoMap);
			Assoc(Gurax_Symbol(nocast),			FlagArg::NoCast);
			Assoc(Gurax_Symbol(nil),			FlagArg::Nil);
			Assoc(Gurax_Symbol(r),				FlagArg::Read);
			Assoc(Gurax_Symbol(w),				FlagArg::Write);
		}
		static SymbolAssoc* GetInstance() {
			return _pInstance? _pInstance : (_pInstance = new SymbolAssoc_FlagArg());
		}
	};
	class SymbolAssoc_FlagFunc : public SymbolAssoc<UInt32, 0> {
	public:
		SymbolAssoc_FlagFunc() {
			Assoc(Gurax_Symbol(map),			FlagFunc::Map);
			Assoc(Gurax_Symbol(nomap),			FlagFunc::NoMap);
			Assoc(Gurax_Symbol(closure),		FlagFunc::Closure);
			Assoc(Gurax_Symbol(cut_extra_args),	FlagFunc::CutExtraArgs);
			Assoc(Gurax_Symbol(dynamic_scope),	FlagFunc::DynamicScope);
			Assoc(Gurax_Symbol(end_marker),		FlagFunc::EndMarker);
			Assoc(Gurax_Symbol(flat),			FlagFunc::Flat);
			Assoc(Gurax_Symbol(fork),			FlagFunc::Fork);
			Assoc(Gurax_Symbol(finalizer),		FlagFunc::Finalizer);
			Assoc(Gurax_Symbol(leader),			FlagFunc::Leader);
			Assoc(Gurax_Symbol(trailer),		FlagFunc::Trailer);
			Assoc(Gurax_Symbol(symbol_func),	FlagFunc::SymbolFunc);
			Assoc(Gurax_Symbol(nonamed),		FlagFunc::NoNamed);
			Assoc(Gurax_Symbol(public_),		FlagFunc::Public);
			Assoc(Gurax_Symbol(private_),		FlagFunc::Private);
			Assoc(Gurax_Symbol(privileged),		FlagFunc::Privileged);
		}
		static SymbolAssoc* GetInstance() {
			return _pInstance? _pInstance : (_pInstance = new SymbolAssoc_FlagFunc());
		}
	};
public:
	class ArgInfo : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(ArgInfo);
	private:
		const Symbol* _pSymbol;
		RefPtr<DottedSymbol> _pDottedSymbol;
		const Klass* _pKlass;
		OccurPattern _occurPattern;
		UInt32 _flagsArg;
		RefPtr<Expr> _pExprDefault;	// this may be nullptr
	public:
		// Constructor
		ArgInfo(const Symbol* pSymbol, DottedSymbol* pDottedSymbol,
				OccurPattern occurPattern, UInt32 flagsArg, Expr* pExprDefault) :
			_pSymbol(pSymbol), _pDottedSymbol(pDottedSymbol), _pKlass(&Object_undefined::klass),
			_occurPattern(occurPattern), _flagsArg(flagsArg), _pExprDefault(pExprDefault) {}
		ArgInfo(const Symbol* pSymbol, const Klass& klass,
				OccurPattern occurPattern, UInt32 flagsArg, Expr* pExprDefault) :
			_pSymbol(pSymbol), _pDottedSymbol(klass.MakeDottedSymbol()), _pKlass(&klass),
			_occurPattern(occurPattern), _flagsArg(flagsArg), _pExprDefault(pExprDefault) {}
		// Copy constructor/operator
		ArgInfo(const ArgInfo& src) = delete;
		ArgInfo& operator=(const ArgInfo& src) = delete;
		// Move constructor/operator
		ArgInfo(ArgInfo&& src) = delete;
		ArgInfo& operator=(ArgInfo&& src) noexcept = delete;
	protected:
		// Destructor
		~ArgInfo() = default;
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
		UInt32 GetFlagsArg() const { return _flagsArg; }
		const Expr* GetExprDefault() const { return _pExprDefault.get(); }
	public:
		size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
		bool IsIdentical(const ArgInfo& argInfo) const { return this == &argInfo; }
		bool IsEqualTo(const ArgInfo& argInfo) const { return IsIdentical(argInfo); }
		bool IsLessThan(const ArgInfo& argInfo) const { return this < &argInfo; }
		String ToString(const StringStyle& ss = StringStyle::Empty) const;
	};
	class ArgInfoList : public std::vector<ArgInfo*> {
	};
	class ArgInfoOwner: public ArgInfoList {
	public:
		~ArgInfoOwner() { Clear(); }
		void Clear() {
			for (ArgInfo* pArgInfo : *this) ArgInfo::Delete(pArgInfo);
			clear();
		}
	};
private:
	bool _validFlag;
	ArgInfoOwner _argInfoOwner;
	UInt32 _flagsFunc;
	RefPtr<Attribute> _pAttr;
public:
	static void Bootup();
public:
	// Constructor
	Declaration() : _validFlag(false), _flagsFunc(0), _pAttr(new Attribute()) {}
	// Copy constructor/operator
	Declaration(const Declaration& src) = delete;
	Declaration& operator=(const Declaration& src) = delete;
	// Move constructor/operator
	Declaration(Declaration&& src) = delete;
	Declaration& operator=(Declaration&& src) noexcept = delete;
protected:
	// Destructor
	~Declaration() = default;
public:
	bool Prepare(const ExprLink& exprLinkCdr, const Attribute& attr, bool issueErrorFlag);
	void Clear();
	static ArgInfo* CreateArgInfo(const Expr* pExpr, bool issueErrorFlag);
	bool IsValid() const { return _validFlag; }
	const ArgInfoOwner& GetArgInfoOwner() const { return _argInfoOwner; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Declaration& declaration) const { return this == &declaration; }
	bool IsEqualTo(const Declaration& declaration) const { return IsIdentical(declaration); }
	bool IsLessThan(const Declaration& declaration) const { return this < &declaration; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	static UInt32 SymbolToFlagArg(const Symbol* pSymbol) {
		return SymbolAssoc_FlagArg::GetInstance()->ToValue(pSymbol);
	}
	static UInt32 SymbolToFlagFunc(const Symbol* pSymbol) {
		return SymbolAssoc_FlagFunc::GetInstance()->ToValue(pSymbol);
	}
	static const Symbol* FlagArgToSymbol(UInt32 flagArg) {
		return SymbolAssoc_FlagArg::GetInstance()->ToSymbol(flagArg);
	}
	static const Symbol* FlagFuncToSymbol(UInt32 flagFunc) {
		return SymbolAssoc_FlagFunc::GetInstance()->ToSymbol(flagFunc);
	}
	static String FlagsArgToString(UInt32 flags);
	static String FlagsFuncToString(UInt32 flags);
	static const char* OccurPatternToString(OccurPattern occurPattern);
};

}

#endif
