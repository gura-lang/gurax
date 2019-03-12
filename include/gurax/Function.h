//==============================================================================
// Function.h
//==============================================================================
#ifndef GURAX_FUNCTION_H
#define GURAX_FUNCTION_H
#include "DeclCallable.h"
#include "Help.h"
#include "Frame.h"
#include "Argument.h"
#include "ArgAccessor.h"

#define Gurax_DeclareFunctionAlias(name, strName) \
class Function_##name : public Function { \
public: \
	Function_##name(const char* name_ = strName); \
	virtual Value* DoEval(Processor& processor, Argument& argument) const override; \
}; \
Function_##name::Function_##name(const char* name_) : Function(Function::Type::Function, name_) \

#define Gurax_DeclareFunction(name) Gurax_DeclareFunctionAlias(name, #name)

#define Gurax_ImplementFunction(name) \
Value* Function_##name::DoEval(Processor& processor, Argument& argument) const

#define Gurax_AssignFunction(name) \
frame.AssignFunction(new Function_##name())

#define Gurax_DeclareStatementAlias(name, strName) \
class Statement_##name : public Function { \
public: \
	Statement_##name(const char* name_ = strName); \
	virtual void Compose(Composer& composer, Expr_Caller* pExprCaller) const override; \
}; \
Statement_##name::Statement_##name(const char* name_) : Function(Function::Type::Statement, name_) \

#define Gurax_DeclareStatement(name) Gurax_DeclareStatementAlias(name, #name)

#define Gurax_ImplementStatement(name) \
void Statement_##name::Compose(Composer& composer, Expr_Caller* pExprCaller) const

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
	RefPtr<DeclCallable> _pDeclCallable;
	RefPtr<HelpProvider> _pHelpProvider;
	RefPtr<Frame::WeakPtr> _pwFrameParent;
public:
	// Constructor
	Function(Type type) :
		Function(type, Symbol::Empty, new DeclCallable(), new HelpProvider()) {}
	Function(Type type, const Symbol* pSymbol) :
		Function(type, pSymbol, new DeclCallable(), new HelpProvider()) {}
	Function(Type type, const Symbol* pSymbol, DeclCallable* pDeclCallable) :
		Function(type, pSymbol, pDeclCallable, new HelpProvider()) {}
	Function(Type type, const Symbol* pSymbol, DeclCallable* pDeclCallable, HelpProvider* pHelpProvider) :
		_type(type), _pSymbol(pSymbol), _pDeclCallable(pDeclCallable), _pHelpProvider(pHelpProvider) {}
	Function(Type type, const char* name) :
		Function(type, Symbol::Add(name)) {}		
	Function(Type type, const char* name, DeclCallable* pDeclCallable) :
		Function(type, Symbol::Add(name), pDeclCallable) {}
	Function(Type type, const char* name, DeclCallable* pDeclCallable, HelpProvider* pHelpProvider) :
		Function(type, Symbol::Add(name), pDeclCallable, pHelpProvider) {}
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
	DeclCallable& GetDeclCallable() { return *_pDeclCallable; }
	const DeclCallable& GetDeclCallable() const { return *_pDeclCallable; }
	void SetFrameParent(Frame& frameParent) { _pwFrameParent.reset(frameParent.GetWeakPtr()); }
	Frame* LockFrameParent() { return _pwFrameParent? _pwFrameParent->Lock() : nullptr; }
	void DeclareCaller(const VType& vtype, DeclCallable::Flags flags) {
		GetDeclCallable().SetVTypeResult(vtype);
		GetDeclCallable().SetFlags(flags);
	}
	void DeclareArg(const Symbol* pSymbol, const VType& vtype,
					const DeclArg::Occur& occur = DeclArg::Occur::Once,
					DeclArg::Flags flags = DeclArg::Flag::None, Expr* pExprDefault = nullptr) {
		GetDeclCallable().GetDeclArgOwner().push_back(new DeclArg(pSymbol, vtype, occur, flags, pExprDefault));
	}
	void DeclareArg(const char* name, const VType& vtype,
					const DeclArg::Occur& occur = DeclArg::Occur::Once,
					DeclArg::Flags flags = DeclArg::Flag::None, Expr* pExprDefault = nullptr) {
		DeclareArg(Symbol::Add(name), vtype, occur, flags, pExprDefault);
	}
	void DeclareAttrOpt(const Symbol* pSymbol) {
		GetDeclCallable().GetAttr().AddSymbolOpt(pSymbol);
	}
	void DeclareAttrOpt(const char* name) {
		GetDeclCallable().GetAttr().AddSymbolOpt(Symbol::Add(name));
	}
	void DeclareBlock(const DeclBlock::Occur& occur, DeclBlock::Flags flags = DeclBlock::Flag::None) {
		GetDeclCallable().GetDeclBlock().SetOccur(occur).SetFlags(flags);
	}
	void DeclareBlock(const Symbol* pSymbol, const DeclBlock::Occur& occur,
					  DeclBlock::Flags flags = DeclBlock::Flag::None) {
		GetDeclCallable().GetDeclBlock().SetSymbol(pSymbol).SetOccur(occur).SetFlags(flags);
	}
	void DeclareBlock(const char* name, const DeclBlock::Occur& occur,
					  DeclBlock::Flags flags = DeclBlock::Flag::None) {
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
public:
	// Virtual functions
	virtual Value* DoCall(Processor& processor, Argument& argument) const { return DoEval(processor, argument); }
	virtual Value* DoEval(Processor& processor, Argument& argument) const { return Value::nil(); };
	virtual void Compose(Composer& composer, Expr_Caller* pExprCaller) const {}
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
