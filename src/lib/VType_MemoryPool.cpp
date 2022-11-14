//==============================================================================
// VType_MemoryPool.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(MemoryPool, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(MemoryPool, `en)}

${help.ComposeMethodHelp(MemoryPool, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// MemoryPool##CountBlocksAllocated()
Gurax_DeclareHybridMethod(MemoryPool, CountBlocksAllocated)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
Returns the number of allocated blocks.
)**");
}

Gurax_ImplementHybridMethod(MemoryPool, CountBlocksAllocated)
{
	// Target
	Value& valueThis = argument.GetValueThis();
	MemoryPool& memoryPool = valueThis.IsInstanceOf(VTYPE_MemoryPool)?
		dynamic_cast<Value_MemoryPool&>(valueThis).GetMemoryPool() : MemoryPool::Global();
	// Arguments
	//ArgPicker args(argument);
	// Function body
	size_t nBlocksAllocated = 0;
	nBlocksAllocated += memoryPool.GetChunkSmall().CountBlocksAllocated();
	nBlocksAllocated += memoryPool.GetChunkMedium().CountBlocksAllocated();
	nBlocksAllocated += memoryPool.GetChunkLarge().CountBlocksAllocated();
	return new Value_Number(nBlocksAllocated);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// MemoryPool#propSkeleton
Gurax_DeclareProperty_R(MemoryPool, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(MemoryPool, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_MemoryPool
//------------------------------------------------------------------------------
VType_MemoryPool VTYPE_MemoryPool("MemoryPool");

void VType_MemoryPool::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(MemoryPool, CountBlocksAllocated));
	// Assignment of property
	Assign(Gurax_CreateProperty(MemoryPool, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_MemoryPool
//------------------------------------------------------------------------------
VType& Value_MemoryPool::vtype = VTYPE_MemoryPool;

String Value_MemoryPool::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetMemoryPool().ToString(ss));
}

}
