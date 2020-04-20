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
// diff.HunkLine#EachEditLine() {block?}
Gurax_DeclareMethod(HunkLine, EachEditLine)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that returns stored edit information.\n");
}

Gurax_ImplementMethod(HunkLine, EachEditLine)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const HunkLine& hunkLine = valueThis.GetHunkLine();
	RefPtr<Iterator> pIterator(valueThis.GetHunkLine().EachEditLine());
	return argument.ReturnIterator(processor, pIterator.release());
}

// diff.HunkLine#Print(stream?:Stream:w):void
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
	valueThis.GetHunkLine().Print(stream);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// diff.HunkLine#lineNoOrg
Gurax_DeclareProperty_R(HunkLine, lineNoOrg)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(HunkLine, lineNoOrg)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetHunkLine().GetLineNoOrg());
}

// diff.HunkLine#lineNoNew
Gurax_DeclareProperty_R(HunkLine, lineNoNew)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(HunkLine, lineNoNew)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetHunkLine().GetLineNoNew());
}

// diff.HunkLine#nLinesNew
Gurax_DeclareProperty_R(HunkLine, nLinesNew)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(HunkLine, nLinesNew)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetHunkLine().GetNLinesNew());
}

// diff.HunkLine#nLinesOrg
Gurax_DeclareProperty_R(HunkLine, nLinesOrg)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(HunkLine, nLinesOrg)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetHunkLine().GetNLinesOrg());
}

// diff.HunkLine#range
Gurax_DeclareProperty_R(HunkLine, range)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(HunkLine, range)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetHunkLine().MakeRangeString());
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
	Assign(Gurax_CreateMethod(HunkLine, EachEditLine));
	Assign(Gurax_CreateMethod(HunkLine, Print));
	// Assignment of property
	Assign(Gurax_CreateProperty(HunkLine, lineNoOrg));
	Assign(Gurax_CreateProperty(HunkLine, lineNoNew));
	Assign(Gurax_CreateProperty(HunkLine, nLinesOrg));
	Assign(Gurax_CreateProperty(HunkLine, nLinesNew));
	Assign(Gurax_CreateProperty(HunkLine, range));
}

//------------------------------------------------------------------------------
// Value_HunkLine
//------------------------------------------------------------------------------
VType& Value_HunkLine::vtype = VTYPE_HunkLine;

//-----------------------------------------------------------------------------
// Iterator_HunkLine
//-----------------------------------------------------------------------------
Iterator_HunkLine::Iterator_HunkLine(Diff* pDiff, size_t nLinesCommon) :
	_picker(pDiff, nLinesCommon)
{
}

Value* Iterator_HunkLine::DoNextValue()
{
	RefPtr<HunkLine> pHunkLine(_picker.NextHunkLine());
	if (!pHunkLine) return nullptr;
	return new Value_HunkLine(pHunkLine.release());
}

#if 0
HunkLine* Iterator_HunkLine::NextHunkLine()
{
	Diff::SesElemVec& sesElems = _pDiff->GetSesElems();
	if (_iSesElem >= sesElems.size()) return nullptr;
	size_t iSesElemTop = _iSesElem;
	for ( ; _iSesElem < sesElems.size(); _iSesElem++) {
		const Diff::SesElem& sesElem = sesElems[_iSesElem];
		if (sesElem.second.type != dtl::SES_COMMON) break;
	}
	if (_iSesElem >= sesElems.size()) return nullptr;
	size_t iSesElemBegin = (_iSesElem > iSesElemTop + _nLinesCommon)? _iSesElem - _nLinesCommon : iSesElemTop;
	size_t nLines = 0;
	for ( ; _iSesElem < sesElems.size(); _iSesElem++) {
		const Diff::SesElem& sesElem = sesElems[_iSesElem];
		if (sesElem.second.type == dtl::SES_COMMON) {
			if (_nLinesCommon == 0) break;
			nLines++;
			if (nLines >= _nLinesCommon * 2) {
				_iSesElem = _iSesElem + 1 - _nLinesCommon;
				break;
			}
		} else {
			nLines = 0;
		}
	}
	size_t iSesElemEnd = _iSesElem;
	size_t lineNoOrg = 0, lineNoNew = 0;
	size_t nLinesOrg = 0, nLinesNew = 0;
	for (size_t iSesElem = iSesElemBegin; iSesElem < iSesElemEnd; iSesElem++) {
		const Diff::SesElem& sesElem = sesElems[iSesElem];
		if (sesElem.second.beforeIdx > 0) {
			lineNoOrg = sesElem.second.beforeIdx;
			break;
		}
	}
	for (size_t iSesElem = iSesElemBegin; iSesElem < iSesElemEnd; iSesElem++) {
		const Diff::SesElem& sesElem = sesElems[iSesElem];
		if (sesElem.second.afterIdx > 0) {
			lineNoNew = sesElem.second.afterIdx;
			break;
		}
	}
	for (size_t iSesElem = iSesElemBegin; iSesElem < iSesElemEnd; iSesElem++) {
		const Diff::SesElem& sesElem = sesElems[iSesElem];
		if (sesElem.second.type != dtl::SES_ADD) nLinesOrg++;
		if (sesElem.second.type != dtl::SES_DELETE) nLinesNew++;
	}
	return new HunkLine(_pDiff->Reference(), iSesElemBegin, iSesElemEnd,
									lineNoOrg, lineNoNew, nLinesOrg, nLinesNew);
}
#endif

String Iterator_HunkLine::ToString(const StringStyle& ss) const
{
	return "diff.HunkLine";
}

Gurax_EndModuleScope(diff)
