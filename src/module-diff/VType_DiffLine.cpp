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
// diff.DiffLine#EachHunk() {block?}
Gurax_DeclareMethod(DiffLine, EachHunk)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that returns stored hunk information.\n");
}

Gurax_ImplementMethod(DiffLine, EachHunk)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_HunkLine(valueThis.GetDiffLine().Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// diff.DiffLine#propSkeleton
Gurax_DeclareProperty_R(DiffLine, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(DiffLine, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
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
	Assign(Gurax_CreateMethod(DiffLine, EachHunk));
	// Assignment of property
	Assign(Gurax_CreateProperty(DiffLine, propSkeleton));
	//Gura_AssignProperty(diff_at_line, distance);
	//Gura_AssignProperty(diff_at_line, edits);
	//Gura_AssignProperty(diff_at_line, nlines_at_new);
	//Gura_AssignProperty(diff_at_line, nlines_at_org);
}

//------------------------------------------------------------------------------
// Value_DiffLine
//------------------------------------------------------------------------------
VType& Value_DiffLine::vtype = VTYPE_DiffLine;

Gurax_EndModuleScope(diff)
