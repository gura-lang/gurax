//==============================================================================
// test-SizeOf.cpp
//==============================================================================
#include "stdafx.h"

#define Gurax_PrintSizeOf(type) ::printf("%-24s %zu\n", #type, sizeof(type))

namespace Gurax {

Gurax_TesterEntry(SizeOf)
{
	Gurax_PrintSizeOf(Argument);
	Gurax_PrintSizeOf(Attribute);
	Gurax_PrintSizeOf(DateTime);
	Gurax_PrintSizeOf(ObjectOwner);
	Gurax_PrintSizeOf(ObjectStack);
	Gurax_PrintSizeOf(Object_Any);
	Gurax_PrintSizeOf(Object_Attribute);
	Gurax_PrintSizeOf(Object_Binary);
	Gurax_PrintSizeOf(Object_Bool);
	Gurax_PrintSizeOf(Object_Dict);
	Gurax_PrintSizeOf(Object_Expr);
	Gurax_PrintSizeOf(Object_Function);
	Gurax_PrintSizeOf(Object_Iterator);
	Gurax_PrintSizeOf(Object_List);
	Gurax_PrintSizeOf(Object_Module);
	Gurax_PrintSizeOf(Object_Nil);
	Gurax_PrintSizeOf(Object_Number);
	Gurax_PrintSizeOf(Object_Stream);
	Gurax_PrintSizeOf(Object_String);
	Gurax_PrintSizeOf(Object_Symbol);
	Gurax_PrintSizeOf(Object_Undefined);
	Gurax_PrintSizeOf(Object_VType);
	Gurax_PrintSizeOf(Symbol);
	Gurax_PrintSizeOf(TimeDelta);
}

}
