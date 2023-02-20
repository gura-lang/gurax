//==============================================================================
// VType_Face.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Face, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Face, `en)}

${help.ComposeMethodHelp(model.obj.Face, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Face#GetV(idx as Number)
Gurax_DeclareMethod(Face, GetV)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Face, GetV)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	int iIndex = args.PickNumber<int>();
	// Function body
	const Vertex4* pV = valueThis.GetFace().GetV(valueThis.GetContent(), iIndex);
	if (pV) return new Value_Vertex4(pV->Reference());
	return Value::nil();
}

// model.obj.Face#GetVt(idx as Number)
Gurax_DeclareMethod(Face, GetVt)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Face, GetVt)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	int iIndex = args.PickNumber<int>();
	// Function body
	const Vertex3* pVt = valueThis.GetFace().GetVt(valueThis.GetContent(), iIndex);
	if (pVt) return new Value_Vertex3(pVt->Reference());
	return Value::nil();
}

// model.obj.Face#GetVn(idx as Number)
Gurax_DeclareMethod(Face, GetVn)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Face, GetVn)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	int iIndex = args.PickNumber<int>();
	// Function body
	const Vertex3* pVn = valueThis.GetFace().GetVn(valueThis.GetContent(), iIndex);
	if (pVn) return new Value_Vertex3(pVn->Reference());
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// model.obj.Face#propSkeleton
Gurax_DeclareProperty_R(Face, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Face, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Face
//------------------------------------------------------------------------------
VType_Face VTYPE_Face("Face");

void VType_Face::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Face, GetV));
	Assign(Gurax_CreateMethod(Face, GetVt));
	Assign(Gurax_CreateMethod(Face, GetVn));
	// Assignment of property
	Assign(Gurax_CreateProperty(Face, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Face
//------------------------------------------------------------------------------
VType& Value_Face::vtype = VTYPE_Face;

String Value_Face::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetFace().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
