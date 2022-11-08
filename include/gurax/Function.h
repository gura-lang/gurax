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
Statement_##name::Statement_##name(const char* name_) : Function(Type::Statement, name_, Flag::None)

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
Function_##name::Function_##name(const char* name_) : Function(Type::Function, name_, Flag::None)

#define Gurax_DeclareFunction(name) Gurax_DeclareFunctionAlias(name, #name)

#define Gurax_ImplementFunction(name) \
Value* Function_##name::DoEval(Processor& processor, Argument& argument) const

#define Gurax_ImplementFunctionEx(name, processor, argument) \
Value* Function_##name::DoEval(Processor& processor, Argument& argument) const

#define Gurax_CreateFunction(name) (new Function_##name())
#define Gurax_CreateFunctionAlias(name, strName) (new Function_##name(strName))

// Declaration/implementation/creation of Constructor
#define Gurax_DeclareConstructorAlias(name, strName) \
class Constructor_##name : public Constructor { \
public: \
	Constructor_##name(const char* name_ = strName); \
	virtual Value* DoEval(Processor& processor, Argument& argument) const override; \
}; \
Constructor_##name::Constructor_##name(const char* name_) : Constructor(name_, Flag::None)

#define Gurax_DeclareConstructor(name) Gurax_DeclareConstructorAlias(name, #name)

#define Gurax_ImplementConstructor(name) \
Value* Constructor_##name::DoEval(Processor& processor, Argument& argument) const

#define Gurax_ImplementConstructorEx(name, processor, argument) \
Value* Constructor_##name::DoEval(Processor& processor, Argument& argument) const

#define Gurax_CreateConstructor(name) (new Constructor_##name())
#define Gurax_CreateConstructorAlias(name, strName) (new Constructor_##name(strName))

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
Method_##nameVType##_##name::Method_##nameVType##_##name(const char* name_) : Function(Type::Method, name_, Flag::OfInstance)

#define Gurax_DeclareMethod(nameVType, name) Gurax_DeclareMethodAlias(nameVType, name, #name)

#define Gurax_ImplementMethod(nameVType, name) \
Value* Method_##nameVType##_##name::DoEval(Processor& processor, Argument& argument) const

#define Gurax_ImplementMethodEx(nameVType, name, processor, argument) \
Value* Method_##nameVType##_##name::DoEval(Processor& processor, Argument& argument) const

#define Gurax_CreateMethod(nameVType, name) (new Method_##nameVType##_##name())
#define Gurax_CreateMethodAlias(nameVType, strName) (new Method_##nameVType##_##name(strName))

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
Method_##nameVType##_##name::Method_##nameVType##_##name(const char* name_) : Function(Type::Method, name_, Flag::OfClass)

#define Gurax_DeclareClassMethod(nameVType, name) Gurax_DeclareClassMethodAlias(nameVType, name, #name)

#define Gurax_ImplementClassMethod(nameVType, name) \
Value* Method_##nameVType##_##name::DoEval(Processor& processor, Argument& argument) const

#define Gurax_ImplementClassMethodEx(nameVType, name, processor, argument) \
Value* Method_##nameVType##_##name::DoEval(Processor& processor, Argument& argument) const

#define Gurax_CreateClassMethod(nameVType, name) (new Method_##nameVType##_##name())
#define Gurax_CreateClassMethodAlias(nameVType, name, strName) (new Method_##nameVType##_##name(strName))

// Declaration/implementation/creation of Hybrid Method
#define Gurax_DeclareHybridMethodAlias(nameVType, name, strName)	\
class Method_##nameVType##_##name : public Function { \
public: \
	Method_##nameVType##_##name(const char* name_ = strName); \
	virtual Value* DoEval(Processor& processor, Argument& argument) const override; \
	static Value_##nameVType& GetValueThis(Argument& argument) { \
		return dynamic_cast<Value_##nameVType&>(argument.GetValueThis()); \
	} \
}; \
Method_##nameVType##_##name::Method_##nameVType##_##name(const char* name_) : Function(Type::Method, name_, Flag::OfClass | Flag::OfInstance)

#define Gurax_DeclareHybridMethod(nameVType, name) Gurax_DeclareHybridMethodAlias(nameVType, name, #name)

#define Gurax_ImplementHybridMethod(nameVType, name) \
Value* Method_##nameVType##_##name::DoEval(Processor& processor, Argument& argument) const

#define Gurax_CreateHybridMethod(nameVType, name) (new Method_##nameVType##_##name())
#define Gurax_CreateHybridMethodAlias(nameVType, name, strName) (new Method_##nameVType##_##name(strName))

namespace Gurax {

//------------------------------------------------------------------------------
// Function
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Function : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Function);
public:
	using Type = DeclCallable::Type;
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
	Function(Type type, DeclCallable::Flags flags) :
		Function(type, Symbol::Empty, new DeclCallable(flags), new HelpHolder()) {}
	Function(Type type, const Symbol* pSymbol, DeclCallable::Flags flags) :
		Function(type, pSymbol, new DeclCallable(flags), new HelpHolder()) {}
	Function(Type type, const Symbol* pSymbol, DeclCallable* pDeclCallable) :
		Function(type, pSymbol, pDeclCallable, new HelpHolder()) {}
	Function(Type type, const char* name, DeclCallable::Flags flags) :
		Function(type, Symbol::Add(name), flags) {}		
	Function(Type type, const char* name, DeclCallable* pDeclCallable) :
		Function(type, Symbol::Add(name), pDeclCallable) {}
	Function(Type type, const char* name, DeclCallable* pDeclCallable, HelpHolder* pHelpHolder) :
		Function(type, Symbol::Add(name), pDeclCallable, pHelpHolder) {}
	// Copy constructor/operator
	Function(const Function& src) :
		_type(src._type), _pSymbol(src._pSymbol), _pDeclCallable(src._pDeclCallable.Reference()),
		_pHelpHolder(src._pHelpHolder.Reference()), _pwFrameOuter(src._pwFrameOuter.Reference()),
		_pVTypeOfOwner(src._pVTypeOfOwner) {}
	Function& operator=(const Function& src) = delete;
	// Move constructor/operator
	Function(Function&& src) = delete;
	Function& operator=(Function&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Function() = default;
public:
	Function* Clone() const { return new Function(*this); }
	static Function* CreateBlockFunction(
		Frame& frameOuter, const Symbol* pSymbol, const Expr_Block& exprOfBlock, bool holdFrameFlag);
	static Function* CreateDynamicFunction(
		const Symbol* pSymbol, const ValueList& valuesExpr, const Expr_Block& exprOfBlock);
public:
	void SetType(Type type) { _type = type; }
	bool IsTypeStatement() const { return _type == Type::Statement; }
	bool IsTypeFunction() const { return _type == Type::Function; }
	bool IsTypeConstructor() const { return _type == Type::Constructor; }
	bool IsTypeMethod() const { return _type == Type::Method; }
	bool IsClassMethod() const { return (GetFlags() & (Flag::OfClass | Flag::OfInstance)) == Flag::OfClass; }
	bool IsInstanceMethod() const { return (GetFlags() & (Flag::OfClass | Flag::OfInstance)) == Flag::OfInstance; }
	bool IsHybridMethod() const { return (GetFlags() & (Flag::OfClass | Flag::OfInstance)) == (Flag::OfClass | Flag::OfInstance); }
	void SetSymbol(const Symbol* pSymbol) { _pSymbol = pSymbol; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const char* GetName() const { return _pSymbol->GetName(); }
	String MakeFullName() const;
	DeclCallable& GetDeclCallable() { return *_pDeclCallable; }
	const DeclCallable& GetDeclCallable() const { return *_pDeclCallable; }
	void SetFrameOuter(Frame& frameOuter) {
		if (!_pwFrameOuter) _pwFrameOuter.reset(frameOuter.GetWeakPtr());
	}
	Frame* LockFrameOuter() const { return _pwFrameOuter? _pwFrameOuter->Lock() : nullptr; }
	bool HasFrameOuter() const { return !!_pwFrameOuter; }
	void SetVTypeOfOwner(VType& vtypeOfOwner) { _pVTypeOfOwner = &vtypeOfOwner; }
	const VType* GetVTypeOfOwner() const { return _pVTypeOfOwner; }
	void OrFlags(Flags flags) { GetDeclCallable().OrFlags(flags); }
public:
	void Declare(VType& vtypeResult, Flags flags) {
		GetDeclCallable().Declare(vtypeResult, flags);
	}
	void DeclareArg(const Symbol* pSymbol, const VType& vtype,
					const DeclArg::Occur& occur = DeclArg::Occur::Once,
					DeclArg::Flags flags = DeclArg::Flag::None, Expr* pExprDefault = nullptr) {
		GetDeclCallable().DeclareArg(pSymbol, vtype, occur, flags, pExprDefault);
	}
	void DeclareArg(const char* name, const VType& vtype,
					const DeclArg::Occur& occur = DeclArg::Occur::Once,
					DeclArg::Flags flags = DeclArg::Flag::None, Expr* pExprDefault = nullptr) {
		GetDeclCallable().DeclareArg(name, vtype, occur, flags, pExprDefault);
	}
	void DeclareAttrOpt(const Symbol* pSymbol) {
		GetDeclCallable().DeclareAttrOpt(pSymbol);
	}
	void DeclareAttrOpt(const char* name) {
		GetDeclCallable().DeclareAttrOpt(name);
	}
	void DeclareBlock(const Symbol* pSymbol, const DeclBlock::Occur& occur,
					  DeclBlock::Flags flags = DeclBlock::Flag::None) {
		GetDeclCallable().DeclareBlock(pSymbol, occur, flags);
	}
	void DeclareBlock(const char* name, const DeclBlock::Occur& occur,
					  DeclBlock::Flags flags = DeclBlock::Flag::None) {
		GetDeclCallable().DeclareBlock(name, occur, flags);
	}
	void DeclareBlock(const DeclBlock::Occur& occur, DeclBlock::Flags flags = DeclBlock::Flag::None) {
		GetDeclCallable().DeclareBlock(occur, flags);
	}
public:
	Flags GetFlags() const { return GetDeclCallable().GetFlags(); }
	bool IsSet(Flags flags) const { return GetDeclCallable().IsSet(flags); }
	HelpHolder& GetHelpHolder() { return *_pHelpHolder; }
	const HelpHolder& GetHelpHolder() const { return *_pHelpHolder; }
	void AddHelp(const Symbol* pLangCode, const char* doc) { _pHelpHolder->AddHelp(pLangCode, doc); }
	void AddHelp(const char* langCode, const char* doc) { _pHelpHolder->AddHelp(Symbol::Add(langCode), doc); }
	void LinkHelp(VType& vtype, const Symbol* pSymbol);
	void Exec(Processor& processor, Argument& argument) const;
	Value* Eval(Processor& processor, Argument& argument) const;
	Value* EvalEasy(Processor& processor, RefPtr<Value> pValueArg, DeclCallable::Flags flags = DeclCallable::Flag::None) const;
	Value* EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2,
						DeclCallable::Flags flags = DeclCallable::Flag::None) const;
	Value* EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2,
						RefPtr<Value> pValueArg3, DeclCallable::Flags flags = DeclCallable::Flag::None) const;
	Value* EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2,
						RefPtr<Value> pValueArg3, RefPtr<Value> pValueArg4, DeclCallable::Flags flags = DeclCallable::Flag::None) const;
	void Call(Processor& processor, Argument& argument) const;
	void Compose(Composer& composer, Expr_Caller& exprCaller) const;
	void PresentHelp(Processor& processor, const Symbol* pLangCode) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Function& function) const { return this == &function; }
	bool IsEqualTo(const Function& function) const { return IsIdentical(function); }
	bool IsLessThan(const Function& function) const { return this < &function; }
public:
	// Virtual functions
	virtual bool IsEmpty() const { return false; }
	virtual bool IsCustom() const { return false; }
	virtual const Expr& GetExprBody() const { return *Expr::Empty; }
	virtual const PUnit* GetPUnitBody() const { return nullptr; }
	virtual void DoExec(Processor& processor, Argument& argument) const;
	virtual Value* DoEval(Processor& processor, Argument& argument) const { return Value::nil(); }
	virtual void DoCompose(Composer& composer, Expr_Caller& exprCaller) const {}
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Constructor : public Function {
public:
	// Referable declaration
	Gurax_DeclareReferable(Constructor);
public:
	static RefPtr<Constructor> Empty;
public:
	static void Bootup();
public:
	// Constructor
	Constructor(DeclCallable::Flags flags) : Function(Type::Constructor, flags) {}		
	Constructor(const Symbol* pSymbol, DeclCallable* pDeclCallable) : Function(Type::Constructor, pSymbol, pDeclCallable) {}		
	Constructor(const char* name, DeclCallable::Flags flags) : Function(Type::Constructor, name, flags) {}		
	// Copy constructor/operator
	Constructor(const Constructor& src) = delete;
	Constructor& operator=(const Constructor& src) = delete;
	// Move constructor/operator
	Constructor(Constructor&& src) = delete;
	Constructor& operator=(Constructor&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Constructor() = default;
public:
	virtual bool GatherPropValue(ValueOwner& valueOwner, Value& valueThis) const { return false; }
};

}

#endif
