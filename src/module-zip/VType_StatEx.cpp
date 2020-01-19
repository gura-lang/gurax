//==============================================================================
// VType_Stat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(zip)

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
// Implementation of property
//------------------------------------------------------------------------------
// zip.Stat#compressionMethod
Gurax_DeclareProperty_R(StatEx, compressionMethod)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A symbol representing the compression method.");
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
	AddHelp(
		Gurax_Symbol(en),
		"File comment.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Compressed size in bytes.");
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
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Stat, Flag::Immutable);
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
