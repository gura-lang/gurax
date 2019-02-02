//==============================================================================
// Declaration.h
//==============================================================================
#ifndef GURAX_DECLARATION_H
#define GURAX_DECLARATION_H
#include "Attribute.h"

namespace Gurax {

class Expr_Caller;

//------------------------------------------------------------------------------
// Declaration
//------------------------------------------------------------------------------
class Declaration : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Declaration);
public:
	class ArgInfo : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(ArgInfo);
	private:
		const Symbol* _pSymbol;
		UInt32 _flags;
		RefPtr<Attribute> _pAttribute;
	public:
		// Constructor
		ArgInfo(const Symbol* pSymbol, UInt32 flags, Attribute* pAttribute) :
			_pSymbol(pSymbol), _flags(flags), _pAttribute(pAttribute) {}
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
		const Attribute& GetAttribute() const { return *_pAttribute; }
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
	RefPtr<Attribute> _pAttribute;
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
	bool Prepare(const Expr_Caller* pExprCaller, bool issueErrorFlag);
	bool IsValid() const { return _validFlag; }
	const ArgInfoOwner& GetArgInfoOwner() const { return _argInfoOwner; }
	const Attribute& GetAttribute() const { return *_pAttribute; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Declaration& declaration) const { return this == &declaration; }
	bool IsEqualTo(const Declaration& declaration) const { return IsIdentical(declaration); }
	bool IsLessThan(const Declaration& declaration) const { return this < &declaration; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(declaration)"; }
};

}

#endif
