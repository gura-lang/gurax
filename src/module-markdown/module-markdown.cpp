//==============================================================================
// module-markdown.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(markdown)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// markdown.IsInlineTag(tagName:Sting)
Gurax_DeclareFunction(IsInlineTag)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("tagName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if the specified tag is an inlined one.
)**");
}

Gurax_ImplementFunction(IsInlineTag)
{
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	// Function body
	return new Value_Bool(IsInlineTagName(str));
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
	// Initialization
	InitInlineTagNames();
	// Assignment of VType
	Assign(VTYPE_Document);
	Assign(VTYPE_Item);
	// Assignment of function
	Assign(Gurax_CreateFunction(IsInlineTag));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(markdown)
