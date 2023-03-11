//==============================================================================
// VType_Scope.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Scope, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Scope, `en)}

${help.ComposeMethodHelp(Scope, `en)}
)""";

//------------------------------------------------------------------------------
// VType_Scope
//------------------------------------------------------------------------------
VType_Scope VTYPE_Scope("Scope");

void VType_Scope::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Scope
//------------------------------------------------------------------------------
VType& Value_Scope::vtype = VTYPE_Scope;

bool Value_Scope::CanEvalAsMethod(const Function& function) const
{
	if (function.IsTypeMethod() || function.IsTypeFunction() ||
			function.IsTypeConstructor() || function.IsTypeStatement()) {
		return true;
	}
	Error::Issue(ErrorType::ValueError, "the function %s must be evaluated with an instance",
						function.MakeFullName().c_str());
	return false;
}

Value* Value_Scope::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	RefPtr<Value> pValue(GetFrame().Retrieve(pSymbol));
	if (pValue) return pValue.release();
	if (notFoundErrorFlag) {
		Error::Issue(ErrorType::PropertyError,
					 "the scope doesn't have a property '%s'", pSymbol->GetName());
	}
	return nullptr;
}

bool Value_Scope::DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	GetFrame().Assign(pSymbol, pValue.release());
	return true;
}

}
