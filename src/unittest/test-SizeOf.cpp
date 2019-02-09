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
	Gurax_PrintSizeOf(Symbol);
	Gurax_PrintSizeOf(TimeDelta);
	Gurax_PrintSizeOf(ValueOwner);
	Gurax_PrintSizeOf(ValueStack);
	Gurax_PrintSizeOf(Value_Any);
	Gurax_PrintSizeOf(Value_Attribute);
	Gurax_PrintSizeOf(Value_Binary);
	Gurax_PrintSizeOf(Value_Bool);
	Gurax_PrintSizeOf(Value_Dict);
	Gurax_PrintSizeOf(Value_Expr);
	Gurax_PrintSizeOf(Value_Function);
	Gurax_PrintSizeOf(Value_Iterator);
	Gurax_PrintSizeOf(Value_List);
	Gurax_PrintSizeOf(Value_Module);
	Gurax_PrintSizeOf(Value_Nil);
	Gurax_PrintSizeOf(Value_Number);
	Gurax_PrintSizeOf(Value_Stream);
	Gurax_PrintSizeOf(Value_String);
	Gurax_PrintSizeOf(Value_Symbol);
	Gurax_PrintSizeOf(Value_Undefined);
	Gurax_PrintSizeOf(Value_VType);
}

}
