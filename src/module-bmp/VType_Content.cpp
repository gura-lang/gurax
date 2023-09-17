//==============================================================================
// VType_Content.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(bmp.Content, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(bmp.Content, `en)}

${help.ComposeMethodHelp(bmp.Content, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// bmp.Content(stream:Stream) {block?}
Gurax_DeclareConstructor(Content)
{
	Declare(VTYPE_Content, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `bmp.Content` instance.
)""");
}

Gurax_ImplementConstructor(Content)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Content> pContent(new Content());
	if (!pContent->Read(stream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Content(pContent.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// bmp.Content#Write(stream:Stream:w):reduce
Gurax_DeclareMethod(Content, Write)
{
	Declare(VTYPE_Content, Flag::Reduce);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Content, Write)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	if (!valueThis.GetContent().Write(stream)) return Value::nil();
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// bmp.Content#bfh
Gurax_DeclareProperty_R(Content, bfh)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The structure data of BitmapFileHeader.
)""");
}

Gurax_ImplementPropertyGetter(Content, bfh)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_BitmapFileHeader(valueThis.GetContent().Reference());
}

// bmp.Content#bih
Gurax_DeclareProperty_R(Content, bih)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The structure data of BitmapInfoHeader.
)""");
}

Gurax_ImplementPropertyGetter(Content, bih)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_BitmapInfoHeader(valueThis.GetContent().Reference());
}

// bmp.Content#rawImage
Gurax_DeclareProperty_R(Content, rawImage)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
`Pointer` pointed at the raw image data.
)""");
}

Gurax_ImplementPropertyGetter(Content, rawImage)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Memory* pMemory = valueThis.GetContent().GetMemory();
	if (!pMemory) return Value::nil();
	return new Value_Pointer(new Pointer_Memory(pMemory->Reference(), Pointer::ElemType::UInt8));
}

//------------------------------------------------------------------------------
// VType_Content
//------------------------------------------------------------------------------
VType_Content VTYPE_Content("Content");

void VType_Content::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Content));
	// Assignment of method
	Assign(Gurax_CreateMethod(Content, Write));
	// Assignment of property
	Assign(Gurax_CreateProperty(Content, bfh));
	Assign(Gurax_CreateProperty(Content, bih));
	Assign(Gurax_CreateProperty(Content, rawImage));
}

//------------------------------------------------------------------------------
// Value_Content
//------------------------------------------------------------------------------
VType& Value_Content::vtype = VTYPE_Content;

String Value_Content::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetContent().ToString(ss));
}

Gurax_EndModuleScope(bmp)
