//==============================================================================
// module-jpeg.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_H
#define GURAX_MODULE_JPEG_H
#include <gurax.h>
#define HAVE_BOOLEAN
using boolean = bool;
extern "C" {
#include <jpeglib.h>
#include <jerror.h>
#include <setjmp.h>
}
#include "Util.h"
#include "VType_Exif.h"
#include "VType_IFD.h"
#include "VType_Tag.h"

Gurax_BeginModuleHeader(jpeg)
Gurax_EndModuleHeader(jpeg)

#endif
