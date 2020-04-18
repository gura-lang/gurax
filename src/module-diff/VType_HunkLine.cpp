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
// diff.HunkLine#EachEdit(symbol:Symbol) {block?}
Gurax_DeclareMethod(HunkLine, EachEdit)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that returns stored edit information.\n");
}

Gurax_ImplementMethod(HunkLine, EachEdit)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	//SesElemVec* pSesElems =
	//	pSymbol->IsIdentical(Gurax_Symbol()
	//const DiffLine::Hunk& hunk = valueThis.GetHunk();
	//RefPtr<Iterator> pIterator(new Iterator_EditLine(valueThis.GetDiffLine().Reference(), hunk.common[0]));
	//return argument.ReturnIterator(processor, pIterator.release());
	return Value::nil();
}

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
	//DiffLine::PrintHunk(stream, valueThis.GetHunk());
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
	Assign(Gurax_CreateMethod(HunkLine, EachEdit));
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
Iterator_HunkLine::Iterator_HunkLine(DiffLine* pDiffLine, size_t nLinesCommon) :
	_pDiffLine(pDiffLine), _nLinesCommon(nLinesCommon), _iSesElem(0)
{
}

Value* Iterator_HunkLine::DoNextValue()
{
	DiffLine::HunkVec& hunks = _pDiffLine->GetHunkVec();
	//if (_iHunk >= hunks.size()) return nullptr;
	//RefPtr<Value> pValue(new Value_HunkLine(_pDiffLine->Reference(), hunks[_iHunk]));
	//_iHunk++;
	//return pValue.release();
	return Value::nil();
}

HunkLine* Iterator_HunkLine::NextHunk()
{
	DiffLine::SesElemVec& sesElems = _pDiffLine->GetSesElemVec();
	if (_iSesElem >= sesElems.size()) return false;
	size_t iSesElemTop = _iSesElem;
	for ( ; _iSesElem < sesElems.size(); _iSesElem++) {
		const DiffLine::SesElem& sesElem = sesElems[_iSesElem];
		if (sesElem.second.type != dtl::SES_COMMON) break;
	}
	if (_iSesElem == sesElems.size()) return nullptr;
	size_t iSesElemBegin = (_iSesElem > iSesElemTop + _nLinesCommon)? _iSesElem - _nLinesCommon : iSesElemTop;
	size_t nLines = 0;
	for ( ; _iSesElem < sesElems.size(); _iSesElem++) {
		const DiffLine::SesElem& sesElem = sesElems[_iSesElem];
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
		const DiffLine::SesElem& sesElem = sesElems[_iSesElem];
		if (sesElem.second.beforeIdx > 0) {
			lineNoOrg = sesElem.second.beforeIdx;
			break;
		}
	}
	for (size_t iSesElem = iSesElemBegin; iSesElem < iSesElemEnd; iSesElem++) {
		const DiffLine::SesElem& sesElem = sesElems[_iSesElem];
		if (sesElem.second.afterIdx > 0) {
			lineNoNew = sesElem.second.afterIdx;
			break;
		}
	}
	for (size_t iSesElem = iSesElemBegin; iSesElem < iSesElemEnd; iSesElem++) {
		const DiffLine::SesElem& sesElem = sesElems[_iSesElem];
		if (sesElem.second.type != dtl::SES_ADD) nLinesOrg++;
		if (sesElem.second.type != dtl::SES_DELETE) nLinesNew++;
	}
#if 0
	do {
		const Edit &edit = GetEdit(pHunk->idxEditBegin);
		if (pHunk->linenoOrg == 0 && pHunk->idxEditBegin > 0) {
			const Edit &edit = GetEdit(pHunk->idxEditBegin - 1);
			pHunk->linenoOrg = edit.second.beforeIdx;
		}
		if (pHunk->linenoNew == 0 && pHunk->idxEditBegin > 0) {
			const Edit &edit = GetEdit(pHunk->idxEditBegin - 1);
			pHunk->linenoNew = edit.second.afterIdx;
		}
	} while (0);
#endif
	return new HunkLine(_pDiffLine->Reference(), iSesElemBegin, iSesElemEnd,
									lineNoOrg, lineNoNew, nLinesOrg, nLinesNew);
}

String Iterator_HunkLine::ToString(const StringStyle& ss) const
{
	return "diff.HunkLine";
}

Gurax_EndModuleScope(diff)
