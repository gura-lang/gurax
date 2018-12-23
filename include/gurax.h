//==============================================================================
// gurax.h
//==============================================================================
#ifndef GURAX_H
#define GURAX_H

#include "gurax/Common.h"
#include "gurax/DateTime.h"
#include "gurax/Error.h"
#include "gurax/Expr.h"
#include "gurax/Function.h"
#include "gurax/Help.h"
#include "gurax/Iterator.h"
#include "gurax/MemoryPool.h"
#include "gurax/Object.h"
#include "gurax/Object_function.h"
#include "gurax/Object_nil.h"
#include "gurax/Object_number.h"
#include "gurax/Object_undefined.h"
#include "gurax/Operator.h"
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
