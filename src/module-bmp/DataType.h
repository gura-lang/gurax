//==============================================================================
// DataType.h
//==============================================================================
#ifndef GURAX_MODULE_BMP_DATATYPE_H
#define GURAX_MODULE_BMP_DATATYPE_H
#include <gurax.h>

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// BitmapFileHeader
//------------------------------------------------------------------------------
struct BitmapFileHeader {
	Gurax_PackedUInt16_LE(bfType);
	Gurax_PackedUInt32_LE(bfSize);
	Gurax_PackedUInt16_LE(bfReserved1);
	Gurax_PackedUInt16_LE(bfReserved2);
	Gurax_PackedUInt32_LE(bfOffBits);
	static const size_t bytes = 14;
};

//------------------------------------------------------------------------------
// BitmapInfoHeader
//------------------------------------------------------------------------------
struct BitmapInfoHeader {
	Gurax_PackedUInt32_LE(biSize);
	Gurax_PackedInt32_LE(biWidth);
	Gurax_PackedInt32_LE(biHeight);
	Gurax_PackedUInt16_LE(biPlanes);
	Gurax_PackedUInt16_LE(biBitCount);
	Gurax_PackedUInt32_LE(biCompression);
	Gurax_PackedUInt32_LE(biSizeImage);
	Gurax_PackedInt32_LE(biXPelsPerMeter);
	Gurax_PackedInt32_LE(biYPelsPerMeter);
	Gurax_PackedUInt32_LE(biClrUsed);
	Gurax_PackedUInt32_LE(biClrImportant);
	static const size_t bytes = 40;
};

Gurax_EndModuleScope(bmp)

#endif
