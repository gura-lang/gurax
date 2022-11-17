//==============================================================================
// ImageExtension.h
//==============================================================================
#ifndef GURAX_MODULE_GIF_IMAGEEXTENSION_H
#define GURAX_MODULE_GIF_IMAGEEXTENSION_H
#include <gurax.h>

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// ImageMgrEx
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageMgrEx : public ImageMgr {
public:
	ImageMgrEx() : ImageMgr("gif", "GIF (Graphics Interchange Format)") {}
public:
	virtual bool IsResponsible(Stream& stream) const override;
	virtual bool IsResponsibleExtName(const char* extName) const override;
	virtual bool Read(Stream& stream, Image& image) const override;
	virtual bool Write(Stream& stream, const Image& image) const override;
public:
	static bool ReadStream(Stream& stream, Image& image);
	static bool WriteStream(Stream& stream, const Image& image);
};

Gurax_EndModuleScope(gif)

#endif
