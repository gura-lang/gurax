//==============================================================================
// VType_Help.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Help(value, lang?:Symbol) {block?}
Gurax_DeclareFunction(Help)
{
	Declare(VTYPE_Help, Flag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("lang", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Help` instance.");
}

Gurax_ImplementFunction(Help)
{
	// Arguments
	ArgPicker args(argument);
	const Value& value = args.PickValue();
	const Symbol* pLangCode = args.IsValid()? args.PickSymbol() : nullptr;
	// Function body
	HelpHolder* pHelpHolder = value.GetHelpHolder();
	if (!pHelpHolder) {
		Error::Issue(ErrorType::ValueError,
					 "value type '%s' doesn't have help", value.GetVType().MakeFullName().c_str());
		return Value::nil();
	}
	const Help* pHelp = nullptr;
	if (pLangCode) {
		pHelp = pHelpHolder->Lookup(pLangCode);
		if (!pHelp) {
			Error::Issue(ErrorType::ValueError, "no help in language `%s", pLangCode->GetName());
			return Value::nil();
		}
	} else {
		pHelp = pHelpHolder->GetDefault();
		if (!pHelp) {
			Error::Issue(ErrorType::ValueError, "no help");
			return Value::nil();
		}
	}
	return argument.ReturnValue(processor, new Value_Help(pHelp->Clone()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Help#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Help, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Help, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Help#doc
Gurax_DeclareProperty_R(Help, doc)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Document text of the help.");
}

Gurax_ImplementPropertyGetter(Help, doc)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetHelp().GetDocReferable().Reference());
}

// Help#lang
Gurax_DeclareProperty_R(Help, lang)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Language code of the help.");
}

Gurax_ImplementPropertyGetter(Help, lang)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetHelp().GetLangCode());
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// ?Any
Gurax_ImplementOpUnary(Question, Any)
{
	value.PresentHelp(Gurax_Symbol(en));
	return Value::nil();
}

// Any %% String
Gurax_ImplementOpBinary(ModMod, Any, String)
{
	HelpHolder* pHelpHolder = valueL.GetHelpHolder();
	if (!pHelpHolder) {
		Error::Issue(ErrorType::ValueError,
				 "can't assign help to value type '%s'", valueL.GetVType().MakeFullName().c_str());
		return Value::nil();
	}
	pHelpHolder->AddHelp(Gurax_Symbol(en), Value_String::GetString(valueR));
	return valueL.Reference();
}

// Any %% Help
Gurax_ImplementOpBinary(ModMod, Any, Help)
{
	HelpHolder* pHelpHolder = valueL.GetHelpHolder();
	if (!pHelpHolder) {
		Error::Issue(ErrorType::ValueError,
				 "can't assign help to value type '%s'", valueL.GetVType().MakeFullName().c_str());
		return Value::nil();
	}
	pHelpHolder->AddHelp(Value_Help::GetHelp(valueR).Clone());
	return valueL.Reference();
}

//------------------------------------------------------------------------------
// VType_Help
//------------------------------------------------------------------------------
VType_Help VTYPE_Help("Help");

void VType_Help::DoPrepare(Frame& frameOuter)
{
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateFunction(Help));
	// Assignment of method
	Assign(Gurax_CreateMethod(Help, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Help, doc));
	Assign(Gurax_CreateProperty(Help, lang));
	// Assignment of operator
	Gurax_AssignOpUnary(Question, Any);
	Gurax_AssignOpBinary(ModMod, Any, String);
	Gurax_AssignOpBinary(ModMod, Any, Help);
}

//------------------------------------------------------------------------------
// Value_Help
//------------------------------------------------------------------------------
VType& Value_Help::vtype = VTYPE_Help;

}
