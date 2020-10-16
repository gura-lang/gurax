//==============================================================================
// VType_Thread.cpp
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
// Thread() {block?}
Gurax_DeclareConstructor(Thread)
{
	Declare(VTYPE_Thread, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Thread` instance.");
}

Gurax_ImplementConstructor(Thread)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	//RefPtr<OAL::Thread> pThread(new OAL::Thread());
	//return argument.ReturnValue(processor, new Value_Thread(pThread.release()));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Thread#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Thread, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Thread, MethodSkeleton)
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
// Thread#propSkeleton
Gurax_DeclareProperty_R(Thread, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Thread, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Thread
//------------------------------------------------------------------------------
VType_Thread VTYPE_Thread("Thread");

void VType_Thread::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Thread));
	// Assignment of method
	Assign(Gurax_CreateMethod(Thread, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Thread, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Thread
//------------------------------------------------------------------------------
VType& Value_Thread::vtype = VTYPE_Thread;

String Value_Thread::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetThread().ToString(ss));
}

}
