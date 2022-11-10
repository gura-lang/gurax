//==============================================================================
// VType_Help.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Help, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Help, `en)}

${help.ComposeMethodHelp(Help, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Help(value, lang? as Symbol) {block?}
Gurax_DeclareConstructor(Help)
{
	Declare(VTYPE_Help, Flag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("lang", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Help` instance.");
}

Gurax_ImplementConstructor(Help)
{
	// Arguments
	ArgPicker args(argument);
	const Value& value = args.PickValue();
	const Symbol* pLangCode = args.IsValid()? args.PickSymbol() : nullptr;
	// Function body
	HelpHolder* pHelpHolder = value.GetHelpHolder();
	if (!pHelpHolder) {
		Error::Issue(ErrorType::ValueError,
					 "value type '%s' doesn't have help", value.GetVTypeCustom().MakeFullName().c_str());
		return Value::nil();
	}
	const Help* pHelp = nullptr;
	if (pLangCode) {
		pHelp = pHelpHolder->LookupLoose(pLangCode);
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
	const Help& help = GetValueThis(valueTarget).GetHelp();
	return new Value_String(help.GetDocReferable().Reference());
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

// Help#tmplDoc
Gurax_DeclareProperty_R(Help, tmplDoc)
{
	Declare(VTYPE_Template, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Template object created from the help text.");
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
	HelpHolder* pHelpHolder = valueL.GetHelpHolder();
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
	HelpHolder* pHelpHolder = valueL.GetHelpHolder();
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
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
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

}
