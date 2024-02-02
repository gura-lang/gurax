//==============================================================================
// DeclArg.h
//==============================================================================
#ifndef GURAX_DECLARG_H
#define GURAX_DECLARG_H
#include "Attribute.h"
#include "Symbols.h"

namespace Gurax {

class VType;
class ArgSlotFactory;
class Processor;

//------------------------------------------------------------------------------
// DeclArg
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DeclArg : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DeclArg);
public:
	using Flags = UInt32;
	struct GURAX_DLLDECLARE Flag {
		static const Flags None			= 0;
		static const Flags ListVar		= 1 << 0;	// :listVar
		static const Flags Referencer	= 1 << 1;	// &x
		static const Flags Nil			= 1 << 2;	// :nil
		static const Flags NilRef		= 1 << 3;	// :nilRef
		static const Flags StreamR		= 1 << 4;	// :r
		static const Flags StreamW		= 1 << 5;	// :w
		static const Flags Map			= 1 << 6;	// :map
		static const Flags NoMap		= 1 << 7;	// :noMap
		static const Flags NoCast		= 1 << 8;	// :noCast
		static const Flags StringCast	= 1 << 9;	// :stringCast
		static const Flags ExplicitCast	= 1 << 10;	// :explicitCast
		static const Flags OfClass		= 1 << 11;	// :static
		static const Flags OfInstance	= 1 << 12;	// :instance
		static const Flags Public		= 1 << 13;	// :public
		static const Flags Private		= 1 << 14;	// :private
		static const Flags Readable		= 1 << 15;	// :readable
		static const Flags Writable		= 1 << 16;	// :writable
	};
	class GURAX_DLLDECLARE Occur {
	private:
		const char* _marker;
		const ArgSlotFactory& _argSlotFactory;
	public:
		static const Occur Invalid;
		static const Occur Zero;		// (none)
		static const Occur Once;		// 1
		static const Occur ZeroOrOnce;	// ?
		static const Occur ZeroOrMore;	// *
		static const Occur OnceOrMore;	// +
	public:
		// Constructor
		explicit Occur(const char* marker, const ArgSlotFactory& argSlotFactory) :
			_marker(marker), _argSlotFactory(argSlotFactory) {}
		// Copy constructor/operator
		Occur(const Occur& src) = delete;
		Occur& operator=(const Occur& src) = delete;
		// Move constructor/operator
		Occur(Occur&& src) = delete;
		Occur& operator=(Occur&& src) noexcept = delete;
		// Destructor
		virtual ~Occur() = default;
	public:
		const char* GetMarker() const { return _marker; }
		const ArgSlotFactory& GetArgSlotFactory() const { return _argSlotFactory; }
	public:
		size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
		bool IsIdentical(const Occur& occur) const { return this == &occur; }
		bool IsEqualTo(const Occur& occur) const { return IsIdentical(occur); }
		bool IsLessThan(const Occur& occur) const { return this < &occur; }
	};
	class GURAX_DLLDECLARE SymbolAssoc_Flag : public SymbolAssoc<Flags, Flag::None> {
	public:
		SymbolAssoc_Flag() {
			Assoc(Gurax_Symbol(listVar),	Flag::ListVar);
			Assoc(Gurax_Symbol(referencer),	Flag::Referencer);
			Assoc(Gurax_Symbol(nil),		Flag::Nil);
			Assoc(Gurax_Symbol(nilRef),		Flag::NilRef);
			Assoc(Gurax_Symbol(r),			Flag::StreamR);
			Assoc(Gurax_Symbol(w),			Flag::StreamW);
			Assoc(Gurax_Symbol(map),		Flag::Map);
			Assoc(Gurax_Symbol(noMap),		Flag::NoMap);
			Assoc(Gurax_Symbol(noCast),		Flag::NoCast);
			Assoc(Gurax_Symbol(stringCast),	Flag::StringCast);
			Assoc(Gurax_Symbol(static_),	Flag::OfClass);
			//Assoc(Gurax_Symbol(instance),	Flag::OfInstance);
			Assoc(Gurax_Symbol(public_),	Flag::Public);
			Assoc(Gurax_Symbol(private_),	Flag::Private);
			Assoc(Gurax_Symbol(R),			Flag::Readable);
			Assoc(Gurax_Symbol(W),			Flag::Writable);
			Assoc(Gurax_Symbol(const_),		Flag::None);		// only for DoesExit()
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_Flag());
		}
	};
private:
	const Symbol* _pSymbol;
	RefPtr<DottedSymbol> _pDottedSymbol;
	const VType* _pVType;
	const Occur& _occur;
	Flags _flags;
	RefPtr<Expr> _pExprDefault;	// this may be nullptr
public:
	static DeclArg* Undefined;
	static DeclArg* Any;
public:
	// Constructor
	DeclArg(const Symbol* pSymbol, DottedSymbol* pDottedSymbol, const Occur& occur, Flags flags, Expr* pExprDefault);
	DeclArg(const Symbol* pSymbol, const VType& vtype, const Occur& occur, Flags flags, Expr* pExprDefault);
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
	static void Bootup();
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const DottedSymbol& GetDottedSymbol() const { return *_pDottedSymbol; }
	//bool IsVType(const VType& vtype) const { return _pVType->IsIdentical(vtype); }
	const VType& GetVType() const { return *_pVType; }
	void SetVType(const VType* pVType) { _pVType = pVType; }
	const Occur& GetOccur() const { return _occur; }
	const ArgSlotFactory& GetArgSlotFactory() const { return GetOccur().GetArgSlotFactory(); }
	bool IsOccurOnce() const { return GetOccur().IsIdentical(Occur::Once); }
	bool IsOccurZeroOrOnce() const { return GetOccur().IsIdentical(Occur::ZeroOrOnce); }
	bool IsOccurZeroOrMore() const { return GetOccur().IsIdentical(Occur::ZeroOrMore); }
	bool IsOccurOnceOrMore() const { return GetOccur().IsIdentical(Occur::OnceOrMore); }
	Flags GetFlags() const { return _flags; }
	bool IsSet(Flags flags) const { return (GetFlags() & flags) != 0; }
	const Expr* GetExprDefault() const { return _pExprDefault.get(); }
	static DeclArg* CreateFromExpr(const Expr& expr);
	bool FixVType(Frame& frame);
	Value* Cast(Processor& processor, Frame& frame, const Value& value);
	static bool CheckFlagConfliction(Flags flags);
	static Flags SymbolToFlag(const Symbol* pSymbol) {
		return SymbolAssoc_Flag::GetInstance().ToAssociated(pSymbol);
	}
	static const Symbol* FlagToSymbol(Flags flag) {
		return SymbolAssoc_Flag::GetInstance().ToSymbol(flag);
	}
	static String FlagsToString(Flags flags);
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
class DeclArgList : public ListBase<DeclArg*> {
public:
	bool IsValidArgNum(size_t nArgs) const;
	DeclArg* FindBySymbol(const Symbol* pSymbol) const;
	String ToString(const StringStyle& ss) const;
};

//------------------------------------------------------------------------------
// DeclArgOwner
//------------------------------------------------------------------------------
class DeclArgOwner: public DeclArgList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DeclArgOwner);
protected:
	~DeclArgOwner() { Clear(); }
public:
	void Clear() {
		for (DeclArg* pDeclArg : *this) DeclArg::Delete(pDeclArg);
		clear();
	}
};

}

#endif
