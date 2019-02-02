//==============================================================================
// Declaration.h
//==============================================================================
#ifndef GURAX_DECLARATION_H
#define GURAX_DECLARATION_H
#include "Attribute.h"

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
		static const UInt32 Closure			= 1 << 0;
		static const UInt32 CutExtraArgs	= 1 << 1;
		static const UInt32 DynamicScope	= 1 << 2;
		static const UInt32 EndMarker		= 1 << 3;
		static const UInt32 Finalizer		= 1 << 4;
		static const UInt32 Flat			= 1 << 5;
		static const UInt32 Fork			= 1 << 6;
		static const UInt32 Leader			= 1 << 7;
		static const UInt32 ListVar			= 1 << 8;
		static const UInt32 Map				= 1 << 9;
		static const UInt32 Nil				= 1 << 10;
		static const UInt32 NoCast			= 1 << 11;
		static const UInt32 NoMap			= 1 << 12;
		static const UInt32 NoNamed			= 1 << 13;
		static const UInt32 Private			= 1 << 14;
		static const UInt32 Privileged		= 1 << 15;
		static const UInt32 Public			= 1 << 16;
		static const UInt32 Read			= 1 << 17;
		static const UInt32 SymbolFunc		= 1 << 18;
		static const UInt32 Trailer			= 1 << 19;
		static const UInt32 Write			= 1 << 29;
	};
public:
	class ArgInfo : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(ArgInfo);
	private:
		const Symbol* _pSymbol;
		UInt32 _flags;
		RefPtr<Attribute> _pAttr;
	public:
		// Constructor
		ArgInfo(const Symbol* pSymbol, UInt32 flags, Attribute* pAttr) :
			_pSymbol(pSymbol), _flags(flags), _pAttr(pAttr) {}
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
		const UInt32 GetFlags() const { return _flags; }
		const Attribute& GetAttr() const { return *_pAttr; }
	public:
		size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
		bool IsIdentical(const ArgInfo& argInfo) const { return this == &argInfo; }
		bool IsEqualTo(const ArgInfo& argInfo) const { return IsIdentical(argInfo); }
		bool IsLessThan(const ArgInfo& argInfo) const { return this < &argInfo; }
		String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(argInfo)"; }
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
	RefPtr<Attribute> _pAttr;
public:
	static void Bootup();
public:
	// Constructor
	Declaration() : _validFlag(false) {}
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
	bool IsValid() const { return _validFlag; }
	const ArgInfoOwner& GetArgInfoOwner() const { return _argInfoOwner; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Declaration& declaration) const { return this == &declaration; }
	bool IsEqualTo(const Declaration& declaration) const { return IsIdentical(declaration); }
	bool IsLessThan(const Declaration& declaration) const { return this < &declaration; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(declaration)"; }
};

}

#endif
