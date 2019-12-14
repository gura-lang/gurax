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
	RefPtr<BinaryReferable> pBinary(new BinaryReferable(true));
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

// Binary#p
Gurax_DeclareProperty_R(Binary, p)
{
	Declare(VTYPE_Pointer, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns a `pointer` instance that accesses the binary.\n"
		"This result is equivalent to that of calling the method `binary#pointer()`");
}

Gurax_ImplementPropertyGetter(Binary, p)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Pointer(new Pointer_Binary(0, valueThis.Reference()));
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
	return new Value_Stream(new Stream_Binary(Stream::Flag::Readable, binary.Reference(), offset));
}

// Binary#writable
Gurax_DeclareProperty_R(Binary, writable)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the binary data can be modified.\n");
}

Gurax_ImplementPropertyGetter(Binary, writable)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetBinary().IsWritable());
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
	if (!binary.GetBinary().CheckWritable()) return Value::nil();
	size_t offset = binary.GetBinary().size();
	return new Value_Stream(new Stream_Binary(Stream::Flag::Writable, binary.Reference(), offset));
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
	Assign(Gurax_CreateProperty(Binary, p));
	Assign(Gurax_CreateProperty(Binary, reader));
	Assign(Gurax_CreateProperty(Binary, writable));
	Assign(Gurax_CreateProperty(Binary, writer));
}

//------------------------------------------------------------------------------
// Value_Binary
//------------------------------------------------------------------------------
VType& Value_Binary::vtype = VTYPE_Binary;

String Value_Binary::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%dbytes", _pBinary->GetBinary().size());
	str += _pBinary->GetBinary().IsWritable()? "writrable" : "constant";
	str += ">";
	return str;
}

String Value_Binary::ToStringDetail(const StringStyle& ss) const
{
	String str = "b";
	str += _pBinary->GetBinary().MakeQuoted(true);
	return str;
}

}
