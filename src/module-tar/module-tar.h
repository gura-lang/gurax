//==============================================================================
// module-tar.h
//==============================================================================
#ifndef GURAX_MODULE_TAR_H
#define GURAX_MODULE_TAR_H
#include <gurax.h>
#include <gurax/helper/BZLibHelper.h>
#include <gurax/helper/ZLibHelper.h>
#include "Reader.h"
#include "Util.h"
#include "PathExtension.h"
#include "TARFormat.h"
#include "Writer.h"
#include "VType_Reader.h"
#include "VType_StatEx.h"
#include "VType_Writer.h"
#include "VType_bzip2.h"
#include "VType_gzip.h"

Gurax_BeginModuleHeader(tar)

extern RefPtr<Codec> g_pCodec;

Gurax_EndModuleHeader(tar)

#endif
