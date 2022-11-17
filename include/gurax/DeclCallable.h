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
class GURAX_DLLDECLARE DeclCallable : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DeclCallable);
public:
	enum class Type { Statement, Function, Constructor, Method };
	using Flags = UInt32;
	struct GURAX_DLLDECLARE Flag {
		static const Flags None				= 0;
		static const Flags Map				= 1 << 0;	// :map .. must be here
		static const Flags NoMap			= 1 << 1;	// :noMap .. must be here
		static const Flags OfClass			= 1 << 2;	// :static
		static const Flags OfInstance		= 1 << 3;	// :instance
		static const Flags Closure			= 1 << 4;	// :closure
		static const Flags CutExtraArgs		= 1 << 5;	// :cutExtraArgs
		static const Flags DynamicScope		= 1 << 6;	// :dynamicScope
		static const Flags EndMarker		= 1 << 7;	// :endMarker
		static const Flags Flat				= 1 << 8;	// :flat
		static const Flags Fork				= 1 << 9;	// :fork
		static const Flags Finalizer		= 1 << 10;	// :finalizer
		static const Flags Leader			= 1 << 11;	// :leader
		static const Flags Trailer			= 1 << 12;	// :trailer
		static const Flags SymbolFunc		= 1 << 13;	// :symbolFunc
		static const Flags NoNamed			= 1 << 14;	// :noNamed
		static const Flags Public			= 1 << 15;	// :public
		static const Flags Private			= 1 << 16;	// :private
		static const Flags Privileged		= 1 << 17;	// :privileged
		static const Flags Reduce			= 1 << 18;	// :reduce
		static const Flags List				= 1 << 19;	// :list
		static const Flags XList			= 1 << 20;	// :xlist
		static const Flags Iter				= 1 << 21;	// :iter
		static const Flags XIter			= 1 << 22;	// :xiter
		static const Flags AnyAttr			= 1 << 23;	// :anyAttr
	};
	class GURAX_DLLDECLARE SymbolAssoc_Flag : public SymbolAssoc<Flags, Flag::None> {
	public:
		SymbolAssoc_Flag() {
			Assoc(Gurax_Symbol(map),			Flag::Map);
			Assoc(Gurax_Symbol(noMap),			Flag::NoMap);
			Assoc(Gurax_Symbol(static_),		Flag::OfClass);
			//Assoc(Gurax_Symbol(instance),		Flag::OfInstance);
			Assoc(Gurax_Symbol(closure),		Flag::Closure);
			Assoc(Gurax_Symbol(cutExtraArgs),	Flag::CutExtraArgs);
			Assoc(Gurax_Symbol(dynamicScope),	Flag::DynamicScope);
			Assoc(Gurax_Symbol(endMarker),		Flag::EndMarker);
			Assoc(Gurax_Symbol(flat),			Flag::Flat);
			Assoc(Gurax_Symbol(fork),			Flag::Fork);
			Assoc(Gurax_Symbol(finalizer),		Flag::Finalizer);
			Assoc(Gurax_Symbol(leader),			Flag::Leader);
			Assoc(Gurax_Symbol(trailer),		Flag::Trailer);
			Assoc(Gurax_Symbol(symbolFunc),	Flag::SymbolFunc);
			Assoc(Gurax_Symbol(noNamed),		Flag::NoNamed);
			Assoc(Gurax_Symbol(public_),		Flag::Public);
			Assoc(Gurax_Symbol(private_),		Flag::Private);
			Assoc(Gurax_Symbol(privileged),		Flag::Privileged);
			Assoc(Gurax_Symbol(reduce),			Flag::Reduce);
			Assoc(Gurax_Symbol(list),			Flag::List);
			Assoc(Gurax_Symbol(xlist),			Flag::XList);
			Assoc(Gurax_Symbol(iter),			Flag::Iter);
			Assoc(Gurax_Symbol(xiter),			Flag::XIter);
			Assoc(Gurax_Symbol(anyAttr),		Flag::AnyAttr);
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_Flag());
		}
	};
private:
	VType* _pVTypeResult;
	RefPtr<DottedSymbol> _pDottedSymbol;
	Flags _flags;
	RefPtr<Attribute> _pAttr;
	RefPtr<DeclArgOwner> _pDeclArgOwner;
	DeclBlock _declBlock;
	const Symbol* _pSymbolOfDict;
	const Symbol* _pSymbolOfAccessor;
public:
	static RefPtr<DeclCallable> Empty;
	static RefPtr<DeclCallable> EmptyWithBlock;
	static RefPtr<DeclCallable> EmptyWithOptionalBlock;
	static RefPtr<DeclCallable> Wildcard;
	static RefPtr<DeclCallable> Unary;
	static RefPtr<DeclCallable> UnaryPost;
	static RefPtr<DeclCallable> Binary;
	static RefPtr<DeclCallable> Binary_NoMap;
	static RefPtr<DeclCallable> MathUnary;
	static RefPtr<DeclCallable> MathBinary;
public:
	static void Bootup();
public:
	// Constructor
	DeclCallable(Flags flags);
	DeclCallable() : DeclCallable(Flag::None) {}
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
	bool IsNaked() const;
	bool Prepare(const ExprLink& exprLinkParam, const Attribute& attr, const Expr_Block* pExprOfBlock);
	void Clear();
	DeclArgOwner& GetDeclArgOwner() { return *_pDeclArgOwner; }
	const DeclArgOwner& GetDeclArgOwner() const { return *_pDeclArgOwner; }
	DeclBlock& GetDeclBlock() { return _declBlock; }
	const DeclBlock& GetDeclBlock() const { return _declBlock; }
	void SetDottedSymbol(DottedSymbol* pDottedSymbol) { _pDottedSymbol.reset(pDottedSymbol); }
	const DottedSymbol& GetDottedSymbol() const { return *_pDottedSymbol; }
	void SetVTypeResult(VType& vtype) { _pVTypeResult = &vtype; }
	VType& GetVTypeResult() { return *_pVTypeResult; }
	const VType& GetVTypeResult() const { return *_pVTypeResult; }
	void SetFlags(Flags flags) { _flags = flags; }
	Flags GetFlags() const { return _flags; }
	void OrFlags(Flags flags) { _flags |= flags; }
public:
	void Declare(VType& vtype, Flags flags) { _pVTypeResult = &vtype; _flags |= flags; }
	void DeclareArg(const Symbol* pSymbol, const VType& vtype,
					const DeclArg::Occur& occur = DeclArg::Occur::Once,
					DeclArg::Flags flags = DeclArg::Flag::None, Expr* pExprDefault = nullptr) {
		GetDeclArgOwner().push_back(new DeclArg(pSymbol, vtype, occur, flags, pExprDefault));
	}
	void DeclareArg(const char* name, const VType& vtype,
					const DeclArg::Occur& occur = DeclArg::Occur::Once,
					DeclArg::Flags flags = DeclArg::Flag::None, Expr* pExprDefault = nullptr) {
		DeclareArg(Symbol::Add(name), vtype, occur, flags, pExprDefault);
	}
	void DeclareAttrOpt(const Symbol* pSymbol) {
		GetAttr().AddSymbolOpt(pSymbol);
	}
	void DeclareAttrOpt(const char* name) {
		DeclareAttrOpt(Symbol::Add(name));
	}
	void DeclareBlock(const Symbol* pSymbol, const DeclBlock::Occur& occur,
					  DeclBlock::Flags flags = DeclBlock::Flag::None) {
		GetDeclBlock().SetSymbol(pSymbol).SetOccur(occur).SetFlags(flags);
	}
	void DeclareBlock(const char* name, const DeclBlock::Occur& occur,
					  DeclBlock::Flags flags = DeclBlock::Flag::None) {
		DeclareBlock(Symbol::Add(name), occur, flags);
	}
	void DeclareBlock(const DeclBlock::Occur& occur, DeclBlock::Flags flags = DeclBlock::Flag::None) {
		DeclareBlock(Gurax_Symbol(block), occur, flags);
	}
public:
	Attribute& GetAttr() { return *_pAttr; }
	const Attribute& GetAttr() const { return *_pAttr; }
	bool HasAttr() const { return GetFlags() != 0 || !GetAttr().IsEmpty(); }
	bool IsSet(Flags flags) const { return (GetFlags() & flags) != 0; }
	bool IsSet(const Symbol* pSymbol) const { return GetAttr().IsSet(pSymbol); }
	bool IsSetOpt(const Symbol* pSymbol) const { return GetAttr().IsSetOpt(pSymbol); }
	bool CheckAttribute(const Attribute& attr) const;
	static bool CheckFlagConfliction(Flags flags);
	const Symbol* GetSymbolOfDict() const { return _pSymbolOfDict; }
	const Symbol* GetSymbolOfAccessor() const { return _pSymbolOfAccessor; }
	bool IsDeclaredSymbol(const Symbol* pSymbol) const {
		return GetDeclArgOwner().FindBySymbol(pSymbol) ||
			GetSymbolOfDict()->IsIdentical(pSymbol) || GetSymbolOfAccessor()->IsIdentical(pSymbol);
	}
	bool IsResultVoid() const { return GetVTypeResult().IsNil(); }
	bool IsResultReduce() const { return IsSet(Flag::Reduce); }
	static bool IsMappable(const DeclArg& declArg, Flags flags);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DeclCallable& declCaller) const { return this == &declCaller; }
	bool IsIdentical(const DeclCallable* pDeclCaller) const { return this == pDeclCaller; }
	bool IsEqualTo(const DeclCallable& declCaller) const { return IsIdentical(declCaller); }
	bool IsLessThan(const DeclCallable& declCaller) const { return this < &declCaller; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	static Flags SymbolToFlag(const Symbol* pSymbol) {
		return SymbolAssoc_Flag::GetInstance().ToAssociated(pSymbol);
	}
	static const Symbol* FlagToSymbol(Flags flag) {
		return SymbolAssoc_Flag::GetInstance().ToSymbol(flag);
	}
	static Flags SymbolsToFlags(const SymbolList& symbols);
	static String FlagsToString(Flags flags);
};

}

#endif
