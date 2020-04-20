//==============================================================================
// VType_Diff.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// diff.Diff(src1, src2):[icase] {block?}
Gurax_DeclareConstructor(Diff)
{
	Declare(VTYPE_Diff, Flag::None);
	DeclareArg("src1", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("src2", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(icase));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `diff.Diff` instance.");
}

Gurax_ImplementConstructor(Diff)
{
	// Arguments
	ArgPicker args(argument);
	Value& src1 = args.PickValue();
	Value& src2 = args.PickValue();
	// Function body
	bool icaseFlag = argument.IsSet(Gurax_Symbol(icase));
	RefPtr<Diff> pDiff(new Diff(icaseFlag));
	if (!pDiff->Compose(src1, src2)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Diff(pDiff.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// diff.Diff#EachEdit() {block?}
Gurax_DeclareMethod(Diff, EachEdit)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that returns stored edit information.\n");
}

Gurax_ImplementMethod(Diff, EachEdit)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	Diff& Diff = valueThis.GetDiff();
	RefPtr<Iterator> pIterator(new Iterator_Edit(Diff.Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// diff.Diff#EachHunk(nLinesCommon?:Number) {block?}
Gurax_DeclareMethod(Diff, EachHunk)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("nLinesCommon", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that returns stored hunk information.\n");
}

Gurax_ImplementMethod(Diff, EachHunk)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	size_t nLinesCommon = args.IsValid()? args.PickNumberNonNeg<size_t>() : 3;
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Hunk(valueThis.GetDiff().Reference(), nLinesCommon));
	return argument.ReturnIterator(processor, pIterator.release());
}

// diff.Diff#PrintHunks(stream?:Stream:w, nLinesCommon?:Number):void
Gurax_DeclareMethod(Diff, PrintHunks)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	DeclareArg("nLinesCommon", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Prints the unified hunks.\n");
}

Gurax_ImplementMethod(Diff, PrintHunks)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.IsValid()? args.PickStream() : Basement::Inst.GetStreamCOut();
	size_t nLinesCommon = args.IsValid()? args.PickNumberNonNeg<size_t>() : 3;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	valueThis.GetDiff().PrintHunks(stream, nLinesCommon);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// diff.Diff#distance
Gurax_DeclareProperty_R(Diff, distance)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Diff, distance)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDiff().GetDistance());
}

//------------------------------------------------------------------------------
// VType_Diff
//------------------------------------------------------------------------------
VType_Diff VTYPE_Diff("Diff");

void VType_Diff::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Diff));
	// Assignment of method
	Assign(Gurax_CreateMethod(Diff, EachEdit));
	Assign(Gurax_CreateMethod(Diff, EachHunk));
	Assign(Gurax_CreateMethod(Diff, PrintHunks));
	// Assignment of property
	Assign(Gurax_CreateProperty(Diff, distance));
	//Gura_AssignProperty(diff_at_line, nLinesNew);
	//Gura_AssignProperty(diff_at_line, nLinesOrg);
}

//------------------------------------------------------------------------------
// Value_Diff
//------------------------------------------------------------------------------
VType& Value_Diff::vtype = VTYPE_Diff;

Gurax_EndModuleScope(diff)
