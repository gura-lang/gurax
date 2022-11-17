//==============================================================================
// ImageExtension.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(png)

bool ImageMgrEx::IsResponsible(Stream& stream) const
{
	png_byte sig[8];
	return stream.Read(sig, sizeof(sig)) == sizeof(sig) && ::png_sig_cmp(sig, 0, sizeof(sig)) == 0;
}

bool ImageMgrEx::IsResponsibleExtName(const char* extName) const
{
	return ::strcasecmp(extName, ".png") == 0;
}

bool ImageMgrEx::Read(Stream& stream, Image& image) const
{
	return ReadStream(stream, image);
}

bool ImageMgrEx::Write(Stream& stream, const Image& image) const
{
	return WriteStream(stream, image);
}

bool ImageMgrEx::ReadStream(Stream& stream, Image& image) const
{
	Handler handler(stream);
	png_structp png_ptr = ::png_create_read_struct(
			PNG_LIBPNG_VER_STRING, nullptr, Handler::Error, Handler::Warning);
	png_infop info_ptr = ::png_create_info_struct(png_ptr);
	png_infop end_info = ::png_create_info_struct(png_ptr);
	if (::setjmp(png_jmpbuf(png_ptr))) {
		::png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return false;
	}
	::png_set_read_fn(png_ptr, &handler, Handler::ReadData);
	::png_read_info(png_ptr, info_ptr);
	png_uint_32 width, height;
	int bit_depth, color_type, interlace_type;
	::png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth,
							&color_type, &interlace_type, nullptr, nullptr);
	::png_set_strip_16(png_ptr); // 16-bit RGB is converted into 8-bit.
	if (color_type == PNG_COLOR_TYPE_GRAY) {
		::png_set_expand(png_ptr);
		::png_set_add_alpha(png_ptr, 0x00, PNG_FILLER_AFTER);
		if (image.IsFormat(Image::Format::RGBA)) {
			::png_set_add_alpha(png_ptr, 0x00, PNG_FILLER_AFTER);
		}
	} else if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
		::png_set_gray_to_rgb(png_ptr);
		if (image.IsFormat(Image::Format::RGB)) {
			::png_set_strip_alpha(png_ptr);
		}
	} else if (color_type == PNG_COLOR_TYPE_PALETTE) {
		::png_set_palette_to_rgb(png_ptr);
		::png_set_bgr(png_ptr);
		if (image.IsFormat(Image::Format::RGB)) {
			::png_set_strip_alpha(png_ptr);
		} else if (::png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
			::png_set_tRNS_to_alpha(png_ptr);
		} else {
			::png_set_add_alpha(png_ptr, 0xff, PNG_FILLER_AFTER);
		}
	} else if (color_type == PNG_COLOR_TYPE_RGB) {
		::png_set_bgr(png_ptr);
		if (image.IsFormat(Image::Format::RGBA)) {
			::png_set_add_alpha(png_ptr, 0xff, PNG_FILLER_AFTER);
		}
	} else if (color_type == PNG_COLOR_TYPE_RGB_ALPHA) {
		::png_set_bgr(png_ptr);
		if (image.IsFormat(Image::Format::RGB)) {
			::png_set_strip_alpha(png_ptr);
		}
	}
	if (::png_get_valid(png_ptr, info_ptr, PNG_INFO_PLTE)) {
		png_color* palette;
		int num_palette;
		::png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
		if (num_palette > 0) {
			RefPtr<Palette> pPaletteDst(new Palette(num_palette));
			for (size_t idx = 0; idx < num_palette; idx++, palette++) {
				pPaletteDst->SetRGB(idx, palette->red, palette->green, palette->blue);
			}
			image.SetPalette(pPaletteDst.release());
		}
	}
	::png_set_packing(png_ptr);
	::png_read_update_info(png_ptr, info_ptr);
	::png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth,
							&color_type, &interlace_type, nullptr, nullptr);
	if (!image.Allocate(width, height)) {
		::png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return false;
	}
	std::unique_ptr<png_bytep[]> row_pointers(new png_bytep [height]);
	for (size_t y = 0; y < static_cast<size_t>(height); y++) {
		row_pointers[y] = reinterpret_cast<png_bytep>(image.GetPointerC(0, y));
	}
	::png_read_image(png_ptr, row_pointers.get());
	::png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	return !Error::IsIssued();
}

bool ImageMgrEx::WriteStream(Stream& stream, const Image& image) const
{
	Handler handler(stream);
	png_structp png_ptr = ::png_create_write_struct(
			PNG_LIBPNG_VER_STRING, &handler, Handler::Error, Handler::Warning);
	png_infop info_ptr = ::png_create_info_struct(png_ptr);
	if (::setjmp(png_jmpbuf(png_ptr))) {
		::png_destroy_write_struct(&png_ptr, &info_ptr);
		return false;
	}
	::png_set_write_fn(png_ptr, &handler, Handler::WriteData, Handler::FlushData);
	png_uint_32 width = static_cast<png_uint_32>(image.GetWidth());
	png_uint_32 height = static_cast<png_uint_32>(image.GetHeight());
	int bit_depth = 8;
	int color_type = PNG_COLOR_TYPE_RGB;
#if 0
	if (image.HasPalette()) {
		const Palette* pPaletteSrc = image.GetPalette();
		int num_palette = static_cast<int>(pPaletteSrc->GetSize());
		std::unique_ptr<png_color[]> palette(new png_color [num_palette]);
		for (int idx = 0; idx < num_palette; idx++) {
			const Color& color = pPaletteSrc->GetColor(idx);
			palette[idx].red = color.GetR();
			palette[idx].green = color.GetG();
			palette[idx].blue = color.GetB();
		}
		::png_set_PLTE(png_ptr, info_ptr, palette.get(), num_palette);
		::png_set_palette_to_rgb(png_ptr);
		color_type = PNG_COLOR_TYPE_PALETTE;
		if (image.IsFormat(Image::Format::RGBA)) {
			//*********************
		}
	}
#endif
	if (image.IsFormat(Image::Format::RGB)) {
		color_type = PNG_COLOR_TYPE_RGB;
	} else { // if (image.IsFormat(Image::Format::RGBA))
		color_type = PNG_COLOR_TYPE_RGB_ALPHA;
	}
	int interlace_type = PNG_INTERLACE_NONE;
	int compression_type = PNG_COMPRESSION_TYPE_BASE;
	int filter_method = PNG_FILTER_TYPE_BASE;
	::png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth,
				color_type, interlace_type, compression_type, filter_method);
	::png_write_info(png_ptr, info_ptr);
	::png_set_packing(png_ptr);		// pack pixels into bytes
	::png_set_bgr(png_ptr);			// flip BGR pixel to RGB 
	const UInt8* pRow = image.GetPointerC();
	for (size_t y = 0; y < static_cast<size_t>(height); y++, pRow += image.GetBytesPerLine()) {
		::png_write_row(png_ptr, pRow);
	}
	::png_write_end(png_ptr, info_ptr);
	::png_destroy_write_struct(&png_ptr, &info_ptr);
	return true;
}

//-----------------------------------------------------------------------------
// Handler
//-----------------------------------------------------------------------------
void Handler::Error(png_structp png_ptr, png_const_charp error_msg)
{
	Error::Issue(ErrorType::FormatError, "%s", reinterpret_cast<const char *>(error_msg));
	::longjmp(png_jmpbuf(png_ptr), 1);
}

void Handler::Warning(png_structp png_ptr, png_const_charp warning_msg)
{
	// just ignore it
}

void Handler::ReadData(png_structp png_ptr, png_bytep data, png_size_t length)
{
	Handler& hdr = *reinterpret_cast<Handler*>(::png_get_io_ptr(png_ptr));
	Stream& stream = hdr.GetStream();
	if (stream.Read(data, length) < length) {
		::png_error(png_ptr, "read data error");
	}
}

void Handler::WriteData(png_structp png_ptr, png_bytep data, png_size_t length)
{
	Handler& hdr = *reinterpret_cast<Handler*>(::png_get_io_ptr(png_ptr));
	Stream& stream = hdr.GetStream();
	if (!stream.Write(data, length)) {
		::png_error(png_ptr, "write data error");
	}
}

void Handler::FlushData(png_structp png_ptr)
{
	Handler& hdr = *reinterpret_cast<Handler*>(::png_get_io_ptr(png_ptr));
	Stream& stream = hdr.GetStream();
	if (!stream.Flush()) {
		::png_error(png_ptr, "flush data error");
	}
}

Gurax_EndModuleScope(png)