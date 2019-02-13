//==============================================================================
// DeclCaller.h
//==============================================================================
#ifndef GURAX_DECLCALLER_H
#define GURAX_DECLCALLER_H
#include "Attribute.h"
#include "Symbols.h"
#include "DeclArg.h"

namespace Gurax {

class ExprLink;

//------------------------------------------------------------------------------
// DeclCaller
//------------------------------------------------------------------------------
class DeclCaller : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DeclCaller);
public:
	struct Flag {
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
	class SymbolAssoc_Flag : public SymbolAssoc<UInt32, 0> {
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
		}
		static SymbolAssoc* GetInstance() {
			return _pInstance? _pInstance : (_pInstance = new SymbolAssoc_Flag());
		}
	};
private:
	DeclArgOwner _declArgOwner;
	UInt32 _flags;
	RefPtr<Attribute> _pAttr;
public:
	static const DeclCaller* Empty;
public:
	static void Bootup();
public:
	// Constructor
	DeclCaller() : _flags(0), _pAttr(new Attribute()) {}
	// Copy constructor/operator
	DeclCaller(const DeclCaller& src) = delete;
	DeclCaller& operator=(const DeclCaller& src) = delete;
	// Move constructor/operator
	DeclCaller(DeclCaller&& src) = delete;
	DeclCaller& operator=(DeclCaller&& src) noexcept = delete;
protected:
	// Destructor
	~DeclCaller() = default;
public:
	bool Prepare(const ExprLink& exprLinkCdr, const Attribute& attr, bool issueErrorFlag);
	void Clear();
	const DeclArgOwner& GetDeclArgOwner() const { return _declArgOwner; }
	UInt32 GetFlags() const { return _flags; }
	const Attribute& GetAttr() const { return *_pAttr; }
	bool IsSet(const Symbol* pSymbol) const { return GetAttr().IsSet(pSymbol); }
	bool IsSetOpt(const Symbol* pSymbol) const { return GetAttr().IsSetOpt(pSymbol); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DeclCaller& declCaller) const { return this == &declCaller; }
	bool IsEqualTo(const DeclCaller& declCaller) const { return IsIdentical(declCaller); }
	bool IsLessThan(const DeclCaller& declCaller) const { return this < &declCaller; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	static UInt32 SymbolToFlag(const Symbol* pSymbol) {
		return SymbolAssoc_Flag::GetInstance()->ToAssociated(pSymbol);
	}
	static const Symbol* FlagToSymbol(UInt32 flag) {
		return SymbolAssoc_Flag::GetInstance()->ToSymbol(flag);
	}
	static String FlagsToString(UInt32 flags);
};

}

#endif
