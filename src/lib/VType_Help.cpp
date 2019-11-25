//==============================================================================
// VType_Help.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Help() {block?}
Gurax_DeclareFunction(Help)
{
	Declare(VTYPE_Help, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Help` instance.");
}

Gurax_ImplementFunction(Help)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	//RefPtr<Help> pHelp(new Help());
	//return argument.ReturnValue(processor, new Value_Help(pHelp.release()));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Help#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Help, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Help, MethodSkeleton)
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
// Help#propSkeleton
Gurax_DeclareProperty_R(Help, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Help, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// ?Any
Gurax_ImplementOpUnary(Question, Any)
{
	return Value::nil();
}

// Any %% String
Gurax_ImplementOpBinary(ModMod, Any, String)
{
	HelpHolder* pHelpHolder = valueL.GetHelpHolder();
	if (!pHelpHolder) {
		Error::Issue(ErrorType::ValueError,
				 "can't assign help to value type '%s'", valueL.GetVType().MakeFullName().c_str());
		return Value::nil();
	}
	pHelpHolder->AddHelp(Gurax_Symbol(en), Value_String::GetString(valueR));
	return valueL.Reference();
}

//------------------------------------------------------------------------------
// VType_Help
//------------------------------------------------------------------------------
VType_Help VTYPE_Help("Help");

void VType_Help::DoPrepare(Frame& frameOuter)
{
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateFunction(Help));
	// Assignment of method
	Assign(Gurax_CreateMethod(Help, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Help, propSkeleton));
	// Assignment of operator
	Gurax_AssignOpUnary(Question, Any);
	Gurax_AssignOpBinary(ModMod, Any, String);
}

//------------------------------------------------------------------------------
// Value_Help
//------------------------------------------------------------------------------
VType& Value_Help::vtype = VTYPE_Help;

}
