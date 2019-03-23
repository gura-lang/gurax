//==============================================================================
// test-SizeOf.cpp
//==============================================================================
#include "stdafx.h"

#define PrintSizeOf(type) ::printf("%-24s %zu\n", #type, sizeof(type))

namespace Gurax {

Gurax_TesterEntry(SizeOf)
{
	PrintSizeOf(ArgSlot);
	PrintSizeOf(Argument);
	PrintSizeOf(Attribute);
	PrintSizeOf(DateTime);
	PrintSizeOf(PUnit_Value);
	PrintSizeOf(PUnit_Lookup);
	PrintSizeOf(PUnit_AssignToSymbol);
	PrintSizeOf(PUnit_AssignToDeclArg);
	PrintSizeOf(PUnit_AssignFunction);
	PrintSizeOf(PUnit_Cast);
	PrintSizeOf(PUnit_GenIterator);
	PrintSizeOf(PUnit_GenRangeIterator);
	PrintSizeOf(PUnit_EvalIterator);
	PrintSizeOf(PUnit_PopValueToDiscard);
	PrintSizeOf(PUnit_UnaryOp);
	PrintSizeOf(PUnit_BinaryOp);
	PrintSizeOf(PUnit_CreateList);
	PrintSizeOf(PUnit_AddList);
	PrintSizeOf(PUnit_Index);
	PrintSizeOf(PUnit_FeedIndex);
	PrintSizeOf(PUnit_IndexGet);
	PrintSizeOf(PUnit_IndexSet);
	PrintSizeOf(PUnit_PropGet);
	PrintSizeOf(PUnit_PropSet);
	PrintSizeOf(PUnit_Member);
	PrintSizeOf(PUnit_Argument);
	PrintSizeOf(PUnit_ArgSlot);
	PrintSizeOf(PUnit_FeedArgSlot);
	PrintSizeOf(PUnit_ArgSlotNamed);
	PrintSizeOf(PUnit_FeedArgSlotNamed);
	PrintSizeOf(PUnit_Call);
	PrintSizeOf(PUnit_Jump);
	PrintSizeOf(PUnit_JumpIf);
	PrintSizeOf(PUnit_JumpIfNot);
	PrintSizeOf(PUnit_NilJumpIf);
	PrintSizeOf(PUnit_NilJumpIfNot);
	PrintSizeOf(PUnit_ExitPoint);
	PrintSizeOf(PUnit_PopValueToDiscard);
	PrintSizeOf(PUnit_RemoveValue);
	PrintSizeOf(PUnit_Return);
	PrintSizeOf(PUnit_PushFrame_Block);
	PrintSizeOf(PUnit_PopFrame);
	PrintSizeOf(PUnit_Terminate);
	PrintSizeOf(PUnit_Bridge);
	PrintSizeOf(Symbol);
	PrintSizeOf(TimeDelta);
	PrintSizeOf(ValueOwner);
	PrintSizeOf(ValueStack);
	PrintSizeOf(Value_Any);
	PrintSizeOf(Value_ArgSlot);
	PrintSizeOf(Value_Argument);
	PrintSizeOf(Value_Attribute);
	PrintSizeOf(Value_Binary);
	PrintSizeOf(Value_Bool);
	PrintSizeOf(Value_DateTime);
	PrintSizeOf(Value_Dict);
	PrintSizeOf(Value_Expr);
	PrintSizeOf(Value_Function);
	PrintSizeOf(Value_Index);
	PrintSizeOf(Value_Iterator);
	PrintSizeOf(Value_List);
	PrintSizeOf(Value_Member);
	PrintSizeOf(Value_Module);
	PrintSizeOf(Value_Nil);
	PrintSizeOf(Value_Number);
	PrintSizeOf(Value_Object);
	PrintSizeOf(Value_Quote);
	PrintSizeOf(Value_Stream);
	PrintSizeOf(Value_String);
	PrintSizeOf(Value_Symbol);
	PrintSizeOf(Value_Template);
	PrintSizeOf(Value_TimeDelta);
	PrintSizeOf(Value_Undefined);
	PrintSizeOf(Value_VType);
}

}
