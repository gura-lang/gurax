//==============================================================================
// gurax.h
//==============================================================================
#ifndef GURAX_H
#define GURAX_H

#include "gurax/ArgSlot.h"
#include "gurax/Argument.h"
#include "gurax/Attribute.h"
#include "gurax/Binary.h"
#include "gurax/Codec.h"
#include "gurax/Common.h"
#include "gurax/Context.h"
#include "gurax/DateTime.h"
#include "gurax/DeclArg.h"
#include "gurax/DeclCaller.h"
#include "gurax/DottedSymbol.h"
#include "gurax/Environment.h"
#include "gurax/Error.h"
#include "gurax/Expr.h"
#include "gurax/Formatter.h"
#include "gurax/Frame.h"
#include "gurax/Function.h"
#include "gurax/Help.h"
#include "gurax/Iterator.h"
#include "gurax/MemoryPool.h"
#include "gurax/Operator.h"
#include "gurax/Operators.h"
#include "gurax/Parser.h"
#include "gurax/Random.h"
#include "gurax/Referable.h"
#include "gurax/Stream.h"
#include "gurax/Streams.h"
#include "gurax/String.h"
#include "gurax/Symbol.h"
#include "gurax/Symbols.h"
#include "gurax/Template.h"
#include "gurax/TimeDelta.h"
#include "gurax/Token.h"
#include "gurax/Tokenizer.h"
#include "gurax/Value.h"
#include "gurax/Value_Any.h"
#include "gurax/Value_ArgSlot.h"
#include "gurax/Value_Argument.h"
#include "gurax/Value_Attribute.h"
#include "gurax/Value_Binary.h"
#include "gurax/Value_Bool.h"
#include "gurax/Value_DateTime.h"
#include "gurax/Value_Dict.h"
#include "gurax/Value_Expr.h"
#include "gurax/Value_Function.h"
#include "gurax/Value_Iterator.h"
#include "gurax/Value_List.h"
#include "gurax/Value_Member.h"
#include "gurax/Value_Module.h"
#include "gurax/Value_Nil.h"
#include "gurax/Value_Number.h"
#include "gurax/Value_Object.h"
#include "gurax/Value_Quote.h"
#include "gurax/Value_Stream.h"
#include "gurax/Value_String.h"
#include "gurax/Value_StringPtr.h"
#include "gurax/Value_Symbol.h"
#include "gurax/Value_Template.h"
#include "gurax/Value_TimeDelta.h"
#include "gurax/Value_Undefined.h"
#include "gurax/Value_VType.h"
#include "gurax/VType.h"

namespace Gurax {

void Bootup();

}

#endif
