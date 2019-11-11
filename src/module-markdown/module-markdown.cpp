//==============================================================================
// module-markdown.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(markdown)

#if 0
inline bool IsTagNameFirst(char ch) { return IsAlpha(ch); }
inline bool IsTagNameFollower(char ch) { return IsAlpha(ch) || IsDigit(ch) || ch == '.'; }

const int WIDTH_Tab = 4;
const int INDENT_CodeBlock = 4;
#endif

//StringSet g_inlineTagNames;

#if 0
//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// markdown.isinlinetag(tagname:sting)
Gurax_DeclareFunction(isinlinetag)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "tagname", VTYPE_string);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the specified tag is an inlined one.\n");
}

Gurax_ImplementFunction(isinlinetag)
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
	// class realization
	Gurax_RealizeUserClass(document, env.LookupClass(VTYPE_object));
	Gurax_RealizeUserClass(item, env.LookupClass(VTYPE_object));
	// class preparation
	Gurax_PrepareUserClass(document);
	Gurax_PrepareUserClass(item);
	// operator assignment
	Gurax_AssignBinaryOperator(Shl, document, string);
	// function assignment
	Gurax_AssignFunction(isinlinetag);
#endif
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(markdown)
