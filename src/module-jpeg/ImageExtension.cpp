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
	jpeg_decompress_struct cinfo;
	ErrorMgr errMgr;
	if (!errMgr.Initialize(cinfo)) return false;
	::jpeg_create_decompress(&cinfo);
	SourceMgr::Setup(&cinfo, stream);
	::jpeg_read_header(&cinfo, TRUE);
	if (!image.Allocate(cinfo.image_width, cinfo.image_height)) {
		::jpeg_destroy_decompress(&cinfo);
		return false;
	}
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
	return false;
}

bool ImageMgrEx::DoDecompress(Image& image, jpeg_decompress_struct& cinfo)
{
#if 0
	::jpeg_start_decompress(&cinfo);
	bool grayScaleFlag = (cinfo.output_components != 3);
	JSAMPARRAY scanlines = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo,
					JPOOL_IMAGE, cinfo.output_width * cinfo.output_components, 1);
	while (cinfo.output_scanline < cinfo.output_height) {
		::jpeg_read_scanlines(&cinfo, scanlines, 1);
		if (sig.IsSignalled()) {
			::jpeg_finish_decompress(&cinfo);
			::jpeg_destroy_decompress(&cinfo);
			return false;
		}
		const UChar *srcp = scanlines[0];
		UChar *dstp = pImage->GetPointer(0, cinfo.output_scanline - 1);
		if (grayScaleFlag) {
			for (UInt i = 0; i < cinfo.output_width; i++) {
				*(dstp + Image::OffsetR) = *srcp;
				*(dstp + Image::OffsetG) = *srcp;
				*(dstp + Image::OffsetB) = *srcp;
				srcp++;
				dstp += pImage->GetBytesPerPixel();
			}
		} else {
			for (UInt i = 0; i < cinfo.output_width; i++) {
				*(dstp + Image::OffsetR) = *srcp++;
				*(dstp + Image::OffsetG) = *srcp++;
				*(dstp + Image::OffsetB) = *srcp++;
				dstp += pImage->GetBytesPerPixel();
			}
		}
	}
	::jpeg_finish_decompress(&cinfo);
	::jpeg_destroy_decompress(&cinfo);
#endif
	return true;
}

bool ImageMgrEx::DoDecompressWithBilinearScaling(Image& iImage, jpeg_decompress_struct& cinfo)
{
#if 0
	::jpeg_start_decompress(&cinfo);
	bool grayScaleFlag = (cinfo.output_components != 3);
	size_t widthDst = pImage->GetWidth();
	size_t heightDst = pImage->GetHeight();
	JSAMPARRAY scanlines = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo,
					JPOOL_IMAGE, cinfo.output_width * cinfo.output_components, 1);
	UChar *pLineDst = pImage->GetPointer(0);
	size_t bytesPerPixel = pImage->GetBytesPerPixel();
	size_t bytesPerLineDst = pImage->GetBytesPerLine();
	size_t accumsSize = widthDst * sizeof(Image::Accum);
	AutoPtr<Memory> pMemory(new MemoryHeap(accumsSize));
	Image::Accum *accums = reinterpret_cast<Image::Accum *>(pMemory->GetPointer());
	::memset(accums, 0x00, accumsSize);
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
			const UChar *pPixelSrc = scanlines[0];
			Image::Accum *pAccum = accums;
			size_t xDst = 0;
			size_t numerX = 0;
			if (grayScaleFlag) {
				for (UInt xSrc = 0; xSrc < cinfo.output_width; xSrc++) {
					pAccum->AddRGB(pPixelSrc[0], pPixelSrc[0], pPixelSrc[0]);
					pPixelSrc += 1;
					numerX += widthDst;
					for ( ; numerX >= cinfo.output_width && xDst < widthDst;
						  numerX -= cinfo.output_width, xDst++) {
						pAccum++;
					}
				}
			} else {
				for (UInt xSrc = 0; xSrc < cinfo.output_width; xSrc++) {
					pAccum->AddRGB(pPixelSrc[0], pPixelSrc[1], pPixelSrc[2]);
					pPixelSrc += 3;
					numerX += widthDst;
					for ( ; numerX >= cinfo.output_width && xDst < widthDst;
						  numerX -= cinfo.output_width, xDst++) {
						pAccum++;
					}
				}
			}
		}
		numerY += heightDst;
		if (numerY >= cinfo.output_height) {
			if (accums[0].cnt == 0) accums[0].cnt = 0; // this must not happen
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
				UChar *pPixelDst = pLineDst;
				for (size_t xDst = 0; xDst < widthDst;
					 xDst++, pAccum++, pPixelDst += bytesPerPixel) {
					pAccum->StoreRGB(pPixelDst);
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
	size_t widthDst = pImage->GetWidth();
	size_t heightDst = pImage->GetHeight();
	JSAMPARRAY scanlines = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo,
					JPOOL_IMAGE, cinfo.output_width * cinfo.output_components, 1);
	UChar *pLineDst = pImage->GetPointer(0);
	size_t bytesPerPixelDst = pImage->GetBytesPerPixel();
	size_t bytesPerLineDst = pImage->GetBytesPerLine();
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
		const UChar *pLineSrc = scanlines[0];
		if (grayScaleFlag) {
			UChar *pPixelDst = pLineDst;
			for (UInt xDst = 0; xDst < widthDst; xDst++) {
				const UChar *pPixelSrc = pLineSrc + offsetDst[xDst];
				*(pPixelDst + Image::OffsetR) = *pPixelSrc;
				*(pPixelDst + Image::OffsetG) = *pPixelSrc;
				*(pPixelDst + Image::OffsetB) = *pPixelSrc;
				pPixelDst += bytesPerPixelDst;
			}
		} else {
			UChar *pPixelDst = pLineDst;
			for (UInt xDst = 0; xDst < widthDst; xDst++) {
				const UChar *pPixelSrc = pLineSrc + offsetDst[xDst];
				*(pPixelDst + Image::OffsetR) = *(pPixelSrc + 0);
				*(pPixelDst + Image::OffsetG) = *(pPixelSrc + 1);
				*(pPixelDst + Image::OffsetB) = *(pPixelSrc + 2);
				pPixelDst += bytesPerPixelDst;
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
