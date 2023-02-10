//==============================================================================
// VType_Vertex.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Vertex, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Vertex, `en)}

${help.ComposeMethodHelp(Vertex, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Vertex(x? as Number, y? as Number, z? as Number) {block?}
Gurax_DeclareConstructor(Vertex)
{
	Declare(VTYPE_Vertex, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("z", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Vertex` instance.
)**");
}

Gurax_ImplementConstructor(Vertex)
{
	// Arguments
	ArgPicker args(argument);
	Double x = args.IsValid()? args.PickNumber<Double>() : 0;
	Double y = args.IsValid()? args.PickNumber<Double>() : 0;
	Double z = args.IsValid()? args.PickNumber<Double>() : 0;
	// Function body
	return argument.ReturnValue(processor, new Value_Vertex(Vertex(x, y, z)));
}

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------
// Vertex.Normal(v1 as Vertex, v2 as Vertex, v3 as Vertex):[unit] {block?}
Gurax_DeclareClassMethod(Vertex, Normal)
{
	Declare(VTYPE_Vertex, Flag::Map);
	DeclareArg("v1", VTYPE_Vertex, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v2", VTYPE_Vertex, ArgOccur::Once, ArgFlag::None);
	DeclareArg("v3", VTYPE_Vertex, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(unit));
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementClassMethod(Vertex, Normal)
{
	// Arguments
	ArgPicker args(argument);
	const Vertex& v1 = args.Pick<Value_Vertex>().GetVertex();
	const Vertex& v2 = args.Pick<Value_Vertex>().GetVertex();
	const Vertex& v3 = args.Pick<Value_Vertex>().GetVertex();
	bool unitFlag = argument.IsSet(Gurax_Symbol(unit));
	// Function body
	return argument.ReturnValue(processor, new Value_Vertex(Vertex::Normal(v1, v2, v3, unitFlag)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Vertex#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Vertex, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Vertex, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Vertex#x
Gurax_DeclareProperty_RW(Vertex, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Vertex, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetVertex().x);
}

Gurax_ImplementPropertySetter(Vertex, x)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetVertex().x = Value_Number::GetNumber<Double>(value);
}

// Vertex#y
Gurax_DeclareProperty_RW(Vertex, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Vertex, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetVertex().y);
}

Gurax_ImplementPropertySetter(Vertex, y)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetVertex().y = Value_Number::GetNumber<Double>(value);
}

// Vertex#z
Gurax_DeclareProperty_RW(Vertex, z)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Vertex, z)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetVertex().z);
}

Gurax_ImplementPropertySetter(Vertex, z)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetVertex().z = Value_Number::GetNumber<Double>(value);
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// -Vertex
Gurax_ImplementOpUnary(Neg, Vertex)
{
	const Vertex& v = Value_Vertex::GetVertex(value);
	return new Value_Vertex(Vertex::Neg(v));
}

// Vertex + Vertex
Gurax_ImplementOpBinary(Add, Vertex, Vertex)
{
	const Vertex& v1 = Value_Vertex::GetVertex(valueL);
	const Vertex& v2 = Value_Vertex::GetVertex(valueR);
	return new Value_Vertex(Vertex::Add(v1, v2));
}

// Vertex - Vertex
Gurax_ImplementOpBinary(Sub, Vertex, Vertex)
{
	const Vertex& v1 = Value_Vertex::GetVertex(valueL);
	const Vertex& v2 = Value_Vertex::GetVertex(valueR);
	return new Value_Vertex(Vertex::Sub(v1, v2));
}

// Vertex * Number
Gurax_ImplementOpBinary(Mul, Vertex, Number)
{
	const Vertex& v = Value_Vertex::GetVertex(valueL);
	Double num = Value_Number::GetNumber<Double>(valueR);
	return new Value_Vertex(Vertex::Mul(v, num));
}

// Number * Vertex
Gurax_ImplementOpBinary(Mul, Number, Vertex)
{
	Double num = Value_Number::GetNumber<Double>(valueL);
	const Vertex& v = Value_Vertex::GetVertex(valueR);
	return new Value_Vertex(Vertex::Mul(v, num));
}

// Vertex / Number
Gurax_ImplementOpBinary(Div, Vertex, Number)
{
	const Vertex& v = Value_Vertex::GetVertex(valueL);
	Double num = Value_Number::GetNumber<Double>(valueR);
	return new Value_Vertex(Vertex::Div(v, num));
}

// Vertex |.| Vertex
Gurax_ImplementOpBinary(Dot, Vertex, Vertex)
{
	const Vertex& v1 = Value_Vertex::GetVertex(valueL);
	const Vertex& v2 = Value_Vertex::GetVertex(valueR);
	return new Value_Number(Vertex::Dot(v1, v2));
}

// Vertex |^| Vertex
Gurax_ImplementOpBinary(Cross, Vertex, Vertex)
{
	const Vertex& v1 = Value_Vertex::GetVertex(valueL);
	const Vertex& v2 = Value_Vertex::GetVertex(valueR);
	return new Value_Vertex(Vertex::Cross(v1, v2));
}


//------------------------------------------------------------------------------
// VType_Vertex
//------------------------------------------------------------------------------
VType_Vertex VTYPE_Vertex("Vertex");

void VType_Vertex::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Vertex));
	// Assignment of class method
	Assign(Gurax_CreateMethod(Vertex, Normal));
	// Assignment of method
	Assign(Gurax_CreateMethod(Vertex, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Vertex, x));
	Assign(Gurax_CreateProperty(Vertex, y));
	Assign(Gurax_CreateProperty(Vertex, z));
	// Assignment of operator
	Gurax_AssignOpUnary(Neg,	Vertex);
	Gurax_AssignOpBinary(Add,	Vertex, Vertex);
	Gurax_AssignOpBinary(Sub,	Vertex, Vertex);
	Gurax_AssignOpBinary(Mul,	Vertex, Number);
	Gurax_AssignOpBinary(Mul,	Number, Vertex);
	Gurax_AssignOpBinary(Div,	Vertex, Number);
	Gurax_AssignOpBinary(Dot,	Vertex, Vertex);
	Gurax_AssignOpBinary(Cross,	Vertex, Vertex);
}

//------------------------------------------------------------------------------
// Value_Vertex
//------------------------------------------------------------------------------
VType& Value_Vertex::vtype = VTYPE_Vertex;

String Value_Vertex::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetVertex().ToString(ss));
}

}