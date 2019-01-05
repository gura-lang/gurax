//==============================================================================
// test-SizeOf.cpp
//==============================================================================
#include "stdafx.h"

#define Gurax_PrintSizeOf(type) ::printf("%-24s %zu\n", #type, sizeof(type))

namespace Gurax {

Gurax_TesterEntry(SizeOf)
{
	Gurax_PrintSizeOf(Frame_Node);
	Gurax_PrintSizeOf(Frame_Branch);
	Gurax_PrintSizeOf(ObjectOwner);
	Gurax_PrintSizeOf(ObjectStack);
	Gurax_PrintSizeOf(Object_bool);
	Gurax_PrintSizeOf(Object_function);
	Gurax_PrintSizeOf(Object_nil);
	Gurax_PrintSizeOf(Object_number);
	Gurax_PrintSizeOf(Object_string);
	Gurax_PrintSizeOf(Object_symbol);
	Gurax_PrintSizeOf(Object_undefined);
	Gurax_PrintSizeOf(Symbol);
}

}
