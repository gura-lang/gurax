//==============================================================================
// VType_Frame.cpp
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

//------------------------------------------------------------------------------
// VType_Frame
//------------------------------------------------------------------------------
VType_Frame VTYPE_Frame("Frame");

void VType_Frame::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Frame
//------------------------------------------------------------------------------
VType& Value_Frame::vtype = VTYPE_Frame;

bool Value_Frame::CanEvalAsMethod(const Function& function) const
{
	if (function.IsTypeMethod() || function.IsTypeFunction() ||
			function.IsTypeConstructor() || function.IsTypeStatement()) {
		return true;
	}
	Error::Issue(ErrorType::ValueError, "the function %s must be evaluated with an instance",
						function.MakeFullName().c_str());
	return false;
}

Value* Value_Frame::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	RefPtr<Value> pValue(GetFrame().Retrieve(pSymbol));
	if (pValue) return pValue.release();
	if (notFoundErrorFlag) {
		Error::Issue(ErrorType::PropertyError,
					 "the frame doesn't have a property '%s'", pSymbol->GetName());
	}
	return nullptr;
}

bool Value_Frame::DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	GetFrame().Assign(pSymbol, pValue.release());
	return true;
}

}
