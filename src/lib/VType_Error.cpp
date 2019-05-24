//==============================================================================
// VType_Error.cpp
//==============================================================================
#include "stdafx.h"

#define ImplementErrorTypeProperty(name) \
Gurax_DeclareClassProperty_R(Error, name) { \
	Declare(VTYPE_ErrorType, Flag::None); \
	AddHelp(Gurax_Symbol(en), "An `ErrorType` instance of `" #name "`."); \
} \
Gurax_ImplementClassPropertyGetter(Error, name) { return new Value_ErrorType(ErrorType::name); }

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------
// Error.Raise(errorType:ErrorType):void
Gurax_DeclareClassMethod(Error, Raise)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("errorType", VTYPE_ErrorType, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("msg", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementClassMethod(Error, Raise)
{
	// Arguments
	ArgPicker args(argument);
	const ErrorType& errorType = Value_ErrorType::GetErrorType(args.PickValue());
	const char* msg = args.PickString();
	// Function body
	Error::Issue(errorType, "%s", msg);
	return Value::nil();
}

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
ImplementErrorTypeProperty(ArgumentError)
ImplementErrorTypeProperty(CodecError)
ImplementErrorTypeProperty(ContextError)
ImplementErrorTypeProperty(DeclarationError)
ImplementErrorTypeProperty(DividedByZero)
ImplementErrorTypeProperty(ImportError)
ImplementErrorTypeProperty(IndexError)
ImplementErrorTypeProperty(InvalidOperation)
ImplementErrorTypeProperty(IOError)
ImplementErrorTypeProperty(IteratorError)
ImplementErrorTypeProperty(PropertyError)
ImplementErrorTypeProperty(RangeError)
ImplementErrorTypeProperty(StreamError)
ImplementErrorTypeProperty(SyntaxError)
ImplementErrorTypeProperty(TypeError)
ImplementErrorTypeProperty(ValueError)

//------------------------------------------------------------------------------
// VType_Error
//------------------------------------------------------------------------------
VType_Error VTYPE_Error("Error");

void VType_Error::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Error, Raise));
	// Assignment of property
	Assign(Gurax_CreateProperty(Error, errorType));
	Assign(Gurax_CreateProperty(Error, expr));
	Assign(Gurax_CreateProperty(Error, fileName));
	Assign(Gurax_CreateProperty(Error, lineNo));
	Assign(Gurax_CreateProperty(Error, lineNoBtm));
	Assign(Gurax_CreateProperty(Error, text));
	// Assignment of class property
	Assign(Gurax_CreateClassProperty(Error, ArgumentError));
	Assign(Gurax_CreateClassProperty(Error, CodecError));
	Assign(Gurax_CreateClassProperty(Error, ContextError));
	Assign(Gurax_CreateClassProperty(Error, DeclarationError));
	Assign(Gurax_CreateClassProperty(Error, DividedByZero));
	Assign(Gurax_CreateClassProperty(Error, ImportError));
	Assign(Gurax_CreateClassProperty(Error, InvalidOperation));
	Assign(Gurax_CreateClassProperty(Error, IOError));
	Assign(Gurax_CreateClassProperty(Error, IteratorError));
	Assign(Gurax_CreateClassProperty(Error, PropertyError));
	Assign(Gurax_CreateClassProperty(Error, StreamError));
	Assign(Gurax_CreateClassProperty(Error, SyntaxError));
	Assign(Gurax_CreateClassProperty(Error, TypeError));
	Assign(Gurax_CreateClassProperty(Error, ValueError));
}

//------------------------------------------------------------------------------
// Value_Error
//------------------------------------------------------------------------------
String Value_Error::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%s:%s",
			   GetError().GetErrorType().GetName(),
			   PathName(GetError().GetFileName()).ExtractFileName().c_str());
	int lineNoTop = GetError().GetLineNoTop();
	int lineNoBtm = GetError().GetLineNoBtm();
	if (lineNoTop == lineNoBtm) {
		str.Printf(":%d>", lineNoTop);
	} else {
		str.Printf(":%d:%d>", lineNoTop, lineNoBtm);
	}
	return str;
}

String Value_Error::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

}
