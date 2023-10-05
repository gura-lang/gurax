﻿//==============================================================================
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
	using PUnit_Value_ = PUnit_Value<false>;
	PrintSizeOf(PUnit_Value_);
	using PUnit_Lookup_ = PUnit_Lookup<false, false>;
	PrintSizeOf(PUnit_Lookup_);
	using PUnit_AssignToSymbol_ = PUnit_AssignToSymbol<false, false>;
	PrintSizeOf(PUnit_AssignToSymbol_);
	using PUnit_AssignToDeclArg_ = PUnit_AssignToDeclArg<false>;
	PrintSizeOf(PUnit_AssignToDeclArg_);
	using PUnit_AssignFunction_ = PUnit_AssignFunction<false>;
	PrintSizeOf(PUnit_AssignFunction_);
	using PUnit_AssignMethod_ = PUnit_AssignMethod<false, false>;
	PrintSizeOf(PUnit_AssignMethod_);
	using PUnit_AssignPropSlot_ = PUnit_AssignPropSlot<false, false>;
	PrintSizeOf(PUnit_AssignPropSlot_);
	using PUnit_Cast_ = PUnit_Cast<false>;
	PrintSizeOf(PUnit_Cast_);
	using PUnit_GenIterator_ = PUnit_GenIterator<false>;
	PrintSizeOf(PUnit_GenIterator_);
	using PUnit_GenIterator_Range_ = PUnit_GenIterator_Range<false>;
	PrintSizeOf(PUnit_GenIterator_Range_);
	using PUnit_GenIterator_Counter_ = PUnit_GenIterator_Counter<false>;
	PrintSizeOf(PUnit_GenIterator_Counter_);
	using PUnit_EvalIterator_ = PUnit_EvalIterator<false>;
	PrintSizeOf(PUnit_EvalIterator_);
	using PUnit_ForEach_ = PUnit_ForEach<false>;
	PrintSizeOf(PUnit_ForEach_);
	using PUnit_UnaryOp_ = PUnit_UnaryOp<false>;
	PrintSizeOf(PUnit_UnaryOp_);
	using PUnit_BinaryOp_ = PUnit_BinaryOp<false>;
	PrintSizeOf(PUnit_BinaryOp_);
	using PUnit_Import_ = PUnit_Import<false>;
	PrintSizeOf(PUnit_Import_);
	using PUnit_VTypeBegin_ = PUnit_VTypeBegin<false, false>;
	PrintSizeOf(PUnit_VTypeBegin_);
	using PUnit_CreateList_ = PUnit_CreateList<false>;
	PrintSizeOf(PUnit_CreateList_);
	using PUnit_ListElem_ = PUnit_ListElem<false, false, false>;
	PrintSizeOf(PUnit_ListElem_);
	using PUnit_CreateDict_ = PUnit_CreateDict<false>;
	PrintSizeOf(PUnit_CreateDict_);
	using PUnit_DictElem_ = PUnit_DictElem<false>;
	PrintSizeOf(PUnit_DictElem_);
	using PUnit_Index_ = PUnit_Index<false>;
	PrintSizeOf(PUnit_Index_);
	using PUnit_FeedIndex_ = PUnit_FeedIndex<false>;
	PrintSizeOf(PUnit_FeedIndex_);
	using PUnit_IndexGet_ = PUnit_IndexGet<false>;
	PrintSizeOf(PUnit_IndexGet_);
	using PUnit_IndexSet_ = PUnit_IndexSet<false, false>;
	PrintSizeOf(PUnit_IndexSet_);
	using PUnit_MemberSet_Normal_ = PUnit_MemberSet_Normal<false, false>;
	PrintSizeOf(PUnit_MemberSet_Normal_);
	using PUnit_MemberGet_Normal_ = PUnit_MemberGet_Normal<false>;
	PrintSizeOf(PUnit_MemberGet_Normal_);
	using PUnit_MemberGet_MapAlong_ = PUnit_MemberGet_MapAlong<false>;
	PrintSizeOf(PUnit_MemberGet_MapAlong_);
	using PUnit_MemberGet_MapToList_ = PUnit_MemberGet_MapToList<false>;
	PrintSizeOf(PUnit_MemberGet_MapToList_);
	using PUnit_MemberGet_MapToIter_ = PUnit_MemberGet_MapToIter<false>;
	PrintSizeOf(PUnit_MemberGet_MapToIter_);
	using PUnit_Argument_ = PUnit_Argument<false, false>;
	PrintSizeOf(PUnit_Argument_);
	using PUnit_ArgSlotBegin_ = PUnit_ArgSlotBegin<false>;
	PrintSizeOf(PUnit_ArgSlotBegin_);
	using PUnit_ArgSlotEnd_ = PUnit_ArgSlotEnd<false>;
	PrintSizeOf(PUnit_ArgSlotEnd_);
	using PUnit_NamedArgSlotBegin_ = PUnit_NamedArgSlotBegin<false>;
	PrintSizeOf(PUnit_NamedArgSlotBegin_);
	using PUnit_NamedArgSlotEnd_ = PUnit_NamedArgSlotEnd<false>;
	PrintSizeOf(PUnit_NamedArgSlotEnd_);
	using PUnit_Call_ = PUnit_Call<false>;
	PrintSizeOf(PUnit_Call_);
	using PUnit_Jump_ = PUnit_Jump<false>;
	PrintSizeOf(PUnit_Jump_);
	using PUnit_JumpIf_ = PUnit_JumpIf<false, PUnit::BranchMode::Empty>;
	PrintSizeOf(PUnit_JumpIf_);
	using PUnit_JumpIfNot_ = PUnit_JumpIfNot<false, PUnit::BranchMode::Empty>;
	PrintSizeOf(PUnit_JumpIfNot_);
	using PUnit_TryBlockBegin_ = PUnit_TryBlockBegin<false>;
	PrintSizeOf(PUnit_TryBlockBegin_);
	using PUnit_TryBlockEnd_ = PUnit_TryBlockEnd<false>;
	PrintSizeOf(PUnit_TryBlockEnd_);
	using PUnit_JumpIfNoCatch_ = PUnit_JumpIfNoCatch<false, PUnit::BranchMode::Empty>;
	PrintSizeOf(PUnit_JumpIfNoCatch_);
	using PUnit_JumpIfNoCatchAny_ = PUnit_JumpIfNoCatchAny<false, PUnit::BranchMode::Empty>;
	PrintSizeOf(PUnit_JumpIfNoCatchAny_);
	using PUnit_SequenceBegin_ = PUnit_SequenceBegin<false>;
	PrintSizeOf(PUnit_SequenceBegin_);
	using PUnit_SequenceEnd_ = PUnit_SequenceEnd<false>;
	PrintSizeOf(PUnit_SequenceEnd_);
	using PUnit_DiscardValue_ = PUnit_DiscardValue<false>;
	PrintSizeOf(PUnit_DiscardValue_);
	using PUnit_RemoveValue_ = PUnit_RemoveValue<false>;
	PrintSizeOf(PUnit_RemoveValue_);
	using PUnit_Break_ = PUnit_Break<false, false>;
	PrintSizeOf(PUnit_Break_);
	using PUnit_Continue_ = PUnit_Continue<false>;
	PrintSizeOf(PUnit_Continue_);
	using PUnit_FailCatch_ = PUnit_FailCatch<false>;
	PrintSizeOf(PUnit_FailCatch_);
	using PUnit_Return_ = PUnit_Return<false>;
	PrintSizeOf(PUnit_Return_);
	using PUnit_PushFrame_ = PUnit_PushFrame<false, Frame_Block>;
	PrintSizeOf(PUnit_PushFrame_);
	using PUnit_PopFrame_ = PUnit_PopFrame<false>;
	PrintSizeOf(PUnit_PopFrame_);
	PrintSizeOf(PUnit_Terminate);
	PrintSizeOf(PUnit_Bridge);
	PrintSizeOf(Symbol);
	PrintSizeOf(SymbolList);
	PrintSizeOf(SymbolSet);
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
