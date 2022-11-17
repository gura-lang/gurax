//==============================================================================
// module-zip.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_H
#define GURAX_MODULE_ZIP_H
#include <gurax.h>
#include "PathExtension.h"
#include "Util.h"
#include "VType_Reader.h"
#include "VType_Writer.h"
#include "VType_StatEx.h"
#include "VType_bzip2.h"
#include "VType_gzip.h"

Gurax_BeginModuleHeader(zip)

extern RefPtr<Codec> g_pCodec;

Gurax_EndModuleHeader(zip)

#endif
