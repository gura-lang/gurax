//==============================================================================
// module-zip.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_H
#define GURAX_MODULE_ZIP_H
#include <gurax.h>
#include "PathMgrEx.h"
#include "Util.h"
#include "VType_Reader.h"
#include "VType_Stat.h"
#include "VType_Writer.h"

Gurax_BeginModuleHeader(zip)

//------------------------------------------------------------------------------
// Symbol
//------------------------------------------------------------------------------
#if 0
Gurax_DeclareSymbol(filename);
Gurax_DeclareSymbol(comment);
Gurax_DeclareSymbol(compression_method);
Gurax_DeclareSymbol(mtime);
Gurax_DeclareSymbol(crc32);
Gurax_DeclareSymbol(size);
Gurax_DeclareSymbol(compressed_size);
Gurax_DeclareSymbol(attributes);
#endif

Gurax_EndModuleHeader(zip)

#endif
