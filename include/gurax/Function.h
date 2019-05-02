//==============================================================================
// Function.h
//==============================================================================
#ifndef GURAX_FUNCTION_H
#define GURAX_FUNCTION_H
#include "DeclCallable.h"
#include "Help.h"
#include "Frame.h"
#include "Argument.h"

//------------------------------------------------------------------------------
// Macros to declare functions
//------------------------------------------------------------------------------
// Declaration/implementation/creation of Statement
#define Gurax_DeclareStatementAlias(name, strName) \
class Statement_##name : public Function { \
public: \
	Statement_##name(const char* name_ = strName); \
	virtual void DoCompose(Composer& composer, Expr_Caller& exprCaller) const override; \
}; \
Statement_##name::Statement_##name(const char* name_) : Function(Function::Type::Statement, name_) \

#define Gurax_DeclareStatement(name) Gurax_DeclareStatementAlias(name, #name)

#define Gurax_ImplementStatement(name) \
void Statement_##name::DoCompose(Composer& composer, Expr_Caller& exprCaller) const

#define Gurax_CreateStatement(name) (new Statement_##name())

// Declaration/implementation/creation of Function
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

#define Gurax_CreateFunction(name) (new Function_##name())

// Declaration/implementation/creation of Method
#define Gurax_DeclareMethodAlias(nameVType, name, strName)	\
class Method_##nameVType##_##name : public Function { \
public: \
	Method_##nameVType##_##name(const char* name_ = strName); \
	virtual Value* DoEval(Processor& processor, Argument& argument) const override; \
	static Value_##nameVType& GetValueThis(Argument& argument) { \
		return dynamic_cast<Value_##nameVType&>(argument.GetValueThis()); \
	} \
}; \
Method_##nameVType##_##name::Method_##nameVType##_##name(const char* name_) : Function(Function::Type::Method, name_) \

#define Gurax_DeclareMethod(nameVType, name) Gurax_DeclareMethodAlias(nameVType, name, #name)

#define Gurax_ImplementMethod(nameVType, name) \
Value* Method_##nameVType##_##name::DoEval(Processor& processor, Argument& argument) const

#define Gurax_CreateMethod(nameVType, name) (new Method_##nameVType##_##name())

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
	using Flags = DeclCallable::Flags;
	using Flag = DeclCallable::Flag;
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
	const char* GetName() const { return _pSymbol->GetName(); }
	String MakeFullName() const;
	DeclCallable& GetDeclCallable() { return *_pDeclCallable; }
	const DeclCallable& GetDeclCallable() const { return *_pDeclCallable; }
	void SetFrameParent(Frame& frameParent) { _pwFrameParent.reset(frameParent.GetWeakPtr()); }
	Frame* LockFrameParent() const { return _pwFrameParent? _pwFrameParent->Lock() : nullptr; }
	void Declare(const VType& vtypeResult, Flags flags) {
		GetDeclCallable().SetVTypeResult(vtypeResult);
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
	void AddHelp(const Symbol* pLangCode, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(doc));
	}
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	void DoEvalVoid(Processor& processor, Argument& argument) const {
		Value::Delete(DoEval(processor, argument));
	}
	void DoCall(Processor& processor, Argument& argument) const;
	void Compose(Composer& composer, Expr_Caller& exprCaller) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Function& function) const { return this == &function; }
	bool IsEqualTo(const Function& function) const { return IsIdentical(function); }
	bool IsLessThan(const Function& function) const { return this < &function; }
public:
	// Virtual functions
	virtual void DoExec(Processor& processor, Argument& argument) const;
	virtual Value* DoEval(Processor& processor, Argument& argument) const { return Value::nil(); };
	virtual void DoCompose(Composer& composer, Expr_Caller& exprCaller) const {}
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
