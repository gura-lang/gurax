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
// diff.EditLine#propSkeleton
Gurax_DeclareProperty_R(EditLine, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(EditLine, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
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
	Assign(Gurax_CreateProperty(EditLine, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_EditLine
//------------------------------------------------------------------------------
VType& Value_EditLine::vtype = VTYPE_EditLine;

//-----------------------------------------------------------------------------
// Iterator_EditLine
//-----------------------------------------------------------------------------
Iterator_EditLine::Iterator_EditLine(DiffLine* pDiffLine, const DiffLine::SesElemVec& sesElems) :
	_pDiffLine(pDiffLine), _sesElems(sesElems), _iSesElem(0)
{
}

Value* Iterator_EditLine::DoNextValue()
{
	if (_iSesElem >= _sesElems.size()) return nullptr;
	RefPtr<Value> pValue(new Value_EditLine(_pDiffLine->Reference(), _sesElems[_iSesElem]));
	_iSesElem++;
	return pValue.release();
}

String Iterator_EditLine::ToString(const StringStyle& ss) const
{
	return "diff.EditLine";
}

Gurax_EndModuleScope(diff)
