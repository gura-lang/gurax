//==============================================================================
// gurax.h
//==============================================================================
#ifndef GURAX_H
#define GURAX_H

#include "gurax/Attribute.h"
#include "gurax/Binary.h"
#include "gurax/Common.h"
#include "gurax/Context.h"
#include "gurax/DateTime.h"
#include "gurax/Environment.h"
#include "gurax/Error.h"
#include "gurax/Expr.h"
#include "gurax/Formatter.h"
#include "gurax/Frame.h"
#include "gurax/Function.h"
#include "gurax/Help.h"
#include "gurax/Iterator.h"
#include "gurax/MemoryPool.h"
#include "gurax/Object.h"
#include "gurax/Object_attribute.h"
#include "gurax/Object_binary.h"
#include "gurax/Object_bool.h"
#include "gurax/Object_dict.h"
#include "gurax/Object_expr.h"
#include "gurax/Object_function.h"
#include "gurax/Object_iterator.h"
#include "gurax/Object_klass.h"
#include "gurax/Object_list.h"
#include "gurax/Object_module.h"
#include "gurax/Object_nil.h"
#include "gurax/Object_number.h"
#include "gurax/Object_stream.h"
#include "gurax/Object_string.h"
#include "gurax/Object_stringptr.h"
#include "gurax/Object_symbol.h"
#include "gurax/Object_undefined.h"
#include "gurax/Operator.h"
#include "gurax/Operators.h"
#include "gurax/Parser.h"
#include "gurax/Random.h"
#include "gurax/Referable.h"
#include "gurax/Stream.h"
#include "gurax/String.h"
#include "gurax/Symbol.h"
#include "gurax/Symbols.h"
#include "gurax/TimeDelta.h"
#include "gurax/Token.h"
#include "gurax/Tokenizer.h"

namespace Gurax {

void Bootup();

}

#endif
