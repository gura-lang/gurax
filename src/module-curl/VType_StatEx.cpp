//==============================================================================
// VType_Stat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(curl.StatEx, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(curl.StatEx, `en)}

${help.ComposeMethodHelp(curl.StatEx, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// zip.Stat#PrintCentralFileHeader():void
Gurax_DeclareMethod(StatEx, PrintCentralFileHeader)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Prints the field values in the Central File Header.
)""");
}

Gurax_ImplementMethod(StatEx, PrintCentralFileHeader)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetStatEx().GetCentralFileHeader().Print(*Stream::COut);
	return Value::nil();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// zip.Stat#compressionMethod
Gurax_DeclareProperty_R(StatEx, compressionMethod)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
A symbol representing the compression method.
)""");
}

Gurax_ImplementPropertyGetter(StatEx, compressionMethod)
{
	auto& valueThis = GetValueThis(valueTarget);
	UInt16 compressionMethod = valueThis.GetStatEx().GetCentralFileHeader().GetCompressionMethod();
	return new Value_Symbol(CompressionMethodToSymbol(compressionMethod));
}

// zip.Stat#fileComment
Gurax_DeclareProperty_R(StatEx, fileComment)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
File comment.
)""");
}

Gurax_ImplementPropertyGetter(StatEx, fileComment)
{
	auto& valueThis = GetValueThis(valueTarget);
	const char* fileComment = valueThis.GetStatEx().GetCentralFileHeader().GetFileComment();
	return new Value_String(fileComment);
}

// zip.Stat#compressedSize
Gurax_DeclareProperty_R(StatEx, compressedSize)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Compressed size in bytes.
)""");
}

Gurax_ImplementPropertyGetter(StatEx, compressedSize)
{
	auto& valueThis = GetValueThis(valueTarget);
	size_t compressedSize = valueThis.GetStatEx().GetCentralFileHeader().GetCompressedSize();
	return new Value_Number(compressedSize);
}

//------------------------------------------------------------------------------
// VType_StatEx
//------------------------------------------------------------------------------
VType_StatEx VTYPE_StatEx("Stat");

void VType_StatEx::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Stat, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(StatEx, PrintCentralFileHeader));
	// Assignment of property
	Assign(Gurax_CreateProperty(StatEx, compressedSize));
	Assign(Gurax_CreateProperty(StatEx, compressionMethod));
	Assign(Gurax_CreateProperty(StatEx, fileComment));
}

//------------------------------------------------------------------------------
// Value_StatEx
//------------------------------------------------------------------------------
VType& Value_StatEx::vtype = VTYPE_StatEx;

Gurax_EndModuleScope(zip)
