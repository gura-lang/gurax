//==============================================================================
// BasicVType.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// BasicVType
//------------------------------------------------------------------------------
void BasicVType::Prepare(Frame& frame)
{
	frame.Assign(VTYPE_Object);
	frame.Assign(VTYPE_Any);
	frame.Assign(VTYPE_ArgMapper);
	frame.Assign(VTYPE_ArgMapper_Multiple);
	frame.Assign(VTYPE_ArgSlot);
	frame.Assign(VTYPE_Argument);
	frame.Assign(VTYPE_Array);
	frame.Assign(VTYPE_Attribute);
	frame.Assign(VTYPE_Binary);
	frame.Assign(VTYPE_Bool);
	frame.Assign(VTYPE_CallableMember);
	frame.Assign(VTYPE_Codec);
	frame.Assign(VTYPE_Color);
	frame.Assign(VTYPE_Complex);
	frame.Assign(VTYPE_DateTime);
	frame.Assign(VTYPE_DeclArg);
	frame.Assign(VTYPE_Dict);
	frame.Assign(VTYPE_Directory);
	frame.Assign(VTYPE_Error);
	frame.Assign(VTYPE_ErrorType);
	frame.Assign(VTYPE_Expr);
	frame.Assign(VTYPE_Frame);
	frame.Assign(VTYPE_Function);
	frame.Assign(VTYPE_Help);
	frame.Assign(VTYPE_Iterator);
	frame.Assign(VTYPE_Image);
	frame.Assign(VTYPE_ImageMgr);
	frame.Assign(VTYPE_KeyValuePair);
	frame.Assign(VTYPE_VType);
	frame.Assign(VTYPE_List);
	frame.Assign(VTYPE_MemoryPool);
	frame.Assign(VTYPE_Module);
	frame.Assign(VTYPE_Nil);
	frame.Assign(VTYPE_Number);
	frame.Assign(VTYPE_NumberTrait);
	frame.Assign(VTYPE_Operator);
	frame.Assign(VTYPE_PathMgr);
	frame.Assign(VTYPE_Palette);
	frame.Assign(VTYPE_Pixel);
	frame.Assign(VTYPE_Pointer);
	frame.Assign(VTYPE_PropSlot);
	frame.Assign(VTYPE_PUnit);
	frame.Assign(VTYPE_Quote);
	frame.Assign(VTYPE_Rational);
	frame.Assign(VTYPE_Random);
	frame.Assign(VTYPE_Scope);
	frame.Assign(VTYPE_Semaphore);
	frame.Assign(VTYPE_Stat);
	frame.Assign(VTYPE_Stream);
	frame.Assign(VTYPE_String);
	frame.Assign(VTYPE_StringPtr);
	frame.Assign(VTYPE_Symbol);
	frame.Assign(VTYPE_Template);
	frame.Assign(VTYPE_Thread);
	frame.Assign(VTYPE_TimeDelta);
	frame.Assign(VTYPE_Tuple);
	frame.Assign(VTYPE_Undefined);
	frame.Assign(VTYPE_Vertex);
}

}
