//==============================================================================
// module-zip.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_H
#define GURAX_MODULE_ZIP_H
#include <gurax.h>
#include "Util.h"
#include "VType_Reader.h"
#include "VType_Stat.h"
#include "VType_Writer.h"

Gurax_BeginModuleHeader(zip)

#if 0
Gurax_DeclareSymbol(filename);
Gurax_DeclareSymbol(comment);
Gurax_DeclareSymbol(compression_method);
Gurax_DeclareSymbol(mtime);
Gurax_DeclareSymbol(crc32);
Gurax_DeclareSymbol(size);
Gurax_DeclareSymbol(compressed_size);
Gurax_DeclareSymbol(attributes);

Gurax_DeclareSymbol(store);
Gurax_DeclareSymbol(shrink);
Gurax_DeclareSymbol(factor1);
Gurax_DeclareSymbol(factor2);
Gurax_DeclareSymbol(factor3);
Gurax_DeclareSymbol(factor4);
Gurax_DeclareSymbol(implode);
Gurax_DeclareSymbol(deflate);
Gurax_DeclareSymbol(deflate64);
Gurax_DeclareSymbol(pkware);
Gurax_DeclareSymbol(bzip2);
Gurax_DeclareSymbol(lzma);
Gurax_DeclareSymbol(tersa);
Gurax_DeclareSymbol(lz77);
Gurax_DeclareSymbol(wavpack);
Gurax_DeclareSymbol(ppmd);
#endif

Gurax_EndModuleHeader(zip)

#endif
