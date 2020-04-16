//==============================================================================
// VType_HunkLine.cpp
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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// diff.HunkLine#Print(stream?:Stream:w)
Gurax_DeclareMethod(HunkLine, Print)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	AddHelp(
		Gurax_Symbol(en),
		"Prints the unified hunk.\n");
}

Gurax_ImplementMethod(HunkLine, Print)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.IsValid()? args.PickStream() : Basement::Inst.GetStreamCOut();
	// Function body
	DiffLine::PrintHunk(stream, valueThis.GetHunk());
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// diff.HunkLine#propSkeleton
Gurax_DeclareProperty_R(HunkLine, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(HunkLine, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_HunkLine
//------------------------------------------------------------------------------
VType_HunkLine VTYPE_HunkLine("HunkLine");

void VType_HunkLine::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(HunkLine, Print));
	// Assignment of property
	Assign(Gurax_CreateProperty(HunkLine, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_HunkLine
//------------------------------------------------------------------------------
VType& Value_HunkLine::vtype = VTYPE_HunkLine;

//-----------------------------------------------------------------------------
// Iterator_HunkLine
//-----------------------------------------------------------------------------
Iterator_HunkLine::Iterator_HunkLine(DiffLine* pDiffLine) : _pDiffLine(pDiffLine), _iHunk(0)
{
}

Value* Iterator_HunkLine::DoNextValue()
{
	if (_iHunk >= _pDiffLine->GetHunkVec().size()) return nullptr;
	RefPtr<Value> pValue(new Value_HunkLine(_pDiffLine->Reference(), _iHunk));
	_iHunk++;
	return pValue.release();
}

String Iterator_HunkLine::ToString(const StringStyle& ss) const
{
	return "diff.HunkLine";
}

Gurax_EndModuleScope(diff)
