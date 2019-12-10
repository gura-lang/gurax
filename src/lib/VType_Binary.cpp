//==============================================================================
// VType_Binary.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

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
Gurax_DeclareConstructor(Binary)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Binary` instance.");
}

Gurax_ImplementConstructor(Binary)
{
	// Function body
	RefPtr<BinaryReferable> pBinary(new BinaryReferable());
	return argument.ReturnValue(processor, new Value_Binary(pBinary.release()));
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Binary#bytes
Gurax_DeclareProperty_R(Binary, bytes)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The size of the binary in bytes.");
}

Gurax_ImplementPropertyGetter(Binary, bytes)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BinaryReferable& binary = valueThis.GetBinaryReferable();
	return new Value_Number(binary.GetBinary().size());
}

// Binary#reader
Gurax_DeclareProperty_R(Binary, reader)
{
	Declare(VTYPE_Stream, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A `Stream` instance that reads data from the `Binary`.");
}

Gurax_ImplementPropertyGetter(Binary, reader)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BinaryReferable& binary = valueThis.GetBinaryReferable();
	size_t offset = 0;
	return new Value_Stream(new Stream_Binary(binary.Reference(), offset));
}

// Binary#writer
Gurax_DeclareProperty_R(Binary, writer)
{
	Declare(VTYPE_Stream, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A `Stream` instance that writes data into the `Binary`.");
}

Gurax_ImplementPropertyGetter(Binary, writer)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BinaryReferable& binary = valueThis.GetBinaryReferable();
	size_t offset = binary.GetBinary().size();
	return new Value_Stream(new Stream_Binary(binary.Reference(), offset));
}

//------------------------------------------------------------------------------
// VType_Binary
//------------------------------------------------------------------------------
VType_Binary VTYPE_Binary("Binary");

void VType_Binary::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaretion of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Binary));
	// Assignment of property
	Assign(Gurax_CreateProperty(Binary, bytes));
	Assign(Gurax_CreateProperty(Binary, reader));
	Assign(Gurax_CreateProperty(Binary, writer));
}

//------------------------------------------------------------------------------
// Value_Binary
//------------------------------------------------------------------------------
VType& Value_Binary::vtype = VTYPE_Binary;

}
