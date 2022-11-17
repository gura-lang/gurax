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
public:
	ImageMgrEx() : ImageMgr("png", "PNG (Portable Network Graphics)") {}
public:
	virtual bool IsResponsible(Stream& stream) const override;
	virtual bool IsResponsibleExtName(const char* extName) const override;
	virtual bool Read(Stream& stream, Image& image) const override;
	virtual bool Write(Stream& stream, const Image& image) const override;
public:
	bool ReadStream(Stream& stream, Image& image) const;
	bool WriteStream(Stream& stream, const Image& image) const;
};

//------------------------------------------------------------------------------
// Handler
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Handler {
private:
	Stream& _stream;
public:
	inline Handler(Stream& stream) : _stream(stream) {}
	inline Stream& GetStream() { return _stream; }
public:
	static void Error(png_structp png_ptr, png_const_charp error_msg);
	static void Warning(png_structp png_ptr, png_const_charp warning_msg);
	static void ReadData(png_structp png_ptr, png_bytep data, png_size_t length);
	static void WriteData(png_structp png_ptr, png_bytep data, png_size_t length);
	static void FlushData(png_structp png_ptr);
};

Gurax_EndModuleScope(png)

#endif
