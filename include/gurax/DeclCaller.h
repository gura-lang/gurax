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
	struct FlagCaller {
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
	class SymbolAssoc_FlagCaller : public SymbolAssoc<UInt32, 0> {
	public:
		SymbolAssoc_FlagCaller() {
			Assoc(Gurax_Symbol(map),			FlagCaller::Map);
			Assoc(Gurax_Symbol(nomap),			FlagCaller::NoMap);
			Assoc(Gurax_Symbol(closure),		FlagCaller::Closure);
			Assoc(Gurax_Symbol(cut_extra_args),	FlagCaller::CutExtraArgs);
			Assoc(Gurax_Symbol(dynamic_scope),	FlagCaller::DynamicScope);
			Assoc(Gurax_Symbol(end_marker),		FlagCaller::EndMarker);
			Assoc(Gurax_Symbol(flat),			FlagCaller::Flat);
			Assoc(Gurax_Symbol(fork),			FlagCaller::Fork);
			Assoc(Gurax_Symbol(finalizer),		FlagCaller::Finalizer);
			Assoc(Gurax_Symbol(leader),			FlagCaller::Leader);
			Assoc(Gurax_Symbol(trailer),		FlagCaller::Trailer);
			Assoc(Gurax_Symbol(symbol_func),	FlagCaller::SymbolFunc);
			Assoc(Gurax_Symbol(nonamed),		FlagCaller::NoNamed);
			Assoc(Gurax_Symbol(public_),		FlagCaller::Public);
			Assoc(Gurax_Symbol(private_),		FlagCaller::Private);
			Assoc(Gurax_Symbol(privileged),		FlagCaller::Privileged);
		}
		static SymbolAssoc* GetInstance() {
			return _pInstance? _pInstance : (_pInstance = new SymbolAssoc_FlagCaller());
		}
	};
private:
	bool _validFlag;
	DeclArgOwner _declArgOwner;
	UInt32 _flagsCaller;
	RefPtr<Attribute> _pAttr;
public:
	static void Bootup();
public:
	// Constructor
	DeclCaller() : _validFlag(false), _flagsCaller(0), _pAttr(new Attribute()) {}
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
	bool IsValid() const { return _validFlag; }
	const DeclArgOwner& GetDeclArgOwner() const { return _declArgOwner; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DeclCaller& declCaller) const { return this == &declCaller; }
	bool IsEqualTo(const DeclCaller& declCaller) const { return IsIdentical(declCaller); }
	bool IsLessThan(const DeclCaller& declCaller) const { return this < &declCaller; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	static UInt32 SymbolToFlagCaller(const Symbol* pSymbol) {
		return SymbolAssoc_FlagCaller::GetInstance()->ToValue(pSymbol);
	}
	static const Symbol* FlagCallerToSymbol(UInt32 flagCaller) {
		return SymbolAssoc_FlagCaller::GetInstance()->ToSymbol(flagCaller);
	}
	static String FlagsCallerToString(UInt32 flags);
};

}

#endif
