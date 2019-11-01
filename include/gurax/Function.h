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
#define Gurax_CreateFunctionAlias(name, strName) (new Function_##name(strName))

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

// Declaration/implementation/creation of Class Method
#define Gurax_DeclareClassMethodAlias(nameVType, name, strName)	\
class Method_##nameVType##_##name : public Function { \
public: \
	Method_##nameVType##_##name(const char* name_ = strName); \
	virtual Value* DoEval(Processor& processor, Argument& argument) const override; \
	static Value_##nameVType& GetValueThis(Argument& argument) { \
		return dynamic_cast<Value_##nameVType&>(argument.GetValueThis()); \
	} \
}; \
Method_##nameVType##_##name::Method_##nameVType##_##name(const char* name_) : Function(Function::Type::ClassMethod, name_) \

#define Gurax_DeclareClassMethod(nameVType, name) Gurax_DeclareClassMethodAlias(nameVType, name, #name)

#define Gurax_ImplementClassMethod(nameVType, name) \
Value* Method_##nameVType##_##name::DoEval(Processor& processor, Argument& argument) const

#define Gurax_CreateClassMethod(nameVType, name) (new Method_##nameVType##_##name())

namespace Gurax {

//------------------------------------------------------------------------------
// Function
//------------------------------------------------------------------------------
class Function : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Function);
public:
	enum class Type { Statement, Function, Method, ClassMethod };
	using Flags = DeclCallable::Flags;
	using Flag = DeclCallable::Flag;
	using ArgOccur = DeclArg::Occur;
	using ArgFlag = DeclArg::Flag;
	using BlkOccur = DeclBlock::Occur;
	using BlkFlag = DeclBlock::Flag;
protected:
	Type _type;
	const Symbol* _pSymbol;
	RefPtr<DeclCallable> _pDeclCallable;
	RefPtr<HelpHolder> _pHelpHolder;
	RefPtr<Frame::WeakPtr> _pwFrameOuter;
	VType* _pVTypeOfOwner;					// this may be nullptr
public:
	static RefPtr<Function> Empty;
public:
	static void Bootup();
public:
	// Constructor
	Function(Type type, const Symbol* pSymbol, DeclCallable* pDeclCallable, HelpHolder* pHelpHolder) :
		_type(type), _pSymbol(pSymbol), _pDeclCallable(pDeclCallable), _pHelpHolder(pHelpHolder),
		_pVTypeOfOwner(nullptr) {}
	Function(Type type) :
		Function(type, Symbol::Empty, new DeclCallable(), new HelpHolder()) {}
	Function(Type type, const Symbol* pSymbol) :
		Function(type, pSymbol, new DeclCallable(), new HelpHolder()) {}
	Function(Type type, const Symbol* pSymbol, DeclCallable* pDeclCallable) :
		Function(type, pSymbol, pDeclCallable, new HelpHolder()) {}
	Function(Type type, const char* name) :
		Function(type, Symbol::Add(name)) {}		
	Function(Type type, const char* name, DeclCallable* pDeclCallable) :
		Function(type, Symbol::Add(name), pDeclCallable) {}
	Function(Type type, const char* name, DeclCallable* pDeclCallable, HelpHolder* pHelpHolder) :
		Function(type, Symbol::Add(name), pDeclCallable, pHelpHolder) {}
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
	static Function* CreateBlockFunction(const Symbol* pSymbol, const Expr_Block& exprOfBlock);
	static Function* CreateDynamicFunction(
		const Symbol* pSymbol, const ValueList& valuesExpr, const Expr_Block& exprOfBlock);
public:
	bool IsTypeStatement() const { return _type == Type::Statement; }
	bool IsTypeFunction() const { return _type == Type::Function; }
	bool IsTypeMethod() const { return _type == Type::Method; }
	bool IsTypeClassMethod() const { return _type == Type::ClassMethod; }
	void SetSymbol(const Symbol* pSymbol) { _pSymbol = pSymbol; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const char* GetName() const { return _pSymbol->GetName(); }
	String MakeFullName() const;
	DeclCallable& GetDeclCallable() { return *_pDeclCallable; }
	const DeclCallable& GetDeclCallable() const { return *_pDeclCallable; }
	void SetFrameOuter(Frame& frameOuter) { _pwFrameOuter.reset(frameOuter.GetWeakPtr()); }
	Frame* LockFrameOuter() const { return _pwFrameOuter? _pwFrameOuter->Lock() : nullptr; }
	void SetVTypeOfOwner(VType& vtypeOfOwner) { _pVTypeOfOwner = &vtypeOfOwner; }
	const VType* GetVTypeOfOwner() const { return _pVTypeOfOwner; }
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
	void DeclareBlock(const Symbol* pSymbol, const DeclBlock::Occur& occur,
					  DeclBlock::Flags flags = DeclBlock::Flag::None) {
		GetDeclCallable().GetDeclBlock().SetSymbol(pSymbol).SetOccur(occur).SetFlags(flags);
	}
	void DeclareBlock(const char* name, const DeclBlock::Occur& occur,
					  DeclBlock::Flags flags = DeclBlock::Flag::None) {
		DeclareBlock(Symbol::Add(name), occur, flags);
	}
	void DeclareBlock(const DeclBlock::Occur& occur, DeclBlock::Flags flags = DeclBlock::Flag::None) {
		DeclareBlock(Gurax_Symbol(block), occur, flags);
	}
	const HelpHolder& GetHelpHolder() const { return *_pHelpHolder; }
	void AddHelp(const Symbol* pLangCode, String doc) {
		_pHelpHolder->AddHelp(pLangCode, std::move(doc));
	}
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpHolder->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	void LinkHelp(VType& vtype, const Symbol* pSymbol);
	void DoEvalVoid(Processor& processor, Argument& argument) const {
		Value::Delete(DoEval(processor, argument));
	}
	void DoCall(Processor& processor, Argument& argument) const;
	void Compose(Composer& composer, Expr_Caller& exprCaller) const;
	Value* ReturnValue(Processor& processor, Argument& argument, RefPtr<Value> pValueRtn) const;
	Value* ReturnIterator(Processor& processor, Argument& argument, RefPtr<Iterator> pIterator) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Function& function) const { return this == &function; }
	bool IsEqualTo(const Function& function) const { return IsIdentical(function); }
	bool IsLessThan(const Function& function) const { return this < &function; }
public:
	// Virtual functions
	virtual bool IsEmpty() const { return false; }
	virtual const Expr& GetExprBody() const { return *Expr::Empty; }
	virtual const PUnit* GetPUnitBody() const { return nullptr; }
	virtual void DoExec(Processor& processor, Argument& argument) const;
	virtual Value* DoEval(Processor& processor, Argument& argument) const { return Value::nil(); }
	virtual void DoCompose(Composer& composer, Expr_Caller& exprCaller) const {}
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
