//==============================================================================
// VType_Edit.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(diff.Edit, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(diff.Edit, `en)}

${help.ComposeMethodHelp(diff.Edit, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// diff.Edit#lineNoOrg
Gurax_DeclareProperty_R(Edit, lineNoOrg)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Edit, lineNoOrg)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Diff::SesElem& sesElem = valueThis.GetSesElem();
	return new Value_Number(sesElem.second.beforeIdx);
}

// diff.Edit#lineNoNew
Gurax_DeclareProperty_R(Edit, lineNoNew)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Edit, lineNoNew)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Diff::SesElem& sesElem = valueThis.GetSesElem();
	return new Value_Number(sesElem.second.afterIdx);
}

// diff.Edit#source
Gurax_DeclareProperty_R(Edit, source)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Edit, source)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Diff::SesElem& sesElem = valueThis.GetSesElem();
	return new Value_String(sesElem.first);
}

// diff.Edit#type
Gurax_DeclareProperty_R(Edit, type)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Edit, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Diff::SesElem& sesElem = valueThis.GetSesElem();
	const Symbol* pSymbol =
		(sesElem.second.type == dtl::SES_ADD)? Gurax_Symbol(add) :
		(sesElem.second.type == dtl::SES_DELETE)? Gurax_Symbol(delete_) :
		(sesElem.second.type == dtl::SES_COMMON)? Gurax_Symbol(common) : Symbol::Empty;
	return new Value_Symbol(pSymbol);
}

// diff.Edit#mark
Gurax_DeclareProperty_R(Edit, mark)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Edit, mark)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Diff::SesElem& sesElem = valueThis.GetSesElem();
	const char* str =
		(sesElem.second.type == dtl::SES_ADD)? SES_MARK_ADD :
		(sesElem.second.type == dtl::SES_DELETE)? SES_MARK_DELETE :
		(sesElem.second.type == dtl::SES_COMMON)? SES_MARK_COMMON : "";
	return new Value_String(str);
}

//------------------------------------------------------------------------------
// VType_Edit
//------------------------------------------------------------------------------
VType_Edit VTYPE_Edit("Edit");

void VType_Edit::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(Edit, lineNoOrg));
	Assign(Gurax_CreateProperty(Edit, lineNoNew));
	Assign(Gurax_CreateProperty(Edit, source));
	Assign(Gurax_CreateProperty(Edit, type));
	Assign(Gurax_CreateProperty(Edit, mark));
}

//------------------------------------------------------------------------------
// Value_Edit
//------------------------------------------------------------------------------
VType& Value_Edit::vtype = VTYPE_Edit;

//-----------------------------------------------------------------------------
// Iterator_Edit
//-----------------------------------------------------------------------------
Iterator_Edit::Iterator_Edit(Diff* pDiff, size_t iSesElemBegin, size_t iSesElemEnd) :
	_pDiff(pDiff), _iSesElemBegin(iSesElemBegin), _iSesElemEnd(iSesElemEnd), _iSesElem(iSesElemBegin)
{
}

Iterator_Edit::Iterator_Edit(Diff* pDiff) :
	Iterator_Edit(pDiff, 0, pDiff->GetSesElems().size())
{
}

Value* Iterator_Edit::DoNextValue()
{
	const Diff::SesElemVec& sesElems = _pDiff->GetSesElems();
	if (_iSesElem >= _iSesElemEnd) return nullptr;
	RefPtr<Value> pValue(new Value_Edit(_pDiff->Reference(), _iSesElem));
	_iSesElem++;
	return pValue.release();
}

String Iterator_Edit::ToString(const StringStyle& ss) const
{
	return "diff.Edit";
}

Gurax_EndModuleScope(diff)
