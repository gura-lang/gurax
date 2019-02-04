//==============================================================================
// Declaration.h
//==============================================================================
#ifndef GURAX_DECLARATION_H
#define GURAX_DECLARATION_H
#include "Attribute.h"
#include "Symbols.h"

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
	struct Flag {
		static const UInt32 None			= 0;
		static const UInt32 Closure			= 1 << 0;	// :closure
		static const UInt32 CutExtraArgs	= 1 << 1;	// :cut_extra_args
		static const UInt32 DynamicScope	= 1 << 2;	// :dynamic_scope
		static const UInt32 EndMarker		= 1 << 3;	// :end_marker
		static const UInt32 Finalizer		= 1 << 4;	// :finalizer
		static const UInt32 Flat			= 1 << 5;	// :flat
		static const UInt32 Fork			= 1 << 6;	// :fork
		static const UInt32 Leader			= 1 << 7;	// :leader
		static const UInt32 ListVar			= 1 << 8;	// :listvar
		static const UInt32 Map				= 1 << 9;	// :map
		static const UInt32 Nil				= 1 << 10;	// :nil
		static const UInt32 NoCast			= 1 << 11;	// :nocast
		static const UInt32 NoMap			= 1 << 12;	// :nomap
		static const UInt32 NoNamed			= 1 << 13;	// :nonamed
		static const UInt32 Private			= 1 << 14;	// :private
		static const UInt32 Privileged		= 1 << 15;	// :privileged
		static const UInt32 Public			= 1 << 16;	// :public
		static const UInt32 Read			= 1 << 17;	// :r
		static const UInt32 SymbolFunc		= 1 << 18;	// :symbol_func
		static const UInt32 Trailer			= 1 << 19;	// :trailer
		static const UInt32 Write			= 1 << 20;	// :w
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
			Assoc(Gurax_Symbol(closure),		Flag::Closure);
			Assoc(Gurax_Symbol(cut_extra_args),	Flag::CutExtraArgs);
			Assoc(Gurax_Symbol(dynamic_scope),	Flag::DynamicScope);
			Assoc(Gurax_Symbol(end_marker),		Flag::EndMarker);
			Assoc(Gurax_Symbol(finalizer),		Flag::Finalizer);
			Assoc(Gurax_Symbol(flat),			Flag::Flat);
			Assoc(Gurax_Symbol(fork),			Flag::Fork);
			Assoc(Gurax_Symbol(leader),			Flag::Leader);
			Assoc(Gurax_Symbol(listvar),		Flag::ListVar);
			Assoc(Gurax_Symbol(map),			Flag::Map);
			Assoc(Gurax_Symbol(nil),			Flag::Nil);
			Assoc(Gurax_Symbol(nocast),			Flag::NoCast);
			Assoc(Gurax_Symbol(nomap),			Flag::NoMap);
			Assoc(Gurax_Symbol(nonamed),		Flag::NoNamed);
			Assoc(Gurax_Symbol(private_),		Flag::Private);
			Assoc(Gurax_Symbol(privileged),		Flag::Privileged);
			Assoc(Gurax_Symbol(public_),		Flag::Public);
			Assoc(Gurax_Symbol(r),				Flag::Read);
			Assoc(Gurax_Symbol(symbol_func),	Flag::SymbolFunc);
			Assoc(Gurax_Symbol(trailer),		Flag::Trailer);
			Assoc(Gurax_Symbol(w),				Flag::Write);
		}
		static SymbolAssoc* GetInstance() {
			return _pInstance? _pInstance : (_pInstance = new SymbolAssoc_Flag());
		}
	};
public:
	class ArgInfo : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(ArgInfo);
	private:
		const Symbol* _pSymbol;
		OccurPattern _occurPattern;
		RefPtr<DottedSymbol> _pDottedSymbol;
		UInt32 _flags;
		RefPtr<Expr> _pExprDefault;	// this may be nullptr
	public:
		// Constructor
		ArgInfo(const Symbol* pSymbol, OccurPattern occurPattern,
				DottedSymbol* pDottedSymbol, UInt32 flags, Expr* pExprDefault) :
			_pSymbol(pSymbol), _occurPattern(occurPattern), _pDottedSymbol(pDottedSymbol),
			_flags(flags), _pExprDefault(pExprDefault) {}
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
		const DottedSymbol* GetDottedSymbol() const { return _pDottedSymbol.get(); }
		bool IsOccurOnce() const { return _occurPattern == OccurPattern::Once; }
		bool IsOccurZeroOrOnce() const { return _occurPattern == OccurPattern::ZeroOrOnce; }
		bool IsOccurZeroOrMore() const { return _occurPattern == OccurPattern::ZeroOrMore; }
		bool IsOccurOnceOrMore() const { return _occurPattern == OccurPattern::OnceOrMore; }
		UInt32 GetFlags() const { return _flags; }
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
	UInt32 _flags;
	RefPtr<Attribute> _pAttr;
public:
	static void Bootup();
public:
	// Constructor
	Declaration() : _validFlag(false), _flags(0) {}
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
	static UInt32 SymbolToFlag(const Symbol* pSymbol) {
		return SymbolAssoc_Flag::GetInstance()->ToValue(pSymbol);
	}
	static const Symbol* FlagToSymbol(UInt32 flag) {
		return SymbolAssoc_Flag::GetInstance()->ToSymbol(flag);
	}
	static String FlagsToString(UInt32 flags);
	static const char* OccurPatternToString(OccurPattern occurPattern);
};

}

#endif
