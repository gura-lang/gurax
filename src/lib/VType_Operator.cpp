//==============================================================================
// VType_Operator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Operator, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Operator, `en)}

${help.ComposeMethodHelp(Operator, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of class method
//-----------------------------------------------------------------------------
// Operator.Binary(symbol:Symbol)
Gurax_DeclareClassMethod(Operator, Binary)
{
	Declare(VTYPE_Operator, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Creates an Operator instance of binary one.
)**");
}

Gurax_ImplementClassMethod(Operator, Binary)
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	Operator* pOp = Operator::LookupBinary(pSymbol);
	if (!pOp) {
		Error::Issue(ErrorType::SymbolError, "unknown binary operator: %s", pSymbol->GetName());
		return Value::nil();
	}
	return new Value_Operator(pOp);
}

// Operator.Math(symbol:Symbol)
Gurax_DeclareClassMethod(Operator, Math)
{
	Declare(VTYPE_Operator, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Creates an Operator instance of mathematical one.
)**");
}

Gurax_ImplementClassMethod(Operator, Math)
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	Operator* pOp = Operator::LookupMath(pSymbol);
	if (!pOp) {
		Error::Issue(ErrorType::SymbolError, "unknown mathematical operator: %s", pSymbol->GetName());
		return Value::nil();
	}
	return new Value_Operator(pOp);
}

// Operator.Unary(symbol:Symbol)
Gurax_DeclareClassMethod(Operator, Unary)
{
	Declare(VTYPE_Operator, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Creates an Operator instance of unary one.
)**");
}

Gurax_ImplementClassMethod(Operator, Unary)
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	Operator* pOp = Operator::LookupUnary(pSymbol);
	if (!pOp) {
		Error::Issue(ErrorType::SymbolError, "unknown unary operator: %s", pSymbol->GetName());
		return Value::nil();
	}
	return new Value_Operator(pOp);
}

// Operator.UnaryPost(symbol:Symbol)
Gurax_DeclareClassMethod(Operator, UnaryPost)
{
	Declare(VTYPE_Operator, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Creates an Operator instance of unary-post one.
)**");
}

Gurax_ImplementClassMethod(Operator, UnaryPost)
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	Operator* pOp = Operator::LookupUnaryPost(pSymbol);
	if (!pOp) {
		Error::Issue(ErrorType::SymbolError, "unknown unary-post operator: %s", pSymbol->GetName());
		return Value::nil();
	}
	return new Value_Operator(pOp);
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Operator#Assign(args as Any) as void
Gurax_DeclareMethod(Operator, Assign)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::OnceOrMore, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethod(Operator, Assign)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Operator& op = valueThis.GetOperator();
	ArgPicker args(argument);
	const ValueList& args_ = args.PickList();
	// Function body
	if (op.IsUnary() || op.IsUnaryPost() || op.IsMathUnary()) {
		// Operator#Assign(vtype as VType, funct as Any) as void
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("vtype", VTYPE_VType);
			pDeclCallable->DeclareArg("funct", VTYPE_Any);
		}
		RefPtr<Argument> pArgument(new Argument(processor, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor, args_)) return Value::nil();
		ArgPicker args(*pArgument);
		VType& vtype = args.Pick<Value_VType>().GetVTypeThis();
		Value& valueFunct = args.PickValue();
		op.AssignEntry(vtype, new OpEntryCustom_Unary(valueFunct.Reference()));
		return Value::nil();
	} else {
		// Operator#Assign(vtypeL as VType, vtypeR as VType, funct as Any) as void
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("vtypeL", VTYPE_VType);
			pDeclCallable->DeclareArg("vtypeR", VTYPE_VType);
			pDeclCallable->DeclareArg("funct", VTYPE_Any);
		}
		RefPtr<Argument> pArgument(new Argument(processor, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor, args_)) return Value::nil();
		ArgPicker args(*pArgument);
		VType& vtypeL = args.Pick<Value_VType>().GetVTypeThis();
		VType& vtypeR = args.Pick<Value_VType>().GetVTypeThis();
		Value& valueFunct = args.PickValue();
		op.AssignEntry(vtypeL, vtypeR, new OpEntryCustom_Binary(valueFunct.Reference()));
		return Value::nil();
	}
}

// Operator#IsBinary()
Gurax_DeclareMethod(Operator, IsBinary)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp("en", u8R"**(
Returns `true` if the operator is a binary one.
)**");
}

Gurax_ImplementMethod(Operator, IsBinary)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Operator& op = valueThis.GetOperator();
	// Function body
	return new Value_Bool(op.IsBinary());
}

// Operator#IsUnary()
Gurax_DeclareMethod(Operator, IsUnary)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp("en", u8R"**(
Returns `true` if the operator is a unary one.
)**");
}

Gurax_ImplementMethod(Operator, IsUnary)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Operator& op = valueThis.GetOperator();
	// Function body
	return new Value_Bool(op.IsUnary());
}

// Operator#IsUnaryPost()
Gurax_DeclareMethod(Operator, IsUnaryPost)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp("en", u8R"**(
Returns `true` if the operator is a unary-post one.
)**");
}

Gurax_ImplementMethod(Operator, IsUnaryPost)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Operator& op = valueThis.GetOperator();
	// Function body
	return new Value_Bool(op.IsUnaryPost());
}

// Operator#IsMath()
Gurax_DeclareMethod(Operator, IsMath)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp("en", u8R"**(
Returns `true` if the operator is a mathematics one.
)**");
}

Gurax_ImplementMethod(Operator, IsMath)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Operator& op = valueThis.GetOperator();
	// Function body
	return new Value_Bool(op.IsMath());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Operator#name
Gurax_DeclareProperty_R(Operator, name)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(
Name of the operator.
)**");
}

Gurax_ImplementPropertyGetter(Operator, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetOperator().GetName());
}

// Operator#style
Gurax_DeclareProperty_R(Operator, style)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp("en", u8R"**(
A symbol of the operator's style.
)**");
}

Gurax_ImplementPropertyGetter(Operator, style)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetOperator().GetStyleAsSymbol());
}

// Operator#symbol
Gurax_DeclareProperty_R(Operator, symbol)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp("en", u8R"**(
Symbol of the operator.
)**");
}

Gurax_ImplementPropertyGetter(Operator, symbol)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetOperator().GetSymbol());
}

// Operator#typeId
Gurax_DeclareProperty_R(Operator, typeId)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(
Type of the operator.
)**");
}

Gurax_ImplementPropertyGetter(Operator, typeId)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(static_cast<int>(valueThis.GetOperator().GetType()));
}

//------------------------------------------------------------------------------
// VType_Operator
//------------------------------------------------------------------------------
VType_Operator VTYPE_Operator("Operator");

void VType_Operator::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of class method
	Assign(Gurax_CreateMethod(Operator, Binary));
	Assign(Gurax_CreateMethod(Operator, Math));
	Assign(Gurax_CreateMethod(Operator, Unary));
	Assign(Gurax_CreateMethod(Operator, UnaryPost));
	// Assignment of method
	Assign(Gurax_CreateMethod(Operator, Assign));
	Assign(Gurax_CreateMethod(Operator, IsBinary));
	Assign(Gurax_CreateMethod(Operator, IsMath));
	Assign(Gurax_CreateMethod(Operator, IsUnary));
	Assign(Gurax_CreateMethod(Operator, IsUnaryPost));
	// Assignment of property
	Assign(Gurax_CreateProperty(Operator, name));
	Assign(Gurax_CreateProperty(Operator, style));
	Assign(Gurax_CreateProperty(Operator, symbol));
	Assign(Gurax_CreateProperty(Operator, typeId));
}

//------------------------------------------------------------------------------
// Value_Operator
//------------------------------------------------------------------------------
VType& Value_Operator::vtype = VTYPE_Operator;

String Value_Operator::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetOperator().ToString(StringStyle::Cram));
}

const DeclCallable* Value_Operator::GetDeclCallable()
{
	return &GetOperator().GetDeclCallable();
}

Value* Value_Operator::DoEval(Processor& processor, Argument& argument) const
{
	ArgPicker args(argument);
	Value& value = args.PickValue();
	if (args.IsValid()) {
		Value& valueRight = args.PickValue();
		return GetOperator().EvalBinary(processor, value, valueRight);
	} else {
		return GetOperator().EvalUnary(processor, value);
	}
}

}
