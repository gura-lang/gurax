//==============================================================================
// ImageExtension.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_IMAGEEXTENSION_H
#define GURAX_MODULE_JPEG_IMAGEEXTENSION_H
#include <gurax.h>
#include <gurax/Palette.h>

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// ImageMgrEx
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageMgrEx : public ImageMgr {
public:
	ImageMgrEx() : ImageMgr("jpeg") {}
public:
	virtual bool IsResponsible(Stream& stream) const override;
	virtual bool IsResponsibleExtName(const char* extName) const override;
	virtual bool Read(Stream& stream, Image& image) const override;
	virtual bool Write(Stream& stream, const Image& image) const override;
};

Gurax_EndModuleScope(jpeg)

#endif
