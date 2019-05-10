//==============================================================================
// VType_Error.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Error#errorType
Gurax_DeclareProperty_R(Error, errorType)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `ErrorType` instance associated with the error.\n");
}

Gurax_ImplementPropertyGetter(Error, errorType)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_ErrorType(valueThis.GetError().GetErrorType());
}

// Error#expr
Gurax_DeclareProperty_R(Error, expr)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `Expr` instance that caused the error.\n");
}

Gurax_ImplementPropertyGetter(Error, expr)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Expr(valueThis.GetError().GetExpr().Reference());
}

// Error#fileName
Gurax_DeclareProperty_R(Error, fileName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The name of a file in which the error happened.");
}

Gurax_ImplementPropertyGetter(Error, fileName)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetError().GetFileName());
}

// Error#lineNo
Gurax_DeclareProperty_R(Error, lineNo)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The line number at which the error happened.");
}

Gurax_ImplementPropertyGetter(Error, lineNo)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetError().GetLineNoTop());
}

// Error#lineNoBtm
Gurax_DeclareProperty_R(Error, lineNoBtm)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The last line number of the expression region that causes the error.");
}

Gurax_ImplementPropertyGetter(Error, lineNoBtm)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetError().GetLineNoBtm());
}

// Error#text
Gurax_DeclareProperty_R(Error, text)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The text of the error.");
}

Gurax_ImplementPropertyGetter(Error, text)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetError().GetText());
}

//------------------------------------------------------------------------------
// Implementation of class property
//------------------------------------------------------------------------------
// Error.SyntaxError
Gurax_DeclareClassProperty_R(Error, SyntaxError)
{
	Declare(VTYPE_ErrorType, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `ErrorType` instance of `SyntaxError`.");
}

Gurax_ImplementClassPropertyGetter(Error, SyntaxError)
{
	return new Value_ErrorType(ErrorType::SyntaxError);
}

//------------------------------------------------------------------------------
// VType_Error
//------------------------------------------------------------------------------
VType_Error VTYPE_Error("Error");

void VType_Error::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
	// Assignment of property
	Assign(Gurax_CreateProperty(Error, errorType));
	Assign(Gurax_CreateProperty(Error, expr));
	Assign(Gurax_CreateProperty(Error, fileName));
	Assign(Gurax_CreateProperty(Error, lineNo));
	Assign(Gurax_CreateProperty(Error, lineNoBtm));
	Assign(Gurax_CreateProperty(Error, text));
	// Assignment of class property
	Assign(Gurax_CreateClassProperty(Error, SyntaxError));
}

//------------------------------------------------------------------------------
// Value_Error
//------------------------------------------------------------------------------
String Value_Error::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetError().GetErrorType().GetName();
	str += ">";
	return str;
}

String Value_Error::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

}
