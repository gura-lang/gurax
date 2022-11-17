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

${help.ComposePropertyHelp(csv.Writer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(csv.Writer, `en)}

${help.ComposeMethodHelp(csv.Writer, `en)}
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `csv.Writer` instance.
)**");
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
// csv.Writer#ResetFormatForNumber():reduce
Gurax_DeclareMethod(Writer, ResetFormatForNumber)
{
	Declare(VTYPE_Writer, Flag::Reduce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Resets foratForNumber property to its default value.
)**");
}

Gurax_ImplementMethod(Writer, ResetFormatForNumber)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetWriter().ResetFormatForNumber();
	return valueThis.Reference();
}

// csv.Writer#WriteLine(values*):reduce
Gurax_DeclareMethod(Writer, WriteLine)
{
	Declare(VTYPE_Writer, Flag::Reduce);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Writes a line of values in the CSV format.
)**");
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
	return valueThis.Reference();
}

// csv.Writer#WriteLines(iterator as Iterator):reduce
Gurax_DeclareMethod(Writer, WriteLines)
{
	Declare(VTYPE_Writer, Flag::Reduce);
	DeclareArg("iterator", VTYPE_Iterator, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Writes lines of values in the CSV format.
)**");
}

Gurax_ImplementMethod(Writer, WriteLines)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Iterator& iterator = args.PickIterator();
	if (!iterator.MustBeFinite()) return Value::nil();
	// Function body
	for (;;) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) {
			if (Error::IsIssued()) return Value::nil();
			break;
		}
		if (pValue->IsType(VTYPE_List)) {
			const ValueOwner& valOwner = Value_List::GetValueOwner(*pValue);
			valueThis.GetWriter().PutValues(valOwner, true);
		} else if (pValue->IsType(VTYPE_Tuple)) {
			const ValueOwner& valOwner = Value_Tuple::GetValueOwner(*pValue);
			valueThis.GetWriter().PutValues(valOwner, true);
		} else {
			Error::Issue(ErrorType::TypeError, "must be a Tuple value");
			return false;
		}
	}
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// csv.Writer#formatForNumber
Gurax_DeclareProperty_RW(Writer, formatForNumber)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Format string for converting a Number.
)**");
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
	if (!Formatter().VerifyFormat(formatToSet, Formatter::VaType::Int, Formatter::VaType::None) &&
		!Formatter().VerifyFormat(formatToSet, Formatter::VaType::Float, Formatter::VaType::None)) return;
	valueThis.GetWriter().SetFormatForNumber(formatToSet);
}

//------------------------------------------------------------------------------
// VType_Writer
//------------------------------------------------------------------------------
VType_Writer VTYPE_Writer("Writer");

void VType_Writer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Writer));
	// Assignment of method
	Assign(Gurax_CreateMethod(Writer, ResetFormatForNumber));
	Assign(Gurax_CreateMethod(Writer, WriteLine));
	Assign(Gurax_CreateMethod(Writer, WriteLines));
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
