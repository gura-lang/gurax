//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(diff)

const char* GetEditMark_Normal(dtl::edit_t editType)
{
	return (editType == dtl::SES_ADD)? ">" : (editType == dtl::SES_DELETE)? "<" : " ";
}

const char* GetEditMark_Context(dtl::edit_t editType)
{
	//return (editType == EDITTYPE_Add)? "+" : (editType == EDITTYPE_Delete)? "-" :
	//	(editType == EDITTYPE_Change)? "!" : " ";
    return "";
}

const char* GetEditMark_Unified(dtl::edit_t editType)
{
	return (editType == dtl::SES_ADD)? "+" : (editType == dtl::SES_DELETE)? "-" : " ";
}

Gurax_EndModuleScope(diff)
