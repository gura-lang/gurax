//==============================================================================
// VType_Semaphore.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Semaphore)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Semaphore)}

${help.ComposeMethodHelp(Semaphore)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Semaphore() {block?}
Gurax_DeclareConstructor(Semaphore)
{
	Declare(VTYPE_Semaphore, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Semaphore` instance.");
}

Gurax_ImplementConstructor(Semaphore)
{
	// Function body
	RefPtr<OAL::Semaphore> pSemaphore(new OAL::Semaphore());
	return argument.ReturnValue(processor, new Value_Semaphore(pSemaphore.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Semaphore#Release()
Gurax_DeclareMethod(Semaphore, Release)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Releases the semaphore.\n");
}

Gurax_ImplementMethod(Semaphore, Release)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetSemaphore().Release();
	return Value::nil();
}

// Semaphore#Wait()
Gurax_DeclareMethod(Semaphore, Wait)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Waits for the semaphore to be released.\n");
}

Gurax_ImplementMethod(Semaphore, Wait)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetSemaphore().Wait();
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_Semaphore
//------------------------------------------------------------------------------
VType_Semaphore VTYPE_Semaphore("Semaphore");

void VType_Semaphore::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Semaphore));
	// Assignment of method
	Assign(Gurax_CreateMethod(Semaphore, Release));
	Assign(Gurax_CreateMethod(Semaphore, Wait));
}

//------------------------------------------------------------------------------
// Value_Semaphore
//------------------------------------------------------------------------------
VType& Value_Semaphore::vtype = VTYPE_Semaphore;

String Value_Semaphore::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetSemaphore().ToString(ss));
}

}
