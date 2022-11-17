//==============================================================================
// ImageExtension.h
//==============================================================================
#ifndef GURAX_MODULE_BMP_IMAGEEXTENSION_H
#define GURAX_MODULE_BMP_IMAGEEXTENSION_H
#include <gurax.h>
#include "DataType.h"

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// ImageMgrEx
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageMgrEx : public ImageMgr {
public:
	ImageMgrEx() : ImageMgr("bmp", "BMP (Microsoft Windows Bitmap Image)") {}
public:
	virtual bool IsResponsible(Stream& stream) const override;
	virtual bool IsResponsibleExtName(const char* extName) const override;
	virtual bool Read(Stream& stream, Image& image) const override;
	virtual bool Write(Stream& stream, const Image& image) const override;
public:
	static int CalcDIBBitCount(const Image& image);
	static UInt32 CalcDIBPaletteSize(int biBitCount) { return (biBitCount <= 8)? (1 << biBitCount) * 4 : 0; }
	static UInt32 CalcDIBImageSize(size_t width, size_t height, int biBitCount, bool maskFlag);
	static Palette* ReadDIBPalette(Stream& stream, int biBitCount);
	static bool WriteDIBPalette(Stream& stream, const Palette& palette, int biBitCount);
	static bool ReadDIB(Stream& stream, Image& image, int biWidth, int biHeight, int biBitCount, bool maskFlag);
	static bool WriteDIB(Stream& stream, const Image& image, const Palette* pPalette, int biBitCount, bool maskFlag);
};

Gurax_EndModuleScope(bmp)

#endif
