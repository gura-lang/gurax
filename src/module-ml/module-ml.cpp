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
	ReLU::Initialize();
	Sigmoid::Initialize();
	// Assignment of VType
	Assign(VTYPE_Trainer);
	Assign(VTYPE_Node);
	Assign(VTYPE_Optimizer);
	Assign(VTYPE_Conv1d);
	Assign(VTYPE_Conv2d);
	Assign(VTYPE_Conv3d);
	Assign(VTYPE_ReLU);
	Assign(VTYPE_Sigmoid);
	Assign(VTYPE_Softmax);
	// Assignment of function
	Assign(Gurax_CreateFunction(He));
	Assign(Gurax_CreateFunction(Xavier));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(ml)
