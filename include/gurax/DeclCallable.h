//==============================================================================
// DeclCallable.h
//==============================================================================
#ifndef GURAX_DECLCALLER_H
#define GURAX_DECLCALLER_H
#include "Attribute.h"
#include "Symbols.h"
#include "DeclArg.h"
#include "DeclBlock.h"

namespace Gurax {

class ExprLink;
class Expr_Block;

//------------------------------------------------------------------------------
// DeclCallable
//------------------------------------------------------------------------------
class DeclCallable : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DeclCallable);
public:
	using Flags = UInt32;
	struct Flag {
		static const Flags None				= 0;
		static const Flags Map				= 1 << 0;	// :map .. must be here
		static const Flags NoMap			= 1 << 1;	// :nomap .. must be here
		static const Flags Closure			= 1 << 2;	// :closure
		static const Flags CutExtraArgs		= 1 << 3;	// :cut_extra_args
		static const Flags DynamicScope		= 1 << 4;	// :dynamic_scope
		static const Flags EndMarker		= 1 << 5;	// :end_marker
		static const Flags Flat				= 1 << 6;	// :flat
		static const Flags Fork				= 1 << 7;	// :fork
		static const Flags Finalizer		= 1 << 8;	// :finalizer
		static const Flags Leader			= 1 << 9;	// :leader
		static const Flags Trailer			= 1 << 10;	// :trailer
		static const Flags SymbolFunc		= 1 << 11;	// :symbol_func
		static const Flags NoNamed			= 1 << 12;	// :nonamed
		static const Flags Public			= 1 << 13;	// :public
		static const Flags Private			= 1 << 14;	// :private
		static const Flags Privileged		= 1 << 15;	// :privileged
		static const Flags Reduce			= 1 << 16;	// :reduce
		static const Flags List				= 1 << 17;	// :list
		static const Flags XList			= 1 << 18;	// :xlist
		static const Flags Iter				= 1 << 19;	// :iter
		static const Flags XIter			= 1 << 20;	// :xiter
		
	};
	class SymbolAssoc_Flag : public SymbolAssoc<Flags, Flag::None> {
	public:
		SymbolAssoc_Flag() {
			Assoc(Gurax_Symbol(map),			Flag::Map);
			Assoc(Gurax_Symbol(nomap),			Flag::NoMap);
			Assoc(Gurax_Symbol(closure),		Flag::Closure);
			Assoc(Gurax_Symbol(cut_extra_args),	Flag::CutExtraArgs);
			Assoc(Gurax_Symbol(dynamic_scope),	Flag::DynamicScope);
			Assoc(Gurax_Symbol(end_marker),		Flag::EndMarker);
			Assoc(Gurax_Symbol(flat),			Flag::Flat);
			Assoc(Gurax_Symbol(fork),			Flag::Fork);
			Assoc(Gurax_Symbol(finalizer),		Flag::Finalizer);
			Assoc(Gurax_Symbol(leader),			Flag::Leader);
			Assoc(Gurax_Symbol(trailer),		Flag::Trailer);
			Assoc(Gurax_Symbol(symbol_func),	Flag::SymbolFunc);
			Assoc(Gurax_Symbol(nonamed),		Flag::NoNamed);
			Assoc(Gurax_Symbol(public_),		Flag::Public);
			Assoc(Gurax_Symbol(private_),		Flag::Private);
			Assoc(Gurax_Symbol(privileged),		Flag::Privileged);
			Assoc(Gurax_Symbol(reduce),			Flag::Reduce);
			Assoc(Gurax_Symbol(list),			Flag::List);
			Assoc(Gurax_Symbol(xlist),			Flag::XList);
			Assoc(Gurax_Symbol(iter),			Flag::Iter);
			Assoc(Gurax_Symbol(xiter),			Flag::XIter);
		}
		static SymbolAssoc* GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? pSymbolAssoc : (pSymbolAssoc = new SymbolAssoc_Flag());
		}
	};
private:
	const VType* _pVTypeResult;
	RefPtr<DottedSymbol> _pDottedSymbol;
	Flags _flags;
	RefPtr<Attribute> _pAttr;
	DeclArgOwner _declArgOwner;
	DeclBlock _declBlock;
	const Symbol* _pSymbolOfDict;
	const Symbol* _pSymbolOfAccessor;
public:
	static const DeclCallable* Empty;
public:
	static void Bootup();
public:
	// Constructor
	DeclCallable();
	// Copy constructor/operator
	DeclCallable(const DeclCallable& src) = delete;
	DeclCallable& operator=(const DeclCallable& src) = delete;
	// Move constructor/operator
	DeclCallable(DeclCallable&& src) = delete;
	DeclCallable& operator=(DeclCallable&& src) noexcept = delete;
protected:
	// Destructor
	~DeclCallable() = default;
public:
	bool Prepare(const ExprLink& exprLinkCdr, const Attribute& attr, const Expr_Block* pExprOfBlock);
	void Clear();
	DeclArgOwner& GetDeclArgOwner() { return _declArgOwner; }
	const DeclArgOwner& GetDeclArgOwner() const { return _declArgOwner; }
	DeclBlock& GetDeclBlock() { return _declBlock; }
	const DeclBlock& GetDeclBlock() const { return _declBlock; }
	void SetVTypeResult(const VType& vtype) { _pVTypeResult = &vtype; }
	const VType& GetVTypeResult() const { return *_pVTypeResult; }
	void SetFlags(Flags flags) { _flags = flags; }
	Flags GetFlags() const { return _flags; }
	Attribute& GetAttr() { return *_pAttr; }
	const Attribute& GetAttr() const { return *_pAttr; }
	bool IsSet(Flags flags) const { return (GetFlags() & flags) != 0; }
	bool IsSet(const Symbol* pSymbol) const { return GetAttr().IsSet(pSymbol); }
	bool IsSetOpt(const Symbol* pSymbol) const { return GetAttr().IsSetOpt(pSymbol); }
	bool CheckAttribute(const Attribute& attr) const;
	static bool CheckFlagConfliction(Flags flags);
	const Symbol* GetSymbolOfDict() const { return _pSymbolOfDict; }
	const Symbol* GetSymbolOfAccessor() const { return _pSymbolOfAccessor; }
	bool IsDeclaredSymbol(const Symbol* pSymbol) {
		return GetDeclArgOwner().FindBySymbol(pSymbol) ||
			GetSymbolOfDict()->IsIdentical(pSymbol) || GetSymbolOfAccessor()->IsIdentical(pSymbol);
	}
	bool IsResultVoid() const { return GetVTypeResult().IsNil(); }
	bool IsResultReduce() const { return IsSet(Flag::Reduce); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DeclCallable& declCaller) const { return this == &declCaller; }
	bool IsEqualTo(const DeclCallable& declCaller) const { return IsIdentical(declCaller); }
	bool IsLessThan(const DeclCallable& declCaller) const { return this < &declCaller; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	static Flags SymbolToFlag(const Symbol* pSymbol) {
		return SymbolAssoc_Flag::GetInstance()->ToAssociated(pSymbol);
	}
	static const Symbol* FlagToSymbol(Flags flag) {
		return SymbolAssoc_Flag::GetInstance()->ToSymbol(flag);
	}
	static Flags SymbolsToFlags(const SymbolList& symbols);
	static String FlagsToString(Flags flags);
};

}

#endif
