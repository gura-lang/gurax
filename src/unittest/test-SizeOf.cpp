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
	using PUnit_Value_ = PUnit_Value<0, false>;
	PrintSizeOf(PUnit_Value_);
	using PUnit_Lookup_ = PUnit_Lookup<0, false>;
	PrintSizeOf(PUnit_Lookup_);
	using PUnit_AssignToSymbol_ = PUnit_AssignToSymbol<0, false>;
	PrintSizeOf(PUnit_AssignToSymbol_);
	using PUnit_AssignToDeclArg_ = PUnit_AssignToDeclArg<0, false>;
	PrintSizeOf(PUnit_AssignToDeclArg_);
	using PUnit_AssignFunction_ = PUnit_AssignFunction<0, false>;
	PrintSizeOf(PUnit_AssignFunction_);
	using PUnit_AssignMethod_ = PUnit_AssignMethod<0, false>;
	PrintSizeOf(PUnit_AssignMethod_);
	using PUnit_AssignPropHandler_ = PUnit_AssignPropHandler<0, false, false>;
	PrintSizeOf(PUnit_AssignPropHandler_);
	using PUnit_Cast_ = PUnit_Cast<0, false>;
	PrintSizeOf(PUnit_Cast_);
	using PUnit_GenIterator_ = PUnit_GenIterator<0, false>;
	PrintSizeOf(PUnit_GenIterator_);
	using PUnit_GenIterator_Range_ = PUnit_GenIterator_Range<0, false>;
	PrintSizeOf(PUnit_GenIterator_Range_);
	using PUnit_GenIterator_Counter_ = PUnit_GenIterator_Counter<0, false>;
	PrintSizeOf(PUnit_GenIterator_Counter_);
	using PUnit_EvalIterator_ = PUnit_EvalIterator<0, false>;
	PrintSizeOf(PUnit_EvalIterator_);
	using PUnit_ForEach_ = PUnit_ForEach<0, false>;
	PrintSizeOf(PUnit_ForEach_);
	using PUnit_UnaryOp_ = PUnit_UnaryOp<0, false>;
	PrintSizeOf(PUnit_UnaryOp_);
	using PUnit_BinaryOp_ = PUnit_BinaryOp<0, false>;
	PrintSizeOf(PUnit_BinaryOp_);
	using PUnit_Import_ = PUnit_Import<0, false>;
	PrintSizeOf(PUnit_Import_);
	using PUnit_CreateVType_ = PUnit_CreateVType<0, false, false>;
	PrintSizeOf(PUnit_CreateVType_);
	using PUnit_CreateList_ = PUnit_CreateList<0, false>;
	PrintSizeOf(PUnit_CreateList_);
	using PUnit_ListElem_ = PUnit_ListElem<0, false, false, false>;
	PrintSizeOf(PUnit_ListElem_);
	using PUnit_CreateDict_ = PUnit_CreateDict<0, false>;
	PrintSizeOf(PUnit_CreateDict_);
	using PUnit_DictElem_ = PUnit_DictElem<0, false>;
	PrintSizeOf(PUnit_DictElem_);
	using PUnit_Index_ = PUnit_Index<0, false>;
	PrintSizeOf(PUnit_Index_);
	using PUnit_FeedIndex_ = PUnit_FeedIndex<0, false>;
	PrintSizeOf(PUnit_FeedIndex_);
	using PUnit_IndexGet_ = PUnit_IndexGet<0, false>;
	PrintSizeOf(PUnit_IndexGet_);
	using PUnit_IndexSet_ = PUnit_IndexSet<0, false>;
	PrintSizeOf(PUnit_IndexSet_);
	using PUnit_PropGet_ = PUnit_PropGet<0, false>;
	PrintSizeOf(PUnit_PropGet_);
	using PUnit_PropSet_ = PUnit_PropSet<0, false>;
	PrintSizeOf(PUnit_PropSet_);
	using PUnit_Member_Normal_ = PUnit_Member_Normal<0, false>;
	PrintSizeOf(PUnit_Member_Normal_);
	using PUnit_Member_MapAlong_ = PUnit_Member_MapAlong<0, false>;
	PrintSizeOf(PUnit_Member_MapAlong_);
	using PUnit_Member_MapToList_ = PUnit_Member_MapToList<0, false>;
	PrintSizeOf(PUnit_Member_MapToList_);
	using PUnit_Member_MapToIter_ = PUnit_Member_MapToIter<0, false>;
	PrintSizeOf(PUnit_Member_MapToIter_);
	using PUnit_Argument_ = PUnit_Argument<0, false, false>;
	PrintSizeOf(PUnit_Argument_);
	using PUnit_BeginArgSlot_ = PUnit_BeginArgSlot<0, false>;
	PrintSizeOf(PUnit_BeginArgSlot_);
	using PUnit_EndArgSlot_ = PUnit_EndArgSlot<0, false>;
	PrintSizeOf(PUnit_EndArgSlot_);
	using PUnit_BeginArgSlotNamed_ = PUnit_BeginArgSlotNamed<0, false>;
	PrintSizeOf(PUnit_BeginArgSlotNamed_);
	using PUnit_EndArgSlotNamed_ = PUnit_EndArgSlotNamed<0, false>;
	PrintSizeOf(PUnit_EndArgSlotNamed_);
	using PUnit_Call_ = PUnit_Call<0, false>;
	PrintSizeOf(PUnit_Call_);
	using PUnit_Jump_ = PUnit_Jump<0, false>;
	PrintSizeOf(PUnit_Jump_);
	using PUnit_JumpIf_ = PUnit_JumpIf<0, false>;
	PrintSizeOf(PUnit_JumpIf_);
	using PUnit_JumpIfNot_ = PUnit_JumpIfNot<0, false>;
	PrintSizeOf(PUnit_JumpIfNot_);
	using PUnit_NilJumpIf_ = PUnit_NilJumpIf<0, false>;
	PrintSizeOf(PUnit_NilJumpIf_);
	using PUnit_NilJumpIfNot_ = PUnit_NilJumpIfNot<0, false>;
	PrintSizeOf(PUnit_NilJumpIfNot_);
	using PUnit_KeepJumpIf_ = PUnit_KeepJumpIf<0, false>;
	PrintSizeOf(PUnit_KeepJumpIf_);
	using PUnit_KeepJumpIfNot_ = PUnit_KeepJumpIfNot<0, false>;
	PrintSizeOf(PUnit_KeepJumpIfNot_);
	using PUnit_BeginTryBlock_ = PUnit_BeginTryBlock<0, false>;
	PrintSizeOf(PUnit_BeginTryBlock_);
	using PUnit_EndTryBlock_ = PUnit_EndTryBlock<0, false>;
	PrintSizeOf(PUnit_EndTryBlock_);
	using PUnit_JumpIfNoCatch_ = PUnit_JumpIfNoCatch<0, false>;
	PrintSizeOf(PUnit_JumpIfNoCatch_);
	using PUnit_JumpIfNoCatchAny_ = PUnit_JumpIfNoCatchAny<0, false>;
	PrintSizeOf(PUnit_JumpIfNoCatchAny_);
	using PUnit_NilJumpIfNoCatch_ = PUnit_NilJumpIfNoCatch<0, false>;
	PrintSizeOf(PUnit_NilJumpIfNoCatch_);
	using PUnit_NilJumpIfNoCatchAny_ = PUnit_NilJumpIfNoCatchAny<0, false>;
	PrintSizeOf(PUnit_NilJumpIfNoCatchAny_);
	using PUnit_BeginSequence_ = PUnit_BeginSequence<0, false>;
	PrintSizeOf(PUnit_BeginSequence_);
	using PUnit_EndSequence_ = PUnit_EndSequence<0, false>;
	PrintSizeOf(PUnit_EndSequence_);
	using PUnit_DiscardValue_ = PUnit_DiscardValue<0, false>;
	PrintSizeOf(PUnit_DiscardValue_);
	using PUnit_RemoveValue_ = PUnit_RemoveValue<0, false>;
	PrintSizeOf(PUnit_RemoveValue_);
	using PUnit_Break_ = PUnit_Break<0, false, false>;
	PrintSizeOf(PUnit_Break_);
	using PUnit_Continue_ = PUnit_Continue<0, false>;
	PrintSizeOf(PUnit_Continue_);
	using PUnit_Miscatch_ = PUnit_Miscatch<0, false>;
	PrintSizeOf(PUnit_Miscatch_);
	using PUnit_Return_ = PUnit_Return<0, false>;
	PrintSizeOf(PUnit_Return_);
	using PUnit_PushFrame_ = PUnit_PushFrame<0, false, Frame_Block>;
	PrintSizeOf(PUnit_PushFrame_);
	using PUnit_PopFrame_ = PUnit_PopFrame<0, false>;
	PrintSizeOf(PUnit_PopFrame_);
	PrintSizeOf(PUnit_Terminate);
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
	PrintSizeOf(Value_CallableMember);
	PrintSizeOf(Value_DateTime);
	PrintSizeOf(Value_Dict);
	PrintSizeOf(Value_Error);
	PrintSizeOf(Value_ErrorType);
	PrintSizeOf(Value_Expr);
	PrintSizeOf(Value_Function);
	PrintSizeOf(Value_Index);
	PrintSizeOf(Value_Iterator);
	PrintSizeOf(Value_List);
	PrintSizeOf(Value_Module);
	PrintSizeOf(Value_Nil);
	PrintSizeOf(Value_Number);
	PrintSizeOf(Value_Object);
	PrintSizeOf(Value_Quote);
	PrintSizeOf(Value_Stream);
	PrintSizeOf(Value_String);
	PrintSizeOf(Value_Symbol);
	//PrintSizeOf(Value_Template);
	PrintSizeOf(Value_TimeDelta);
	PrintSizeOf(Value_Undefined);
	PrintSizeOf(Value_VType);
}

}
