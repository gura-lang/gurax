//==============================================================================
// ImageExtension.h
//==============================================================================
#ifndef GURAX_MODULE_BMP_IMAGEEXTENSION_H
#define GURAX_MODULE_BMP_IMAGEEXTENSION_H
#include <gurax.h>
#include <gurax/Palette.h>

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

//------------------------------------------------------------------------------
// ImageMgrEx
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageMgrEx : public ImageMgr {
public:
	ImageMgrEx() : ImageMgr("bmp") {}
public:
	virtual bool IsResponsible(Stream& stream) const override;
	virtual bool IsResponsibleExtName(const char* extName) const override;
	virtual bool Read(Stream& stream, Image& image) const override;
	virtual bool Write(Stream& stream, const Image& image) const override;
public:
	int CalcDIBBitCount() const;
	size_t CalcDIBImageSize(int biBitCount, bool maskFlag) const;
	Palette* ReadDIBPalette(Stream& stream, int biBitCount);
	bool WriteDIBPalette(Stream& stream, int biBitCount);
};

Gurax_EndModuleScope(bmp)

#endif
