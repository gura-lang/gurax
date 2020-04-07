//==============================================================================
// ImageExtension.h
//==============================================================================
#ifndef GURAX_MODULE_PNG_IMAGEEXTENSION_H
#define GURAX_MODULE_PNG_IMAGEEXTENSION_H
#include <gurax.h>
#include <png.h>

Gurax_BeginModuleScope(png)

//------------------------------------------------------------------------------
// ImageMgrEx
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageMgrEx : public ImageMgr {
public:
	ImageMgrEx() : ImageMgr("png") {}
public:
	virtual bool IsResponsible(Stream& stream) const override;
	virtual bool IsResponsibleExtName(const char* extName) const override;
	virtual bool Read(Stream& stream, Image& image) const override;
	virtual bool Write(Stream& stream, const Image& image) const override;
};

Gurax_EndModuleScope(png)

#endif
