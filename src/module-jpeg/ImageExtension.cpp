//==============================================================================
// ImageExtension.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// ImageMgrEx
//------------------------------------------------------------------------------
bool ImageMgrEx::IsResponsible(Stream& stream) const
{
	char buff[2];
	// byte sequence "\xff\xd8" is SOI (Start of Image) marker in JPEG
	return stream.Read(buff, 2) == 2 && ::memcmp(buff, "\xff\xd8", 2) == 0;
}

bool ImageMgrEx::IsResponsibleExtName(const char* extName) const
{
	return ::strcasecmp(extName, ".jpg") == 0 ||
		::strcasecmp(extName, ".jpeg") == 0 || ::strcasecmp(extName, ".jpe") == 0;
}

bool ImageMgrEx::Read(Stream& stream, Image& image) const
{
	return ReadStream(stream, image, false);
}

bool ImageMgrEx::Write(Stream& stream, const Image& image) const
{
	return WriteStream(stream, image, 75);
}

bool ImageMgrEx::ReadStream(Stream& stream, Image& image, bool fastFlag)
{
	ErrorMgr errMgr;
	jpeg_decompress_struct cinfo;
	cinfo.err = ::jpeg_std_error(&errMgr.pub);
	errMgr.pub.error_exit = errMgr.error_exit;	// override error handler
	if (::setjmp(errMgr.jmpenv) != 0) {
		::jpeg_destroy_decompress(&cinfo);
		return false;
	}
	::jpeg_create_decompress(&cinfo);
	SourceMgr::Setup(&cinfo, stream);
	::jpeg_read_header(&cinfo, TRUE);
	if (!image.Allocate(cinfo.image_width, cinfo.image_height)) {
		::jpeg_destroy_decompress(&cinfo);
		return false;
	}
	image.Fill(0xff);
	if (fastFlag) {
		// Setting equivalent to -fast option of djpeg. See line.251 in djpeg.c.
		cinfo.two_pass_quantize = FALSE;
		cinfo.dither_mode = JDITHER_ORDERED;
		if (!cinfo.quantize_colors) cinfo.desired_number_of_colors = 216;
		cinfo.dct_method = JDCT_FASTEST;
		cinfo.do_fancy_upsampling = FALSE;
		::jpeg_calc_output_dimensions(&cinfo);	// update parameters in the structure
	}
	return DoDecompress(image, cinfo);
}

bool ImageMgrEx::WriteStream(Stream& stream, const Image& image, int quality)
{
	ErrorMgr errMgr;
	jpeg_compress_struct cinfo;
	cinfo.err = ::jpeg_std_error(&errMgr.pub);
	errMgr.pub.error_exit = errMgr.error_exit;	// override error handler
	if (::setjmp(errMgr.jmpenv) != 0) {
		::jpeg_destroy_compress(&cinfo);
		return false;
	}
	::jpeg_create_compress(&cinfo);
	DestinationMgr::Setup(&cinfo, stream);
	cinfo.image_width		= static_cast<JDIMENSION>(image.GetWidth());
	cinfo.image_height		= static_cast<JDIMENSION>(image.GetHeight());
	cinfo.input_components	= 3;
	cinfo.in_color_space	= JCS_RGB;
	::jpeg_set_defaults(&cinfo);
	::jpeg_set_quality(&cinfo, quality, TRUE);
	::jpeg_start_compress(&cinfo, TRUE);
	JSAMPARRAY scanlines = (*cinfo.mem->alloc_sarray)(
		reinterpret_cast<j_common_ptr>(&cinfo), JPOOL_IMAGE,
		cinfo.image_width * cinfo.input_components, 1);
	while (cinfo.next_scanline < cinfo.image_height) {
		const UInt8* pSrc = image.GetPointerC(0, cinfo.next_scanline);
		UInt8* pDst = scanlines[0];
		for (UInt i = 0; i < cinfo.image_width; i++) {
			*(pDst + 0) = Image::Pixel::GetR(pSrc);
			*(pDst + 1) = Image::Pixel::GetG(pSrc);
			*(pDst + 2) = Image::Pixel::GetB(pSrc);
			pSrc += image.GetBytesPerPixel();
			pDst += 3;
		}
		::jpeg_write_scanlines(&cinfo, scanlines, 1);
	}
	::jpeg_finish_compress(&cinfo);
	::jpeg_destroy_compress(&cinfo);
	return true;
}

bool ImageMgrEx::DoDecompress(Image& image, jpeg_decompress_struct& cinfo)
{
	::jpeg_start_decompress(&cinfo);
	bool grayScaleFlag = (cinfo.output_components != 3);
	JSAMPARRAY scanlines = (*cinfo.mem->alloc_sarray)(
		reinterpret_cast<j_common_ptr>(&cinfo), JPOOL_IMAGE,
		cinfo.output_width * cinfo.output_components, 1);
	while (cinfo.output_scanline < cinfo.output_height) {
		::jpeg_read_scanlines(&cinfo, scanlines, 1);
		if (Error::IsIssued()) {
			::jpeg_finish_decompress(&cinfo);
			::jpeg_destroy_decompress(&cinfo);
			return false;
		}
		const UInt8* pSrc = scanlines[0];
		UInt8* pDst = image.GetPointerC(0, cinfo.output_scanline - 1);
		if (grayScaleFlag) {
			for (UInt i = 0; i < cinfo.output_width; i++) {
				Image::Pixel::SetRGB(pDst, *pSrc, *pSrc, *pSrc);
				pSrc++;
				pDst += image.GetBytesPerPixel();
			}
		} else {
			for (UInt i = 0; i < cinfo.output_width; i++) {
				Image::Pixel::SetRGB(pDst, *pSrc, *(pSrc + 1), *(pSrc + 2));
				pSrc += 3;
				pDst += image.GetBytesPerPixel();
			}
		}
	}
	::jpeg_finish_decompress(&cinfo);
	::jpeg_destroy_decompress(&cinfo);
	return true;
}

bool ImageMgrEx::DoDecompressWithBilinearScaling(Image& image, jpeg_decompress_struct& cinfo)
{
#if 0
	::jpeg_start_decompress(&cinfo);
	bool grayScaleFlag = (cinfo.output_components != 3);
	size_t widthDst = image.GetWidth();
	size_t heightDst = image.GetHeight();
	JSAMPARRAY scanlines = (*cinfo.mem->alloc_sarray)(
		reinterpret_cast<j_common_ptr>(&cinfo), JPOOL_IMAGE,
		cinfo.output_width * cinfo.output_components, 1);
	UInt8* pLineDst = image.GetPointer();
	size_t bytesPerPixel = image.GetBytesPerPixel();
	size_t bytesPerLineDst = image.GetBytesPerLine();
	//size_t accumsSize = widthDst * sizeof(Image::Accum);
	//AutoPtr<Memory> pMemory(new MemoryHeap(accumsSize));
	//Image::Accum *accums = reinterpret_cast<Image::Accum *>(pMemory->GetPointer());
	//::memset(accums, 0x00, accumsSize);
	Image::Accumulator accumulator(widthDst);
	size_t numerY = 0;
	size_t yDst = 0;
	for (;;) {
		if (cinfo.output_scanline < cinfo.output_height) {
			::jpeg_read_scanlines(&cinfo, scanlines, 1);
			if (sig.IsSignalled()) {
				::jpeg_finish_decompress(&cinfo);
				::jpeg_destroy_decompress(&cinfo);
				return false;
			}
			const UInt8 *pSrc = scanlines[0];
			//Image::Accum *pAccum = accums;
			size_t xDst = 0;
			size_t numerX = 0;
			if (grayScaleFlag) {
				for (UInt xSrc = 0; xSrc < cinfo.output_width; xSrc++) {
					//pAccum->AddRGB(pSrc[0], pSrc[0], pSrc[0]);
					accumulator.StoreRGB(idx, pSrc[0], pSrc[0], pSrc[0]);
					pSrc += 1;
					numerX += widthDst;
					for ( ; numerX >= cinfo.output_width && xDst < widthDst;
						  numerX -= cinfo.output_width, xDst++) ;
				}
			} else {
				for (UInt xSrc = 0; xSrc < cinfo.output_width; xSrc++) {
					//pAccum->AddRGB(pSrc[0], pSrc[1], pSrc[2]);
					accumulator.StoreRGB(idx, pSrc);
					pSrc += 3;
					numerX += widthDst;
					for ( ; numerX >= cinfo.output_width && xDst < widthDst;
						  numerX -= cinfo.output_width, xDst++) ;
				}
			}
		}
		numerY += heightDst;
		if (numerY >= cinfo.output_height) {
			if (accums[0].cnt == 0) accums[0].cnt = 0; // illegal case
			Image::Accum *pAccum = accums;
			Image::Accum *pAccumPrev = accums;
			for (size_t xDst = 0; xDst < widthDst; xDst++, pAccum++) {
				size_t cnt = pAccum->cnt;
				if (cnt == 0) {
					*pAccum = *pAccumPrev;
				} else if (cnt == 1) {
					pAccumPrev = pAccum;
				} else if (cnt == 2) {
					pAccum->r >>= 1;
					pAccum->g >>= 1;
					pAccum->b >>= 1;
					pAccumPrev = pAccum;
				} else if (cnt == 4) {
					pAccum->r >>= 2;
					pAccum->g >>= 2;
					pAccum->b >>= 2;
					pAccumPrev = pAccum;
				} else {
					pAccum->r /= cnt;
					pAccum->g /= cnt;
					pAccum->b /= cnt;
					pAccumPrev = pAccum;
				}
			}
			for ( ; numerY >= cinfo.output_height && yDst < heightDst;
				  numerY -= cinfo.output_height, yDst++) {
				Image::Accum *pAccum = accums;
				UInt8 *pDst = pLineDst;
				for (size_t xDst = 0; xDst < widthDst;
					 xDst++, pAccum++, pDst += bytesPerPixel) {
					pAccum->StoreRGB(pDst);
				}
				pLineDst += bytesPerLineDst;
			}
			::memset(accums, 0x00, accumsSize);
		}
		if (cinfo.output_scanline == cinfo.output_height) break;
	}
	::jpeg_finish_decompress(&cinfo);
	::jpeg_destroy_decompress(&cinfo);
#endif
	return true;
}

bool ImageMgrEx::DoDecompressWithNearestNeighborScaling(Image& image, jpeg_decompress_struct& cinfo)
{
#if 0
	::jpeg_start_decompress(&cinfo);
	bool grayScaleFlag = (cinfo.output_components != 3);
	size_t widthDst = image.GetWidth();
	size_t heightDst = image.GetHeight();
	JSAMPARRAY scanlines = (*cinfo.mem->alloc_sarray)(
		reinterpret_cast<j_common_ptr>(&cinfo), JPOOL_IMAGE,
		cinfo.output_width * cinfo.output_components, 1);
	UInt8 *pLineDst = image.GetPointer(0);
	size_t bytesPerPixelDst = image.GetBytesPerPixel();
	size_t bytesPerLineDst = image.GetBytesPerLine();
	size_t yDst = 0;
	size_t ySrc = 0, ySrcNext = 0;
	AutoPtr<Memory> pMemory(new MemoryHeap(sizeof(UInt) * widthDst));
	UInt *offsetDst = reinterpret_cast<UInt *>(pMemory->GetPointer());
	if (grayScaleFlag) {
		for (UInt xDst = 0; xDst < widthDst; xDst++) {
			offsetDst[xDst] = xDst * cinfo.output_width / widthDst;
		}
	} else {
		for (UInt xDst = 0; xDst < widthDst; xDst++) {
			offsetDst[xDst] = xDst * cinfo.output_width / widthDst * 3;
		}
	}
	while (cinfo.output_scanline < cinfo.output_height) {
		::jpeg_read_scanlines(&cinfo, scanlines, 1);
		if (sig.IsSignalled()) {
			::jpeg_finish_decompress(&cinfo);
			::jpeg_destroy_decompress(&cinfo);
			return false;
		}
		if (ySrc < ySrcNext) {
			ySrc++;
			continue;
		}
		ySrc++;
		const UInt8 *pLineSrc = scanlines[0];
		if (grayScaleFlag) {
			UInt8 *pDst = pLineDst;
			for (UInt xDst = 0; xDst < widthDst; xDst++) {
				const UInt8 *pSrc = pLineSrc + offsetDst[xDst];
				*(pDst + Image::OffsetR) = *pSrc;
				*(pDst + Image::OffsetG) = *pSrc;
				*(pDst + Image::OffsetB) = *pSrc;
				pDst += bytesPerPixelDst;
			}
		} else {
			UInt8 *pDst = pLineDst;
			for (UInt xDst = 0; xDst < widthDst; xDst++) {
				const UInt8 *pSrc = pLineSrc + offsetDst[xDst];
				*(pDst + Image::OffsetR) = *(pSrc + 0);
				*(pDst + Image::OffsetG) = *(pSrc + 1);
				*(pDst + Image::OffsetB) = *(pSrc + 2);
				pDst += bytesPerPixelDst;
			}
		}
		pLineDst += bytesPerLineDst;
		yDst++;
		ySrcNext = yDst * cinfo.output_height / heightDst;
	}
	::jpeg_finish_decompress(&cinfo);
	::jpeg_destroy_decompress(&cinfo);
#endif
	return true;
}

Gurax_EndModuleScope(jpeg)
