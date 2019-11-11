//==============================================================================
// module-markdown.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(markdown)

#if 0
//-----------------------------------------------------------------------------
// Implementation of function
//-----------------------------------------------------------------------------
// markdown.isinlinetag(tagname:sting)
Gura_DeclareFunction(isinlinetag)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "tagname", VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"Returns `true` if the specified tag is an inlined one.\n");
}

Gura_ImplementFunction(isinlinetag)
{
	return Value(IsInlineTagName(arg.GetString(0)));
}
#endif

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// re.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Adds up the given two numbers and returns the result.");
}

Gurax_ImplementFunction(Test)
{
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	Int num = args.PickNumber<Int>();
	// Function body
	return new Value_String(String::Repeat(str, num));
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of VType
	Assign(VTYPE_Document);
	Assign(VTYPE_Item);
	// Assignment of function
	Assign(Gurax_CreateFunction(Test));
#if 0
	// symbol realization
	Gura_RealizeUserSymbol(root);
	Gura_RealizeUserSymbol(refs);
	Gura_RealizeUserSymbol(type);
	Gura_RealizeUserSymbol(text);
	Gura_RealizeUserSymbol(children);
	Gura_RealizeUserSymbol(url);
	Gura_RealizeUserSymbol(title);
	Gura_RealizeUserSymbol(attrs);
	Gura_RealizeUserSymbol(align);
	// class realization
	Gura_RealizeUserClass(document, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(item, env.LookupClass(VTYPE_object));
	// class preparation
	Gura_PrepareUserClass(document);
	Gura_PrepareUserClass(item);
	// operator assignment
	Gura_AssignBinaryOperator(Shl, document, string);
	// function assignment
	Gura_AssignFunction(isinlinetag);
#endif
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(markdown)
