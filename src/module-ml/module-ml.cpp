//==============================================================================
// module-ml.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(ml)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// ml.He(n as Number)
Gurax_DeclareFunction(He)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementFunction(He)
{
	// Arguments
	ArgPicker args(argument);
	Double n = args.PickNumber<Double>();
	// Function body
	if (n == 0.) {
		Error::Issue(ErrorType::DividedByZero, "zero can not be specified");
		return Value::nil();
	}
	return new Value_Number(::sqrt(2 / n));
}

// ml.Xavier(n as Number)
Gurax_DeclareFunction(Xavier)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementFunction(Xavier)
{
	// Arguments
	ArgPicker args(argument);
	Double n = args.PickNumber<Double>();
	// Function body
	if (n == 0.) {
		Error::Issue(ErrorType::DividedByZero, "zero can not be specified");
		return Value::nil();
	}
	return new Value_Number(::sqrt(1 / n));
}

//-----------------------------------------------------------------------------
// Implementation of method for Array
//-----------------------------------------------------------------------------
// Array#Img2dToCol(nRowsFilter as Number, nColsFilter as Number, strides? as Number, padding? as Number) {block?}
Gurax_DeclareMethod(Array, Img2dToCol)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("nRowsFilter", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nColsFilter", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("strides", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("padding", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementMethod(Array, Img2dToCol)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	size_t nRowsFilter = args.PickNumberPos<size_t>();
	size_t nColsFilter = args.PickNumberPos<size_t>();
	size_t strides = args.IsValid()? args.PickNumberPos<size_t>() : 1;
	size_t padding = args.IsValid()? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Array> pArrayOut;
	Img2dToCol(pArrayOut, valueThis.GetArray(), nRowsFilter, nColsFilter, strides, padding);
	return argument.ReturnValue(processor, new Value_Array(pArrayOut.release()));
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Initialize Gear Operators
	Conv1d::Initialize();
	Conv2d::Initialize();
	Conv3d::Initialize();
	ReLU::Initialize();
	Sigmoid::Initialize();
	Softmax::Initialize();
	Tanh::Initialize();
	Trainer::Initialize();
	// Assignment of VType
	Assign(VTYPE_Trainer);
	Assign(VTYPE_Node);
	Assign(VTYPE_NodeMap);
	Assign(VTYPE_Optimizer);
	Assign(VTYPE_Conv1d);
	Assign(VTYPE_Conv2d);
	Assign(VTYPE_Conv3d);
	Assign(VTYPE_ReLU);
	Assign(VTYPE_Sigmoid);
	Assign(VTYPE_Softmax);
	Assign(VTYPE_Tanh);
	// Assignment of function
	Assign(Gurax_CreateFunction(He));
	Assign(Gurax_CreateFunction(Xavier));
	// Assignment of method for Array
	VTYPE_Array.Assign(Gurax_CreateMethod(Array, Img2dToCol));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(ml)
