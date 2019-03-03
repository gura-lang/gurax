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

//------------------------------------------------------------------------------
// DeclArg
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DeclArg : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DeclArg);
public:
	struct Flag {
		static const UInt32 None			= 0;
		static const UInt32 ListVar			= 1 << 0;	// :listvar
		static const UInt32 Map				= 1 << 1;	// :map
		static const UInt32 NoMap			= 1 << 2;	// :nomap
		static const UInt32 NoCast			= 1 << 3;	// :nocast
		static const UInt32 Nil				= 1 << 4;	// :nil
		static const UInt32 Read			= 1 << 5;	// :r
		static const UInt32 Write			= 1 << 6;	// :w
	};
	class Occur {
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
	class SymbolAssoc_Flag : public SymbolAssoc<UInt32, Flag::None> {
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
	const VType* _pVType;
	const Occur& _occur;
	UInt32 _flags;
	RefPtr<Expr> _pExprDefault;	// this may be nullptr
public:
	// Constructor
	DeclArg(const Symbol* pSymbol, DottedSymbol* pDottedSymbol,
			const Occur& occur, UInt32 flags, Expr* pExprDefault);
	DeclArg(const Symbol* pSymbol, const VType& vtype,
			const Occur& occur, UInt32 flags, Expr* pExprDefault);
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
	bool IsVType(const VType& vtype) const { return _pVType->IsIdentical(vtype); }
	const VType& GetVType() const { return *_pVType; }
	void SetVType(const VType* pVType) { _pVType = pVType; }
	const Occur& GetOccur() const { return _occur; }
	const ArgSlotFactory& GetArgSlotFactory() const { return GetOccur().GetArgSlotFactory(); }
	bool IsOccurOnce() const { return GetOccur().IsIdentical(Occur::Once); }
	bool IsOccurZeroOrOnce() const { return GetOccur().IsIdentical(Occur::ZeroOrOnce); }
	bool IsOccurZeroOrMore() const { return GetOccur().IsIdentical(Occur::ZeroOrMore); }
	bool IsOccurOnceOrMore() const { return GetOccur().IsIdentical(Occur::OnceOrMore); }
	UInt32 GetFlags() const { return _flags; }
	const Expr* GetExprDefault() const { return _pExprDefault.get(); }
	static DeclArg* CreateFromExpr(const Expr* pExpr);
	bool FixVType(Frame* pFrame);
	static UInt32 SymbolToFlag(const Symbol* pSymbol) {
		return SymbolAssoc_Flag::GetInstance()->ToAssociated(pSymbol);
	}
	static const Symbol* FlagToSymbol(UInt32 flag) {
		return SymbolAssoc_Flag::GetInstance()->ToSymbol(flag);
	}
	static String FlagsToString(UInt32 flags);
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
public:
	String ToString(const StringStyle& ss) const;
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
