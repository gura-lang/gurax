//==============================================================================
// module-error.cpp
//==============================================================================
#include "stdafx.h"

#define ImplementErrorTypeProperty(name) \
Gurax_DeclareModuleProperty_R(name) { Declare(VTYPE_ErrorType, Flag::None); } \
Gurax_ImplementModulePropertyGetter(name) { return new Value_ErrorType(ErrorType::name); }

Gurax_BeginModule(error)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
ImplementErrorTypeProperty(ArgumentError)
ImplementErrorTypeProperty(CodecError)
ImplementErrorTypeProperty(ContextError)
ImplementErrorTypeProperty(DeclarationError)
ImplementErrorTypeProperty(DividedByZero)
ImplementErrorTypeProperty(IndexError)
ImplementErrorTypeProperty(InvalidOperation)
ImplementErrorTypeProperty(IteratorError)
ImplementErrorTypeProperty(ModuleError)
ImplementErrorTypeProperty(StreamError)
ImplementErrorTypeProperty(SyntaxError)
ImplementErrorTypeProperty(TypeError)
ImplementErrorTypeProperty(ValueError)

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return true;
}

Gurax_ModulePrepare()
{
	// Assignment of property
	Assign(Gurax_CreateModuleProperty(ArgumentError));
	Assign(Gurax_CreateModuleProperty(CodecError));
	Assign(Gurax_CreateModuleProperty(ContextError));
	Assign(Gurax_CreateModuleProperty(DeclarationError));
	Assign(Gurax_CreateModuleProperty(DividedByZero));
	Assign(Gurax_CreateModuleProperty(IndexError));
	Assign(Gurax_CreateModuleProperty(InvalidOperation));
	Assign(Gurax_CreateModuleProperty(IteratorError));
	Assign(Gurax_CreateModuleProperty(ModuleError));
	Assign(Gurax_CreateModuleProperty(StreamError));
	Assign(Gurax_CreateModuleProperty(SyntaxError));
	Assign(Gurax_CreateModuleProperty(TypeError));
	Assign(Gurax_CreateModuleProperty(ValueError));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(error)
