//==============================================================================
// ImageExtension.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_IMAGEEXTENSION_H
#define GURAX_MODULE_JPEG_IMAGEEXTENSION_H
#include <gurax.h>

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// ImageMgrEx
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageMgrEx : public ImageMgr {
public:
	ImageMgrEx() : ImageMgr("jpeg", "JPEG (Joint Photographic Experts Group)") {}
public:
	virtual bool IsResponsible(Stream& stream) const override;
	virtual bool IsResponsibleExtName(const char* extName) const override;
	virtual bool Read(Stream& stream, Image& image) const override;
	virtual bool Write(Stream& stream, const Image& image) const override;
public:
	static bool ReadStream(Stream& stream, Image& image, bool fastFlag);
	static bool WriteStream(Stream& stream, const Image& image, int quality);
protected:
	static bool DoDecompress(Image& image, jpeg_decompress_struct& cinfo);
	static bool DoDecompressWithBilinearScaling(Image& iImage, jpeg_decompress_struct& cinfo);
	static bool DoDecompressWithNearestNeighborScaling(Image& image, jpeg_decompress_struct& cinfo);
};

Gurax_EndModuleScope(jpeg)

#endif
