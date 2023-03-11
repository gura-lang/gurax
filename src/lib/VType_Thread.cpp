//==============================================================================
// VType_Thread.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Thread, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Thread, `en)}

${help.ComposeMethodHelp(Thread, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Thread(func:Function) {block?}
Gurax_DeclareConstructor(Thread)
{
	Declare(VTYPE_Thread, Flag::None);
	DeclareArg("func", VTYPE_Function, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Thread` instance.
)""");
}

Gurax_ImplementConstructor(Thread)
{
	// Arguments
	ArgPicker args(argument);
	Function& func = args.PickFunction();
	// Function body
	RefPtr<Argument> pArgument(new Argument(processor, func));
	RefPtr<OAL::Thread> pThread(new ThreadCustom(processor, func.Reference(), pArgument.release()));
	return argument.ReturnValue(processor, new Value_Thread(pThread.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Thread#Start()
Gurax_DeclareMethod(Thread, Start)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Starts the thread.
)""");
}

Gurax_ImplementMethod(Thread, Start)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetThread().Start();
	return Value::nil();
}

// Thread#Wait()
Gurax_DeclareMethod(Thread, Wait)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Waits for the thread to end.
)""");
}

Gurax_ImplementMethod(Thread, Wait)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetThread().Wait();
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Thread#propSkeleton
Gurax_DeclareProperty_R(Thread, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Thread));
	// Assignment of method
	Assign(Gurax_CreateMethod(Thread, Start));
	Assign(Gurax_CreateMethod(Thread, Wait));
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
