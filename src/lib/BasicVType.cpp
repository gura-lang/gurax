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
	VTYPE_Object.Prepare(frame);
	VTYPE_Any.Prepare(frame);
	VTYPE_ArgMapper.Prepare(frame);
	VTYPE_ArgMapper_Multiple.Prepare(frame);
	VTYPE_ArgSlot.Prepare(frame);
	VTYPE_Argument.Prepare(frame);
	VTYPE_Array.Prepare(frame);
	VTYPE_Attribute.Prepare(frame);
	VTYPE_Binary.Prepare(frame);
	VTYPE_Bool.Prepare(frame);
	VTYPE_CallableMember.Prepare(frame);
	VTYPE_Codec.Prepare(frame);
	VTYPE_Color.Prepare(frame);
	VTYPE_Complex.Prepare(frame);
	VTYPE_DateTime.Prepare(frame);
	VTYPE_Dict.Prepare(frame);
	VTYPE_Directory.Prepare(frame);
	VTYPE_Error.Prepare(frame);
	VTYPE_ErrorType.Prepare(frame);
	VTYPE_Expr.Prepare(frame);
	VTYPE_Frame.Prepare(frame);
	VTYPE_Scope.Prepare(frame);
	VTYPE_Function.Prepare(frame);
	VTYPE_Help.Prepare(frame);
	VTYPE_Iterator.Prepare(frame);
	VTYPE_Image.Prepare(frame);
	VTYPE_ImageMgr.Prepare(frame);
	VTYPE_KeyValuePair.Prepare(frame);
	VTYPE_VType.Prepare(frame);
	VTYPE_List.Prepare(frame);
	VTYPE_MemoryPool.Prepare(frame);
	VTYPE_Module.Prepare(frame);
	VTYPE_Nil.Prepare(frame);
	VTYPE_Number.Prepare(frame);
	VTYPE_NumberTrait.Prepare(frame);
	VTYPE_Operator.Prepare(frame);
	VTYPE_PathMgr.Prepare(frame);
	VTYPE_Palette.Prepare(frame);
	VTYPE_Pixel.Prepare(frame);
	VTYPE_Pointer.Prepare(frame);
	VTYPE_PropSlot.Prepare(frame);
	VTYPE_PUnit.Prepare(frame);
	VTYPE_Quote.Prepare(frame);
	VTYPE_Rational.Prepare(frame);
	VTYPE_Random.Prepare(frame);
	VTYPE_Semaphore.Prepare(frame);
	VTYPE_Stat.Prepare(frame);
	VTYPE_Stream.Prepare(frame);
	VTYPE_String.Prepare(frame);
	VTYPE_StringPtr.Prepare(frame);
	VTYPE_Symbol.Prepare(frame);
	VTYPE_Template.Prepare(frame);
	VTYPE_Thread.Prepare(frame);
	VTYPE_TimeDelta.Prepare(frame);
	VTYPE_Tuple.Prepare(frame);
	VTYPE_Undefined.Prepare(frame);
}

}
