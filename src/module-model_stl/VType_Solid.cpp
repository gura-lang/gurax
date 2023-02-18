//==============================================================================
// VType_Solid.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_stl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.stl.Solid, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.stl.Solid, `en)}

${help.ComposeMethodHelp(model.stl.Solid, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.stl.Solid(stream as Stream) {block?}
Gurax_DeclareConstructor(Solid)
{
	Declare(VTYPE_Solid, Flag::None);
	DeclareArg("stream", VTYPE_Stream, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `model.stl.Solid` instance.
)**");
}

Gurax_ImplementConstructor(Solid)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Solid> pSolid(new Solid(stream.Reference()));
	if (!pSolid->ReadHeader()) return Value::nil();
	return argument.ReturnValue(processor, new Value_Solid(pSolid.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.stl.Solid#EachFace() {block?}
Gurax_DeclareMethod(Solid, EachFace)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that returns `Face` instances that provide coordinates of triangles.
)**");
}

Gurax_ImplementMethod(Solid, EachFace)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return argument.ReturnIterator(processor, valueThis.GetSolid().EachFace());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// model.stl.Solid#name
Gurax_DeclareProperty_R(Solid, name)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Solid, name)
{
	Solid& solid = GetValueThis(valueTarget).GetSolid();
	if (solid.GetBinaryFlag()) return Value::nil();
	return new Value_String(solid.GetName());
}

// model.stl.Solid#header
Gurax_DeclareProperty_R(Solid, header)
{
	Declare(VTYPE_Binary, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Solid, header)
{
	Solid& solid = GetValueThis(valueTarget).GetSolid();
	if (!solid.GetBinaryFlag()) return Value::nil();
	return new Value_Binary(solid.GetHeader());
}

//------------------------------------------------------------------------------
// VType_Solid
//------------------------------------------------------------------------------
VType_Solid VTYPE_Solid("Solid");

void VType_Solid::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Solid));
	// Assignment of method
	Assign(Gurax_CreateMethod(Solid, EachFace));
	// Assignment of property
	Assign(Gurax_CreateProperty(Solid, name));
	Assign(Gurax_CreateProperty(Solid, header));
}

//------------------------------------------------------------------------------
// Value_Solid
//------------------------------------------------------------------------------
VType& Value_Solid::vtype = VTYPE_Solid;

String Value_Solid::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetSolid().ToString(ss));
}

Gurax_EndModuleScope(model_stl)
