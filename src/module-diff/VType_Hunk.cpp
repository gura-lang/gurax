//==============================================================================
// VType_Hunk.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(diff.Hunk, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(diff.Hunk, `en)}

${help.ComposeMethodHelp(diff.Hunk, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// diff.Hunk#EachEdit() {block?}
Gurax_DeclareMethod(Hunk, EachEdit)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates an iterator that returns stored edit information.
)**");
}

Gurax_ImplementMethod(Hunk, EachEdit)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const Hunk& Hunk = valueThis.GetHunk();
	RefPtr<Iterator> pIterator(valueThis.GetHunk().EachEdit());
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// diff.Hunk#lineNoOrg
Gurax_DeclareProperty_R(Hunk, lineNoOrg)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Hunk, lineNoOrg)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetHunk().GetLineNoOrg());
}

// diff.Hunk#lineNoNew
Gurax_DeclareProperty_R(Hunk, lineNoNew)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Hunk, lineNoNew)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetHunk().GetLineNoNew());
}

// diff.Hunk#nLinesNew
Gurax_DeclareProperty_R(Hunk, nLinesNew)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Hunk, nLinesNew)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetHunk().GetNLinesNew());
}

// diff.Hunk#nLinesOrg
Gurax_DeclareProperty_R(Hunk, nLinesOrg)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Hunk, nLinesOrg)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetHunk().GetNLinesOrg());
}

// diff.Hunk#range
Gurax_DeclareProperty_R(Hunk, range)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Hunk, range)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetHunk().MakeRangeString());
}

//------------------------------------------------------------------------------
// VType_Hunk
//------------------------------------------------------------------------------
VType_Hunk VTYPE_Hunk("Hunk");

void VType_Hunk::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Hunk, EachEdit));
	// Assignment of property
	Assign(Gurax_CreateProperty(Hunk, lineNoOrg));
	Assign(Gurax_CreateProperty(Hunk, lineNoNew));
	Assign(Gurax_CreateProperty(Hunk, nLinesOrg));
	Assign(Gurax_CreateProperty(Hunk, nLinesNew));
	Assign(Gurax_CreateProperty(Hunk, range));
}

//------------------------------------------------------------------------------
// Value_Hunk
//------------------------------------------------------------------------------
VType& Value_Hunk::vtype = VTYPE_Hunk;

//-----------------------------------------------------------------------------
// Iterator_Hunk
//-----------------------------------------------------------------------------
Iterator_Hunk::Iterator_Hunk(Diff* pDiff, size_t nLinesCommon) :
	_picker(pDiff, nLinesCommon)
{
}

Value* Iterator_Hunk::DoNextValue()
{
	RefPtr<Hunk> pHunk(_picker.NextHunk());
	if (!pHunk) return nullptr;
	return new Value_Hunk(pHunk.release());
}

#if 0
Hunk* Iterator_Hunk::NextHunk()
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
	return new Hunk(_pDiff->Reference(), iSesElemBegin, iSesElemEnd,
									lineNoOrg, lineNoNew, nLinesOrg, nLinesNew);
}
#endif

String Iterator_Hunk::ToString(const StringStyle& ss) const
{
	return "diff.Hunk";
}

Gurax_EndModuleScope(diff)
