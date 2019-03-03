//==============================================================================
// test-SizeOf.cpp
//==============================================================================
#include "stdafx.h"

#define Gurax_PrintSizeOf(type) ::printf("%-24s %zu\n", #type, sizeof(type))

namespace Gurax {

Gurax_TesterEntry(SizeOf)
{
	Gurax_PrintSizeOf(ArgSlot);
	Gurax_PrintSizeOf(Argument);
	Gurax_PrintSizeOf(Attribute);
	Gurax_PrintSizeOf(DateTime);
	Gurax_PrintSizeOf(PUnit_Value);
	Gurax_PrintSizeOf(PUnit_Lookup);
	Gurax_PrintSizeOf(PUnit_AssignToSymbol);
	Gurax_PrintSizeOf(PUnit_PopToDiscard);
	Gurax_PrintSizeOf(PUnit_UnaryOp);
	Gurax_PrintSizeOf(PUnit_BinaryOp);
	Gurax_PrintSizeOf(PUnit_CreateList);
	Gurax_PrintSizeOf(PUnit_AddList);
	Gurax_PrintSizeOf(PUnit_Index);
	Gurax_PrintSizeOf(PUnit_FeedIndex);
	Gurax_PrintSizeOf(PUnit_IndexGet);
	Gurax_PrintSizeOf(PUnit_IndexSet);
	Gurax_PrintSizeOf(PUnit_PropGet);
	Gurax_PrintSizeOf(PUnit_PropSet);
	Gurax_PrintSizeOf(PUnit_Member);
	Gurax_PrintSizeOf(PUnit_Argument);
	Gurax_PrintSizeOf(PUnit_ArgSlot);
	Gurax_PrintSizeOf(PUnit_FeedArgSlot);
	Gurax_PrintSizeOf(PUnit_ArgSlotNamed);
	Gurax_PrintSizeOf(PUnit_FeedArgSlotNamed);
	Gurax_PrintSizeOf(PUnit_Call);
	Gurax_PrintSizeOf(PUnit_Jump);
	Gurax_PrintSizeOf(PUnit_JumpSub);
	Gurax_PrintSizeOf(PUnit_BranchIf);
	Gurax_PrintSizeOf(PUnit_BranchIfNot);
	Gurax_PrintSizeOf(PUnit_NilBranchIf);
	Gurax_PrintSizeOf(PUnit_NilBranchIfNot);
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
