//==============================================================================
// VType_DiffLine.cpp
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
// diff.DiffLine(src1, src2):[icase] {block?}
Gurax_DeclareConstructor(DiffLine)
{
	Declare(VTYPE_DiffLine, Flag::None);
	DeclareArg("src1", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("src2", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(icase));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `diff.DiffLine` instance.");
}

Gurax_ImplementConstructor(DiffLine)
{
	// Arguments
	ArgPicker args(argument);
	Value& src1 = args.PickValue();
	Value& src2 = args.PickValue();
	// Function body
	bool icaseFlag = argument.IsSet(Gurax_Symbol(icase));
	RefPtr<DiffLine> pDiffLine(new DiffLine(icaseFlag));
	if (!pDiffLine->Compose(src1, src2)) return Value::nil();
	return argument.ReturnValue(processor, new Value_DiffLine(pDiffLine.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// diff.DiffLine#EachEditLine() {block?}
Gurax_DeclareMethod(DiffLine, EachEditLine)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that returns stored edit information.\n");
}

Gurax_ImplementMethod(DiffLine, EachEditLine)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	DiffLine& diffLine = valueThis.GetDiffLine();
	RefPtr<Iterator> pIterator(new Iterator_EditLine(diffLine.Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// diff.DiffLine#EachHunkLine(nLinesCommon?:Number) {block?}
Gurax_DeclareMethod(DiffLine, EachHunkLine)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("nLinesCommon", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that returns stored hunk information.\n");
}

Gurax_ImplementMethod(DiffLine, EachHunkLine)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	size_t nLinesCommon = args.IsValid()? args.PickNumberNonNeg<size_t>() : 3;
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_HunkLine(valueThis.GetDiffLine().Reference(), nLinesCommon));
	return argument.ReturnIterator(processor, pIterator.release());
}

// diff.DiffLine#PrintHunkLines(stream?:Stream:w, nLinesCommon?:Number):void
Gurax_DeclareMethod(DiffLine, PrintHunkLines)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	DeclareArg("nLinesCommon", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Prints the unified hunks.\n");
}

Gurax_ImplementMethod(DiffLine, PrintHunkLines)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.IsValid()? args.PickStream() : Basement::Inst.GetStreamCOut();
	size_t nLinesCommon = args.IsValid()? args.PickNumberNonNeg<size_t>() : 3;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	valueThis.GetDiffLine().PrintHunkLines(stream, nLinesCommon);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// diff.DiffLine#distance
Gurax_DeclareProperty_R(DiffLine, distance)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(DiffLine, distance)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDiffLine().GetDistance());
}

//------------------------------------------------------------------------------
// VType_DiffLine
//------------------------------------------------------------------------------
VType_DiffLine VTYPE_DiffLine("DiffLine");

void VType_DiffLine::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(DiffLine));
	// Assignment of method
	Assign(Gurax_CreateMethod(DiffLine, EachEditLine));
	Assign(Gurax_CreateMethod(DiffLine, EachHunkLine));
	Assign(Gurax_CreateMethod(DiffLine, PrintHunkLines));
	// Assignment of property
	Assign(Gurax_CreateProperty(DiffLine, distance));
	//Gura_AssignProperty(diff_at_line, nLinesNew);
	//Gura_AssignProperty(diff_at_line, nLinesOrg);
}

//------------------------------------------------------------------------------
// Value_DiffLine
//------------------------------------------------------------------------------
VType& Value_DiffLine::vtype = VTYPE_DiffLine;

Gurax_EndModuleScope(diff)
