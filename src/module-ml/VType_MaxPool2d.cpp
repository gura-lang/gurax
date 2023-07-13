//==============================================================================
// VType_MaxPool2d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.MaxPool2d, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.MaxPool2d, `en)}

${help.ComposeMethodHelp(ml.MaxPool2d, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.MaxPool2d(nRowsKernel as Number, nColsKernel as Number, stride? as Number) {block?}
Gurax_DeclareConstructor(MaxPool2d)
{
	Declare(VTYPE_MaxPool2d, Flag::None);
	DeclareArg("nRowsKernel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nColsKernel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stride", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.MaxPool2d` instance.
)""");
}

Gurax_ImplementConstructor(MaxPool2d)
{
	// Arguments
	ArgPicker args(argument);
	size_t nRowsKernel = args.PickNumberPos<size_t>();
	size_t nColsKernel = args.PickNumberPos<size_t>();
	size_t stride = args.IsValid()? args.PickNumberPos<size_t>() : 1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<MaxPool2d> pMaxPool2d(new MaxPool2d(nRowsKernel, nColsKernel, stride));
	return argument.ReturnValue(processor, new Value_MaxPool2d(pMaxPool2d.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
#if 0
// ml.MaxPool2d#nRowsIn
Gurax_DeclareProperty_R(MaxPool2d, nRowsIn)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(MaxPool2d, nRowsIn)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetMaxPool2d().GetNRowsIn());
}

// ml.MaxPool2d#nColsIn
Gurax_DeclareProperty_R(MaxPool2d, nColsIn)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(MaxPool2d, nColsIn)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetMaxPool2d().GetNColsIn());
}
#endif

// ml.MaxPool2d#nRowsKernel
Gurax_DeclareProperty_R(MaxPool2d, nRowsKernel)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(MaxPool2d, nRowsKernel)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetMaxPool2d().GetNRowsKernel());
}

// ml.MaxPool2d#nColsKernel
Gurax_DeclareProperty_R(MaxPool2d, nColsKernel)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(MaxPool2d, nColsKernel)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetMaxPool2d().GetNColsKernel());
}

// ml.MaxPool2d#stride
Gurax_DeclareProperty_R(MaxPool2d, stride)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(MaxPool2d, stride)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetMaxPool2d().GetStride());
}

#if 0
// ml.MaxPool2d#nRowsOut
Gurax_DeclareProperty_R(MaxPool2d, nRowsOut)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(MaxPool2d, nRowsOut)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetMaxPool2d().CalcNRowsOut());
}

// ml.MaxPool2d#nColsOut
Gurax_DeclareProperty_R(MaxPool2d, nColsOut)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(MaxPool2d, nColsOut)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetMaxPool2d().CalcNColsOut());
}
#endif

//------------------------------------------------------------------------------
// VType_MaxPool2d
//------------------------------------------------------------------------------
VType_MaxPool2d VTYPE_MaxPool2d("MaxPool2d");

void VType_MaxPool2d::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(MaxPool2d));
	// Assignment of method
	//Assign(Gurax_CreateMethod(MaxPool2d, CalcSizeOut));
	// Assignment of property
	Assign(Gurax_CreateProperty(MaxPool2d, nRowsKernel));
	Assign(Gurax_CreateProperty(MaxPool2d, nColsKernel));
	Assign(Gurax_CreateProperty(MaxPool2d, stride));
	//Assign(Gurax_CreateProperty(MaxPool2d, nRowsOut));
	//Assign(Gurax_CreateProperty(MaxPool2d, nColsOut));
}

//------------------------------------------------------------------------------
// Value_MaxPool2d
//------------------------------------------------------------------------------
VType& Value_MaxPool2d::vtype = VTYPE_MaxPool2d;

String Value_MaxPool2d::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetMaxPool2d().ToString(ss));
}

bool Value_MaxPool2d::DoSerialize(Stream& stream) const
{
	return GetMaxPool2d().Serialize(stream);
}

Value* VType_MaxPool2d::DoDeserialize(Stream& stream) const
{
	RefPtr<MaxPool2d> pMaxPool2d(MaxPool2d::Deserialize(stream));
	return pMaxPool2d? new Value_MaxPool2d(pMaxPool2d.release()) : nullptr;
}

Gurax_EndModuleScope(ml)
