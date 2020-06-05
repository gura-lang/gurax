//==============================================================================
// VType_PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

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
// Implementation of method
//------------------------------------------------------------------------------
// PUnit#ToString(seqIdOffset?:number)
Gurax_DeclareMethod(PUnit, ToString)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("seqIdOffset", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethod(PUnit, ToString)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const PUnit* pPUnit = valueThis.GetPUnit();
	// Arguments
	ArgPicker args(argument);
	int seqIdOffset = args.IsValid()? args.PickNumber<Int>() : 0;
	// Function body
	RefPtr<Value> pValue(new Value_String(pPUnit->ToString(seqIdOffset)));
	return pValue.release();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
Gurax_DeclareProperty_R(PUnit, seqId)
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementPropertyGetter(PUnit, seqId)
{
	auto& valueThis = GetValueThis(valueTarget);
	const PUnit* pPUnit = valueThis.GetPUnit();
	return new Value_Number(pPUnit->GetSeqId());
}

//------------------------------------------------------------------------------
// VType_PUnit
//------------------------------------------------------------------------------
VType_PUnit VTYPE_PUnit("PUnit");

void VType_PUnit::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(PUnit, ToString));
	// Assignment of property
	Assign(Gurax_CreateProperty(PUnit, seqId));
}

//------------------------------------------------------------------------------
// Value_PUnit
//------------------------------------------------------------------------------
VType& Value_PUnit::vtype = VTYPE_PUnit;

//------------------------------------------------------------------------------
// Iterator_PUnit
//------------------------------------------------------------------------------
Iterator_PUnit::Iterator_PUnit(const PUnit* pPUnit, const PUnit* pPUnitSentinel) :
	_pPUnit(pPUnit), _pPUnitSentinel(pPUnitSentinel)
{}

size_t Iterator_PUnit::GetLength() const
{
	const PUnit* pPUnit = _pPUnit;
	if (!pPUnit || _pPUnit == _pPUnitSentinel) return 0;
	for ( ; pPUnit && pPUnit->IsBridge(); pPUnit = _pPUnit->GetPUnitNext()) ;
	size_t cnt = 0;
	for ( ; pPUnit && pPUnit != _pPUnitSentinel; pPUnit = pPUnit->GetPUnitNext(), ++cnt) ;
	return cnt;
}

Value* Iterator_PUnit::DoNextValue()
{
	if (!_pPUnit || _pPUnit == _pPUnitSentinel) return nullptr;
	for ( ; _pPUnit->IsBridge(); _pPUnit = _pPUnit->GetPUnitNext()) ;
	if (!_pPUnit || _pPUnit == _pPUnitSentinel) return nullptr;
	RefPtr<Value> pValue(new Value_PUnit(_pPUnit));
	_pPUnit = _pPUnit->GetPUnitNext();
	return pValue.release();
}

String Iterator_PUnit::ToString(const StringStyle& ss) const
{
	String str;
	str += "PUnit";
	return str;
}

}
