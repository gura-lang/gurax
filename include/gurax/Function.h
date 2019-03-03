//==============================================================================
// Function.h
//==============================================================================
#ifndef GURAX_FUNCTION_H
#define GURAX_FUNCTION_H
#include "DeclCaller.h"
#include "Help.h"
#include "Frame.h"
#include "Argument.h"
#include "ArgAccessor.h"

#define Gurax_DeclareFunctionAlias(name, strName) \
class Function_##name : public Function { \
public: \
	Function_##name(const char* name_ = strName); \
	virtual Value* DoCall(Processor& processor, const Argument& argument) const override; \
}; \
Function_##name::Function_##name(const char* name_) : Function(Function::Type::Function, name_) \

#define Gurax_DeclareFunction(name) Gurax_DeclareFunctionAlias(name, #name)

#define Gurax_ImplementFunction(name) \
Value* Function_##name::DoCall(Processor& processor, const Argument& argument) const

#define Gurax_AssignFunction(name) \
frame.AssignFunction(new Function_##name())

#define Gurax_DeclareStatementAlias(name, strName) \
class Statement_##name : public Function { \
public: \
	Statement_##name(const char* name_ = strName); \
	virtual void Compose(Composer& composer, const Expr_Caller* pExprCaller) const override; \
}; \
Statement_##name::Statement_##name(const char* name_) : Function(Function::Type::Statement, name_) \

#define Gurax_DeclareStatement(name) Gurax_DeclareStatementAlias(name, #name)

#define Gurax_ImplementStatement(name) \
void Statement_##name::Compose(Composer& composer, const Expr_Caller* pExprCaller) const

#define Gurax_AssignStatement(name) \
frame.AssignFunction(new Statement_##name())

namespace Gurax {

//------------------------------------------------------------------------------
// Function
//------------------------------------------------------------------------------
class Function : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Function);
public:
	enum class Type { Statement, Function, Method };
protected:
	Type _type;
	const Symbol* _pSymbol;
	RefPtr<DeclCaller> _pDeclCaller;
	RefPtr<HelpProvider> _pHelpProvider;
	RefPtr<Frame::WeakPtr> _pwFrameParent;
public:
	// Constructor
	Function(Type type) :
		Function(type, Symbol::Empty, new DeclCaller(), new HelpProvider()) {}
	Function(Type type, const Symbol* pSymbol) :
		Function(type, pSymbol, new DeclCaller(), new HelpProvider()) {}
	Function(Type type, const Symbol* pSymbol, DeclCaller* pDeclCaller) :
		Function(type, pSymbol, pDeclCaller, new HelpProvider()) {}
	Function(Type type, const Symbol* pSymbol, DeclCaller* pDeclCaller, HelpProvider* pHelpProvider) :
		_type(type), _pSymbol(pSymbol), _pDeclCaller(pDeclCaller), _pHelpProvider(pHelpProvider) {}
	Function(Type type, const char* name) :
		Function(type, Symbol::Add(name)) {}		
	Function(Type type, const char* name, DeclCaller* pDeclCaller) :
		Function(type, Symbol::Add(name), pDeclCaller) {}
	Function(Type type, const char* name, DeclCaller* pDeclCaller, HelpProvider* pHelpProvider) :
		Function(type, Symbol::Add(name), pDeclCaller, pHelpProvider) {}
	// Copy constructor/operator
	Function(const Function& src) = delete;
	Function& operator=(const Function& src) = delete;
	// Move constructor/operator
	Function(Function&& src) = delete;
	Function& operator=(Function&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Function() = default;
public:
	bool IsTypeStatement() const { return _type == Type::Statement; }
	bool IsTypeFunction() const { return _type == Type::Function; }
	bool IsTypeMethod() const { return _type == Type::Method; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	DeclCaller& GetDeclCaller() { return *_pDeclCaller; }
	const DeclCaller& GetDeclCaller() const { return *_pDeclCaller; }
	void SetFrameParent(Frame* pFrameParent) { _pwFrameParent.reset(pFrameParent->GetWeakPtr()); }
	Frame* LockFrameParent() { return _pwFrameParent? _pwFrameParent->Lock() : nullptr; }
	void DeclareCaller(const VType& vtype, UInt32 flags) {
		GetDeclCaller().SetVType(vtype);
		GetDeclCaller().SetFlags(flags);
	}
	void DeclareArg(const Symbol* pSymbol, const VType& vtype,
					const DeclArg::Occur& occur = DeclArg::Occur::Once,
					UInt32 flags = DeclArg::Flag::None, Expr* pExprDefault = nullptr) {
		GetDeclCaller().GetDeclArgOwner().push_back(new DeclArg(pSymbol, vtype, occur, flags, pExprDefault));
	}
	void DeclareArg(const char* name, const VType& vtype,
					const DeclArg::Occur& occur = DeclArg::Occur::Once,
					UInt32 flags = DeclArg::Flag::None, Expr* pExprDefault = nullptr) {
		DeclareArg(Symbol::Add(name), vtype, occur, flags, pExprDefault);
	}
	void DeclareAttrOpt(const Symbol* pSymbol) {
		GetDeclCaller().GetAttr().AddSymbolOpt(pSymbol);
	}
	void DeclareAttrOpt(const char* name) {
		GetDeclCaller().GetAttr().AddSymbolOpt(Symbol::Add(name));
	}
	void DeclareBlock(const DeclBlock::Occur& occur, UInt32 flags = DeclBlock::Flag::None) {
		GetDeclCaller().GetDeclBlock().SetOccur(occur).SetFlags(flags);
	}
	void DeclareBlock(const Symbol* pSymbol, const DeclBlock::Occur& occur, UInt32 flags = DeclBlock::Flag::None) {
		GetDeclCaller().GetDeclBlock().SetSymbol(pSymbol).SetOccur(occur).SetFlags(flags);
	}
	void DeclareBlock(const char* name, const DeclBlock::Occur& occur, UInt32 flags = DeclBlock::Flag::None) {
		DeclareBlock(Symbol::Add(name), occur, flags);
	}
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Function& function) const { return this == &function; }
	bool IsEqualTo(const Function& function) const { return IsIdentical(function); }
	bool IsLessThan(const Function& function) const { return this < &function; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(function)"; }
public:
	// Virtual functions
	virtual Value* DoCall(Processor& processor, const Argument& argument) const { return Value::nil(); };
	virtual void Compose(Composer& composer, const Expr_Caller* pExprCaller) const {}
};

}

#endif
