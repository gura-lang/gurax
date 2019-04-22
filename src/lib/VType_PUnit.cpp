//==============================================================================
// VType_PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// PUnit#ToString(seqIdOffset?:number)
Gurax_DeclareMethod(PUnit, ToString)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("seqIdOffset", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementMethod(PUnit, ToString)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const PUnit* pPUnit = valueThis.GetPUnit();
	// Arguments
	ArgPicker args(argument);
	int seqIdOffset = args.IsDefined()? args.PickInt() : 0;
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
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
	// Assignment of method
	Assign(Gurax_CreateMethod(PUnit, ToString));
	// Assignment of property
	Assign(Gurax_CreateProperty(PUnit, seqId));
}

//------------------------------------------------------------------------------
// Value_PUnit
//------------------------------------------------------------------------------

}
