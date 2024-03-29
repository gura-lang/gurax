﻿//==============================================================================
// VType_Help.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Help, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Help, `en)}

${help.ComposeMethodHelp(Help, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Help(value, lang? as Symbol):map:[class,raise] {block?}
Gurax_DeclareConstructor(Help)
{
	Declare(VTYPE_Help, Flag::Map);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("lang", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(class_));
	DeclareAttrOpt(Gurax_Symbol(raise));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Help` instance.
)""");
}

Gurax_ImplementConstructor(Help)
{
	// Arguments
	ArgPicker args(argument);
	const Value& value = args.PickValue();
	const Symbol* pLangCode = args.IsValid()? args.PickSymbol() : Gurax_Symbol(en);
	// Function body
	const HelpHolder* pHelpHolder = value.GetHelpHolder(argument.IsSet(Gurax_Symbol(class_)));
	if (!pHelpHolder) {
		Error::Issue(ErrorType::ValueError, "value type '%s' doesn't have help", value.GetVTypeCustom().MakeFullName().c_str());
		return Value::nil();
	}
	RefPtr<Value> pValueRtn(Value::nil());
	const Help* pHelp = pHelpHolder->LookupLoose(pLangCode);
	if (pHelp) {
		pValueRtn.reset(new Value_Help(pHelp->Clone()));
	} else if (argument.IsSet(Gurax_Symbol(raise))) {
		Error::Issue(ErrorType::ValueError, "no help in language `%s", pLangCode->GetName());
		return Value::nil();
	}
	return argument.ReturnValue(processor, pValueRtn.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Help#doc
Gurax_DeclareProperty_R(Help, doc)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Document text of the help.
)""");
}

Gurax_ImplementPropertyGetter(Help, doc)
{
	const Help& help = GetValueThis(valueTarget).GetHelp();
	return new Value_String(help.GetDocReferable().Reference());
}

// Help#lang
Gurax_DeclareProperty_R(Help, lang)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Language code of the help.
)""");
}

Gurax_ImplementPropertyGetter(Help, lang)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetHelp().GetLangCode());
}

// Help#tmplDoc
Gurax_DeclareProperty_R(Help, tmplDoc)
{
	Declare(VTYPE_Template, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Template object created from the help text.
)""");
}

Gurax_ImplementPropertyGetter(Help, tmplDoc)
{
	Help& help = GetValueThis(valueTarget).GetHelp();
	const Template* pTemplate = help.GetTmplDoc();
	if (!pTemplate) return Value::nil();
	return new Value_Template(pTemplate->Reference());
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// ?Any
Gurax_ImplementOpUnary(Question, Any)
{
	value.PresentHelp(processor, Gurax_Symbol(en));
	return Value::nil();
}

// Any %% String
Gurax_ImplementOpBinary(ModMod, Any, String)
{
	HelpHolder* pHelpHolder = valueL.GetHelpHolder(true);
	if (!pHelpHolder) {
		Error::Issue(ErrorType::ValueError,
				 "can't assign help to value type '%s'", valueL.GetVTypeCustom().MakeFullName().c_str());
		return Value::nil();
	}
	pHelpHolder->AddHelp(Gurax_Symbol(en), Value_String::GetString(valueR));
	return valueL.Reference();
}

// Any %% Help
Gurax_ImplementOpBinary(ModMod, Any, Help)
{
	HelpHolder* pHelpHolder = valueL.GetHelpHolder(true);
	if (!pHelpHolder) {
		Error::Issue(ErrorType::ValueError,
				 "can't assign help to value type '%s'", valueL.GetVTypeCustom().MakeFullName().c_str());
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
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Help));
	// Assignment of property
	Assign(Gurax_CreateProperty(Help, doc));
	Assign(Gurax_CreateProperty(Help, lang));
	Assign(Gurax_CreateProperty(Help, tmplDoc));
	// Assignment of operator
	Gurax_AssignOpUnary(Question, Any);
	Gurax_AssignOpBinary(ModMod, Any, String);
	Gurax_AssignOpBinary(ModMod, Any, Help);
}

//------------------------------------------------------------------------------
// Value_Help
//------------------------------------------------------------------------------
VType& Value_Help::vtype = VTYPE_Help;

String Value_Help::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetHelp().ToString(ss));
}

void Value_Help::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	String str;
	const Help& help = Value_Help::GetHelp(*this);
	str += help.GetDoc();
	if (!str.EndsWith('\n')) str += '\n';
	Basement::Inst.Present(processor, str.c_str());
}

}
