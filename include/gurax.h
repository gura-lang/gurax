//==============================================================================
// gurax.h
//==============================================================================
#ifndef GURAX_H
#define GURAX_H

//#include "gurax/Array.h"
#include "gurax/ArgFeeder.h"
#include "gurax/ArgPicker.h"
#include "gurax/ArgSlot.h"
#include "gurax/Argument.h"
#include "gurax/Attribute.h"
#include "gurax/Basement.h"
#include "gurax/BasicFunction.h"
#include "gurax/BasicIterator.h"
#include "gurax/BasicPointer.h"
#include "gurax/BasicStatement.h"
#include "gurax/BasicStream.h"
#include "gurax/Binary.h"
#include "gurax/Codec.h"
#include "gurax/Color.h"
#include "gurax/CommandLine.h"
#include "gurax/Common.h"
#include "gurax/Complex.h"
#include "gurax/Composer.h"
#include "gurax/DateTime.h"
#include "gurax/DeclArg.h"
#include "gurax/DeclBlock.h"
#include "gurax/DeclCallable.h"
#include "gurax/Directory.h"
#include "gurax/DottedSymbol.h"
#include "gurax/Error.h"
#include "gurax/Expr.h"
#include "gurax/Formatter.h"
#include "gurax/Frame.h"
#include "gurax/Function.h"
#include "gurax/FunctionCustom.h"
#include "gurax/Help.h"
#include "gurax/Image.h"
#include "gurax/ImageMgr.h"
#include "gurax/Index.h"
#include "gurax/Iterator.h"
#include "gurax/Math.h"
#include "gurax/Memory.h"
#include "gurax/MemoryPool.h"
#include "gurax/Number.h"
#include "gurax/OAL.h"
#include "gurax/Operator.h"
#include "gurax/PackedNumber.h"
#include "gurax/Packer.h"
#include "gurax/Palette.h"
#include "gurax/Parser.h"
#include "gurax/PathMgr.h"
#include "gurax/PathName.h"
#include "gurax/Pixel.h"
#include "gurax/Pointer.h"
#include "gurax/Processor.h"
#include "gurax/PropSlot.h"
#include "gurax/PropSlotCustom.h"
#include "gurax/PUnit.h"
#include "gurax/Random.h"
#include "gurax/Rational.h"
#include "gurax/Referable.h"
#include "gurax/Stat.h"
#include "gurax/Stream.h"
#include "gurax/String.h"
#include "gurax/StringPicker.h"
#include "gurax/StringStyle.h"
#include "gurax/SuffixMgr.h"
#include "gurax/Symbol.h"
#include "gurax/Symbols.h"
#include "gurax/Template.h"
#include "gurax/TimeDelta.h"
#include "gurax/Token.h"
#include "gurax/Tokenizer.h"
#include "gurax/Value.h"
#include "gurax/ValueDeque.h"
#include "gurax/ValueDict.h"
#include "gurax/ValueList.h"
#include "gurax/ValueMap.h"
#include "gurax/ValueOwner.h"
#include "gurax/ValueTypedOwner.h"
#include "gurax/Version.h"
#include "gurax/VType.h"
#include "gurax/VTypeCustom.h"
#include "gurax/VType_Any.h"
//#include "gurax/VType_Array.h"
#include "gurax/VType_ArgMapper.h"
#include "gurax/VType_ArgMapper_Multiple.h"
#include "gurax/VType_ArgSlot.h"
#include "gurax/VType_Argument.h"
#include "gurax/VType_Attribute.h"
#include "gurax/VType_Binary.h"
#include "gurax/VType_Bool.h"
#include "gurax/VType_CallableMember.h"
#include "gurax/VType_Codec.h"
#include "gurax/VType_Color.h"
#include "gurax/VType_Complex.h"
#include "gurax/VType_DateTime.h"
#include "gurax/VType_Dict.h"
#include "gurax/VType_Directory.h"
#include "gurax/VType_Error.h"
#include "gurax/VType_ErrorType.h"
#include "gurax/VType_Expr.h"
#include "gurax/VType_Frame.h"
#include "gurax/VType_Function.h"
#include "gurax/VType_Help.h"
#include "gurax/VType_Image.h"
#include "gurax/VType_ImageMgr.h"
#include "gurax/VType_Index.h"
#include "gurax/VType_Iterator.h"
#include "gurax/VType_KeyValuePair.h"
#include "gurax/VType_List.h"
#include "gurax/VType_MemoryPool.h"
#include "gurax/VType_Module.h"
#include "gurax/VType_Nil.h"
#include "gurax/VType_Number.h"
#include "gurax/VType_Object.h"
#include "gurax/VType_Palette.h"
#include "gurax/VType_PathMgr.h"
#include "gurax/VType_Pixel.h"
#include "gurax/VType_Pointer.h"
#include "gurax/VType_PropSlot.h"
#include "gurax/VType_PUnit.h"
#include "gurax/VType_Quote.h"
#include "gurax/VType_Random.h"
#include "gurax/VType_Rational.h"
#include "gurax/VType_Stat.h"
#include "gurax/VType_Stream.h"
#include "gurax/VType_String.h"
#include "gurax/VType_StringPtr.h"
#include "gurax/VType_Symbol.h"
#include "gurax/VType_Template.h"
#include "gurax/VType_TimeDelta.h"
#include "gurax/VType_Undefined.h"
#include "gurax/VType_VType.h"
#include "gurax/Imp_Iterator.h"
#include "gurax/Imp_Number.h"
#include "gurax/Imp_VType_Number.h"

namespace Gurax {
GURAX_DLLDECLARE bool Initialize(int& argc, char* argv[]);
}

// Undefines GURAX_DLLDECLARE
#undef GURAX_DLLDECLARE
#define GURAX_DLLDECLARE

#endif
