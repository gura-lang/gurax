//==============================================================================
// gurax.h
//==============================================================================
#ifndef GURAX_H
#define GURAX_H

#include "gurax/ArgFeeder.h"
#include "gurax/ArgPicker.h"
#include "gurax/ArgSlot.h"
#include "gurax/Argument.h"
#include "gurax/Attribute.h"
#include "gurax/Basement.h"
#include "gurax/Binary.h"
#include "gurax/Codec.h"
#include "gurax/CommandLine.h"
#include "gurax/Common.h"
#include "gurax/Composer.h"
#include "gurax/DateTime.h"
#include "gurax/DeclArg.h"
#include "gurax/DeclBlock.h"
#include "gurax/DeclCallable.h"
#include "gurax/DottedSymbol.h"
#include "gurax/Error.h"
#include "gurax/Expr.h"
#include "gurax/Formatter.h"
#include "gurax/Frame.h"
#include "gurax/Function.h"
#include "gurax/FunctionCustom.h"
#include "gurax/Functions.h"
#include "gurax/Help.h"
#include "gurax/Index.h"
#include "gurax/Iterator.h"
#include "gurax/Iterators.h"
#include "gurax/Math.h"
#include "gurax/Memory.h"
#include "gurax/MemoryPool.h"
#include "gurax/OAL.h"
#include "gurax/Operator.h"
#include "gurax/Operators.h"
#include "gurax/Parser.h"
#include "gurax/PathName.h"
#include "gurax/Processor.h"
#include "gurax/PropHandler.h"
#include "gurax/PropHandlerCustom.h"
#include "gurax/PUnit.h"
#include "gurax/Random.h"
#include "gurax/Referable.h"
#include "gurax/Statements.h"
#include "gurax/Stream.h"
#include "gurax/Streams.h"
#include "gurax/String.h"
#include "gurax/StringPicker.h"
#include "gurax/SuffixMgr.h"
#include "gurax/Symbol.h"
#include "gurax/Symbols.h"
#include "gurax/Template.h"
#include "gurax/TimeDelta.h"
#include "gurax/Token.h"
#include "gurax/Tokenizer.h"
#include "gurax/Value.h"
#include "gurax/Version.h"
#include "gurax/VType.h"
#include "gurax/VTypeCustom.h"
#include "gurax/VType_Any.h"
#include "gurax/VType_ArgMapper.h"
#include "gurax/VType_ArgMapper_Multiple.h"
#include "gurax/VType_ArgSlot.h"
#include "gurax/VType_Argument.h"
#include "gurax/VType_Attribute.h"
#include "gurax/VType_Binary.h"
#include "gurax/VType_Bool.h"
#include "gurax/VType_DateTime.h"
#include "gurax/VType_Dict.h"
#include "gurax/VType_Error.h"
#include "gurax/VType_ErrorType.h"
#include "gurax/VType_Expr.h"
#include "gurax/VType_Frame.h"
#include "gurax/VType_Function.h"
#include "gurax/VType_Index.h"
#include "gurax/VType_Iterator.h"
#include "gurax/VType_List.h"
#include "gurax/VType_Member.h"
#include "gurax/VType_Module.h"
#include "gurax/VType_Nil.h"
#include "gurax/VType_Number.h"
#include "gurax/VType_Object.h"
#include "gurax/VType_PUnit.h"
#include "gurax/VType_Quote.h"
#include "gurax/VType_Random.h"
#include "gurax/VType_Stream.h"
#include "gurax/VType_String.h"
#include "gurax/VType_StringPtr.h"
#include "gurax/VType_Symbol.h"
#include "gurax/VType_Template.h"
#include "gurax/VType_TimeDelta.h"
#include "gurax/VType_Undefined.h"
#include "gurax/VType_VType.h"
#include "../src/module-codecs/module-codecs.h"
#include "../src/module-fs/module-fs.h"
#include "../src/module-math/module-math.h"
#include "../src/module-os/module-os.h"
#include "../src/module-path/module-path.h"
#include "../src/module-re/module-re.h"
#include "../src/module-sys/module-sys.h"

namespace Gurax {

void Initialize();

}

#endif
