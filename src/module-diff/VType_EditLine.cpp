//==============================================================================
// VType_EditLine.cpp
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
// diff.EditLine#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(EditLine, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(EditLine, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// diff.EditLine#source
Gurax_DeclareProperty_R(EditLine, source)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(EditLine, source)
{
	auto& valueThis = GetValueThis(valueTarget);
	const DiffLine::SesElem& sesElem = valueThis.GetSesElem();
	return new Value_String(sesElem.first);
}

// diff.EditLine#type
Gurax_DeclareProperty_R(EditLine, type)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(EditLine, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	const DiffLine::SesElem& sesElem = valueThis.GetSesElem();
	const Symbol* pSymbol =
		(sesElem.second.type == dtl::SES_ADD)? Gurax_Symbol(add) :
		(sesElem.second.type == dtl::SES_DELETE)? Gurax_Symbol(delete_) :
		(sesElem.second.type == dtl::SES_COMMON)? Gurax_Symbol(common) : Symbol::Empty;
	return new Value_Symbol(pSymbol);
}

// diff.EditLine#mark
Gurax_DeclareProperty_R(EditLine, mark)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(EditLine, mark)
{
	auto& valueThis = GetValueThis(valueTarget);
	const DiffLine::SesElem& sesElem = valueThis.GetSesElem();
	const char* str =
		(sesElem.second.type == dtl::SES_ADD)? SES_MARK_ADD :
		(sesElem.second.type == dtl::SES_DELETE)? SES_MARK_DELETE :
		(sesElem.second.type == dtl::SES_COMMON)? SES_MARK_COMMON : "";
	return new Value_String(str);
}

//------------------------------------------------------------------------------
// VType_EditLine
//------------------------------------------------------------------------------
VType_EditLine VTYPE_EditLine("EditLine");

void VType_EditLine::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(EditLine, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(EditLine, source));
	Assign(Gurax_CreateProperty(EditLine, type));
	Assign(Gurax_CreateProperty(EditLine, mark));
}

//------------------------------------------------------------------------------
// Value_EditLine
//------------------------------------------------------------------------------
VType& Value_EditLine::vtype = VTYPE_EditLine;

//-----------------------------------------------------------------------------
// Iterator_EditLine
//-----------------------------------------------------------------------------
Iterator_EditLine::Iterator_EditLine(DiffLine* pDiffLine, size_t iSesElemBegin, size_t iSesElemEnd) :
	_iSesElemBegin(iSesElemBegin), _iSesElemEnd(iSesElemEnd), _iSesElem(iSesElemBegin)
{
}

Iterator_EditLine::Iterator_EditLine(DiffLine* pDiffLine) :
	Iterator_EditLine(pDiffLine, 0, pDiffLine->GetSesElems().size())
{
}

Value* Iterator_EditLine::DoNextValue()
{
	const DiffLine::SesElemVec& sesElems = _pDiffLine->GetSesElems();
	if (_iSesElem == _iSesElemEnd) return nullptr;
	RefPtr<Value> pValue(new Value_EditLine(_pDiffLine->Reference(), sesElems[_iSesElem]));
	_iSesElem++;
	return pValue.release();
}

String Iterator_EditLine::ToString(const StringStyle& ss) const
{
	return "diff.EditLine";
}

Gurax_EndModuleScope(diff)
