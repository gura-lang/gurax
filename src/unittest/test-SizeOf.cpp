//==============================================================================
// test-SizeOf.cpp
//==============================================================================
#include "stdafx.h"

#define PrintSizeOf(type) ::printf("%-32s %zu\n", #type, sizeof(type))

namespace Gurax {

Gurax_TesterEntry(SizeOf)
{
	PrintSizeOf(ArgSlot);
	PrintSizeOf(Argument);
	PrintSizeOf(Attribute);
	PrintSizeOf(DateTime);
	PrintSizeOf(PUnit_Value<false>);
	PrintSizeOf(PUnit_Lookup<false>);
	PrintSizeOf(PUnit_AssignToSymbol<false>);
	PrintSizeOf(PUnit_AssignToDeclArg<false>);
	PrintSizeOf(PUnit_AssignFunction<false>);
	PrintSizeOf(PUnit_Cast<false>);
	PrintSizeOf(PUnit_GenIterator<false>);
	PrintSizeOf(PUnit_GenRangeIterator<false>);
	PrintSizeOf(PUnit_EvalIterator<false>);
	PrintSizeOf(PUnit_ForEach<false>);
	PrintSizeOf(PUnit_UnaryOp<false>);
	PrintSizeOf(PUnit_BinaryOp<false>);
	PrintSizeOf(PUnit_CreateList<false>);
	using PUnit_ListElem_ = PUnit_ListElem<false, false>;
	PrintSizeOf(PUnit_ListElem_);
	PrintSizeOf(PUnit_CreateDict<false>);
	PrintSizeOf(PUnit_DictElem<false>);
	PrintSizeOf(PUnit_Index<false>);
	PrintSizeOf(PUnit_FeedIndex<false>);
	PrintSizeOf(PUnit_IndexGet<false>);
	PrintSizeOf(PUnit_IndexSet<false>);
	PrintSizeOf(PUnit_PropGet<false>);
	PrintSizeOf(PUnit_PropSet<false>);
	PrintSizeOf(PUnit_Member<false>);
	PrintSizeOf(PUnit_Argument<false>);
	PrintSizeOf(PUnit_ArgSlot<false>);
	PrintSizeOf(PUnit_FeedArgSlot<false>);
	PrintSizeOf(PUnit_ArgSlotNamed<false>);
	PrintSizeOf(PUnit_FeedArgSlotNamed<false>);
	PrintSizeOf(PUnit_Call<false>);
	PrintSizeOf(PUnit_Jump<false>);
	PrintSizeOf(PUnit_JumpIf<false>);
	PrintSizeOf(PUnit_JumpIfNot<false>);
	PrintSizeOf(PUnit_NilJumpIf<false>);
	PrintSizeOf(PUnit_NilJumpIfNot<false>);
	PrintSizeOf(PUnit_KeepJumpIf<false>);
	PrintSizeOf(PUnit_KeepJumpIfNot<false>);
	PrintSizeOf(PUnit_PushExceptionInfo<false>);
	PrintSizeOf(PUnit_PopExceptionInfo<false>);
	PrintSizeOf(PUnit_JumpIfNoCatch<false>);
	PrintSizeOf(PUnit_JumpIfNoCatchAny<false>);
	PrintSizeOf(PUnit_NilJumpIfNoCatch<false>);
	PrintSizeOf(PUnit_NilJumpIfNoCatchAny<false>);
	PrintSizeOf(PUnit_BeginSequence<false>);
	PrintSizeOf(PUnit_DiscardValue<false>);
	PrintSizeOf(PUnit_RemoveValue<false>);
	using PUnit_Break_ = PUnit_Break<false, false>;
	PrintSizeOf(PUnit_Break_);
	PrintSizeOf(PUnit_Continue<false>);
	PrintSizeOf(PUnit_Miscatch<false>);
	PrintSizeOf(PUnit_Return<false>);
	using PUnit_PushFrame_ = PUnit_PushFrame<Frame_Block, false>;
	PrintSizeOf(PUnit_PushFrame_);
	PrintSizeOf(PUnit_PopFrame<false>);
	PrintSizeOf(PUnit_Terminate<false>);
	PrintSizeOf(PUnit_Bridge);
	PrintSizeOf(Symbol);
	PrintSizeOf(TimeDelta);
	PrintSizeOf(ValueOwner);
	PrintSizeOf(ValueStack);
	PrintSizeOf(Value_Any);
	PrintSizeOf(Value_ArgMapper);
	PrintSizeOf(Value_ArgSlot);
	PrintSizeOf(Value_Argument);
	PrintSizeOf(Value_Attribute);
	PrintSizeOf(Value_Binary);
	PrintSizeOf(Value_Bool);
	PrintSizeOf(Value_DateTime);
	PrintSizeOf(Value_Dict);
	PrintSizeOf(Value_Error);
	PrintSizeOf(Value_ErrorType);
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
