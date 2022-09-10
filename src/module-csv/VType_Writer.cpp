//==============================================================================
// VType_Writer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(csv)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// csv.Writer(stream:w as Stream) {block?}
Gurax_DeclareConstructor(Writer)
{
	Declare(VTYPE_Writer, Flag::None);
	DeclareArg("stream", VTYPE_Stream, DeclArg::Occur::Once, DeclArg::Flag::StreamW);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `csv.Writer` instance.");
}

Gurax_ImplementConstructor(Writer)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Writer> pWriter(new Writer(stream.Reference()));
	return argument.ReturnValue(processor, new Value_Writer(pWriter.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// csv.Writer#WriteLine(fields+)
Gurax_DeclareMethod(Writer, WriteLine)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("fields", VTYPE_Any, ArgOccur::OnceOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Writer, WriteLine)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const ValueList& valList = args.PickList();
	// Function body
	valueThis.GetWriter().PutValues(valList, true);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// csv.Writer#formatForNumber
Gurax_DeclareProperty_RW(Writer, formatForNumber)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Format string for converting a Number.");
}

Gurax_ImplementPropertyGetter(Writer, formatForNumber)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetWriter().GetFormatForNumber());
}

Gurax_ImplementPropertySetter(Writer, formatForNumber)
{
	auto& valueThis = GetValueThis(valueTarget);
	const char* formatToSet = Value_String::GetString(value);
	if (!Formatter().VerifyFormat(formatToSet, Formatter::VaType::Float, Formatter::VaType::None)) return;
	valueThis.GetWriter().SetFormatForNumber(formatToSet);
}

//------------------------------------------------------------------------------
// VType_Writer
//------------------------------------------------------------------------------
VType_Writer VTYPE_Writer("Writer");

void VType_Writer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Writer));
	// Assignment of method
	Assign(Gurax_CreateMethod(Writer, WriteLine));
	// Assignment of property
	Assign(Gurax_CreateProperty(Writer, formatForNumber));
}

//------------------------------------------------------------------------------
// Value_Writer
//------------------------------------------------------------------------------
VType& Value_Writer::vtype = VTYPE_Writer;

String Value_Writer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetWriter().ToString(ss));
}

Gurax_EndModuleScope(csv)
