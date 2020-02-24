//==============================================================================
// ImageExtension.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// ImageMgrEx
//------------------------------------------------------------------------------
bool ImageMgrEx::IsResponsible(Stream& stream) const
{
	return false;
}

bool ImageMgrEx::IsResponsibleExtName(const char* extName) const
{
	return ::strcasecmp(extName, ".bmp") == 0;
}

bool ImageMgrEx::Read(Stream& stream, Image& image) const
{
	BitmapFileHeader bfh;
	if (stream.Read(&bfh, BitmapFileHeader::bytes) < BitmapFileHeader::bytes) {
		IssueError_InvalidFormat();
		return false;
	}
	if (Gurax_UnpackUInt16(bfh.bfType) != 0x4d42) {
		IssueError_InvalidFormat();
		return false;
	}
	UInt32 bfOffBits = Gurax_UnpackUInt32(bfh.bfOffBits);
	BitmapInfoHeader bih;
	if (stream.Read(&bih, BitmapInfoHeader::bytes) < BitmapInfoHeader::bytes) {
		IssueError_InvalidFormat();
		return false;
	}
	Int32 biWidth = Gurax_UnpackInt32(bih.biWidth);
	Int32 biHeight = Gurax_UnpackInt32(bih.biHeight);
	UInt16 biBitCount = Gurax_UnpackUInt16(bih.biBitCount);
	if (!image.Allocate(biWidth, biHeight)) {
		Error::Issue(ErrorType::MemoryError, "failed to allocate memory");
		return false;
	}
	if (biBitCount == 1 || biBitCount == 4 || biBitCount == 8) {
		RefPtr<Palette> pPalette(ReadDIBPalette(stream, biBitCount));
		if (!pPalette) return false;
		image.SetPalette(pPalette.release());
	} else if (biBitCount == 24 || biBitCount == 32) {
		// nothing to do
	} else {
		IssueError_InvalidFormat();
		return false;
	}
	if (bfOffBits > 0 && !stream.SetOffset(bfOffBits)) return false;
	return ReadDIB(stream, image, biWidth, biHeight, biBitCount, false);
}

bool ImageMgrEx::Write(Stream& stream, const Image& image) const
{
	bool maskFlag = false;
	int biWidth = static_cast<int>(image.GetWidth());
	int biHeight = static_cast<int>(image.GetHeight());
	int biBitCount = CalcDIBBitCount(image);
	do {
		BitmapFileHeader bfh;
		::memset(&bfh, 0x00, BitmapFileHeader::bytes);
		UInt32 bfOffBits = BitmapFileHeader::bytes + BitmapInfoHeader::bytes;
		bfOffBits += CalcDIBPaletteSize(biBitCount);
		UInt32 bfSize = CalcDIBImageSize(biWidth, biHeight, biBitCount, maskFlag) + bfOffBits;
		Gurax_PackUInt16(bfh.bfType,			0x4d42);
		Gurax_PackUInt32(bfh.bfSize,			bfSize);
		Gurax_PackUInt32(bfh.bfOffBits,			bfOffBits);
		if (stream.Write(&bfh, BitmapFileHeader::bytes) < BitmapFileHeader::bytes) {
			Error::Issue(ErrorType::StreamError, "failed to write bitmap data");
			return false;
		}
	} while (0);
	do {
		BitmapInfoHeader bih;
		::memset(&bih, 0x00, BitmapInfoHeader::bytes);
		Gurax_PackUInt32(bih.biSize,			BitmapInfoHeader::bytes);
		Gurax_PackUInt32(bih.biWidth,			biWidth);
		Gurax_PackUInt32(bih.biHeight,			biHeight);
		Gurax_PackUInt16(bih.biPlanes,			1);
		Gurax_PackUInt16(bih.biBitCount,		biBitCount);
		Gurax_PackUInt32(bih.biCompression,		0);
		Gurax_PackUInt32(bih.biSizeImage,		0);
		Gurax_PackUInt32(bih.biXPelsPerMeter,	3780);
		Gurax_PackUInt32(bih.biYPelsPerMeter,	3780);
		Gurax_PackUInt32(bih.biClrUsed,			0);
		Gurax_PackUInt32(bih.biClrImportant,	0);
		if (stream.Write(&bih, BitmapInfoHeader::bytes) < BitmapInfoHeader::bytes) {
			Error::Issue(ErrorType::StreamError, "failed to write bitmap data");
			return false;
		}
	} while (0);
	const Palette* pPalette = image.GetPalette();
	if (pPalette && !WriteDIBPalette(stream, *pPalette, biBitCount)) return false;
	return WriteDIB(stream, image, biBitCount, false);
}

int ImageMgrEx::CalcDIBBitCount(const Image& image)
{
	const Palette* pPalette = image.GetPalette();
	if (!pPalette) return image.IsFormat(Image::Format::RGB)? 24 : 32;
	size_t nEntries = pPalette->GetSize();
	size_t nBits = 1;
	for ( ; nEntries > static_cast<size_t>(1 << nBits); nBits++) ;
	nBits =
		(nBits == 2 || nBits == 3)? 4 :
		(nBits == 5 || nBits == 6 || nBits == 7)? 8 :
		(nBits > 8)? 8 : nBits;
	return static_cast<int>(nBits);
}

UInt32 ImageMgrEx::CalcDIBImageSize(size_t width, size_t height, int biBitCount, bool maskFlag)
{
	size_t bytesPerLine = 0;
	if (biBitCount == 1) {
		bytesPerLine = (width + 7) / 8;
	} else if (biBitCount == 4) {
		bytesPerLine = (width + 1) / 2;
	} else if (biBitCount == 8) {
		bytesPerLine = width;
	} else if (biBitCount == 24) {
		bytesPerLine = width * 3;
	} else if (biBitCount == 32) {
		bytesPerLine = width * 4;
	}
	size_t bytes = ((bytesPerLine + 3) / 4 * 4) * height;
	if (maskFlag) {
		size_t bytesPerLine = (width + 7) / 8;
		bytes += ((bytesPerLine + 3) / 4 * 4) * height;
	}
	return static_cast<UInt32>(bytes);
}

Palette* ImageMgrEx::ReadDIBPalette(Stream& stream, int biBitCount)
{
	size_t nEntries = 1 << biBitCount;
	RefPtr<Palette> pPalette(new Palette(nEntries));
	for (size_t idx = 0; idx < nEntries; idx++) {
		UInt32 packed;
		if (stream.Read(&packed, 4) < 4) {
			Error::Issue(ErrorType::FormatError, "failed to read DIB palette");
			return nullptr;
		}
		pPalette->SetPacked(idx, packed);
	}
	return pPalette.release();
}

bool ImageMgrEx::WriteDIBPalette(Stream& stream, const Palette& palette, int biBitCount)
{
	size_t nEntries = 1 << biBitCount;
	size_t idxMax = std::min(nEntries, palette.GetSize());
	size_t idx = 0;
	for ( ; idx < idxMax; idx++) {
		UInt32 packed = palette.GetPacked(idx);
		if (stream.Write(&packed, 4) < 4) {
			Error::Issue(ErrorType::FormatError, "failed to write DIB palette");
			return false;
		}
	}
	UInt32 packed = 0;
	for (; idx < nEntries; idx++) {
		if (stream.Write(&packed, 4) < 4) {
			Error::Issue(ErrorType::FormatError, "failed to write DIB palette");
			return false;
		}

	}
	return true;
}

bool ImageMgrEx::ReadDIB(Stream& stream, Image& image, int biWidth, int biHeight, int biBitCount, bool maskFlag)
{
	bool vertRevFlag = true;
	if (biHeight < 0) {
		biHeight = -biHeight;
		vertRevFlag = false;
	}
	if (!image.Allocate(biWidth, biHeight)) return false;
	image.GetMemory()->Fill(0xff);
	const Palette* pPalette = image.GetPalette();
	if (biBitCount == 1) {
		size_t bytesPerLine = (biWidth + 7) / 8;
		size_t bytesAlign = (bytesPerLine + 3) / 4 * 4 - bytesPerLine;
		int bitsRest = 0;
		UInt8 ch;
		int iLine = 0, iPixel = 0;
		int bytesPitch = static_cast<int>(image.GetBytesPerLine());
		if (vertRevFlag) bytesPitch = -bytesPitch;
		UInt8* pLine = image.GetPointer(0, vertRevFlag? biHeight - 1 : 0);
		UInt8* pPixel = pLine;
		for (;;) {
			if (iPixel >= biWidth) {
				if (++iLine >= biHeight) break;
				iPixel = 0, pLine += bytesPitch, pPixel = pLine;
				if (!stream.Seek(static_cast<long>(bytesAlign), Stream::SeekMode::Cur)) return false;
				bitsRest = 0;
			}
			if (bitsRest == 0) {
				if (stream.Read(&ch, 1) < 1) break;
				bitsRest = 8;
			}
			UInt8 idx = ch >> 7;
			ch <<= 1, bitsRest--;
			Image::PixelRGB::SetPacked(pPixel, pPalette->GetPacked(idx));
			pPixel += image.GetBytesPerPixel();
			iPixel++;
		}
		if (Error::IsIssued()) return false;
	} else if (biBitCount == 4) {
#if 0
		size_t bytesPerLine = (biWidth + 1) / 2;
		size_t bytesAlign = (bytesPerLine + 3) / 4 * 4 - bytesPerLine;
		UChar ch;
		std::unique_ptr<Scanner> pScanner(CreateScanner(
				vertRevFlag? SCAN_LeftBottomHorz : SCAN_LeftTopHorz));
		if (stream.Read(sig, &ch, 1) < 1) return false;
		int bitsRest = 8;
		for (;;) {
			UChar idx = ch >> 4;
			ch <<= 4, bitsRest -= 4;
			StorePixelRGB(pScanner->GetPointer(), _pPalette->GetEntry(idx));
			if (!pScanner->NextPixel()) {
				if (!pScanner->NextLine()) break;
				stream.Seek(sig, static_cast<long>(bytesAlign), Stream::SeekCur);
				if (sig.IsSignalled()) return false;
				bitsRest = 0;
			}
			if (bitsRest == 0) {
				if (stream.Read(sig, &ch, 1) < 1) break;
				bitsRest = 8;
			}
		}
		if (sig.IsSignalled()) return false;
#endif
	} else if (biBitCount == 8) {
#if 0
		size_t bytesAlign = (biWidth + 3) / 4 * 4 - biWidth;
		UChar ch;
		std::unique_ptr<Scanner> pScanner(CreateScanner(
				vertRevFlag? SCAN_LeftBottomHorz : SCAN_LeftTopHorz));
		if (stream.Read(sig, &ch, 1) < 1) return false;
		for (;;) {
			StorePixelRGB(pScanner->GetPointer(), _pPalette->GetEntry(ch));
			if (!pScanner->NextPixel()) {
				if (!pScanner->NextLine()) break;
				stream.Seek(sig, static_cast<long>(bytesAlign), Stream::SeekCur);
				if (sig.IsSignalled()) return false;
			}
			if (stream.Read(sig, &ch, 1) < 1) break;
		}
		if (sig.IsSignalled()) return false;
#endif
	} else if (biBitCount == 24) {
#if 0
		size_t bytesAlign = (3 * biWidth + 3) / 4 * 4 - 3 * biWidth;
		UChar buff[3];
		std::unique_ptr<Scanner> pScanner(CreateScanner(
				vertRevFlag? SCAN_LeftBottomHorz : SCAN_LeftTopHorz));
		for (;;) {
			if (stream.Read(sig, buff, 3) < 3) break;
			StorePixel(pScanner->GetPointer(), buff[2], buff[1], buff[0]);
			if (!pScanner->NextPixel()) {
				if (!pScanner->NextLine()) break;
				stream.Seek(sig, static_cast<long>(bytesAlign), Stream::SeekCur);
				if (sig.IsSignalled()) return false;
			}
		}
		if (sig.IsSignalled()) return false;
#endif
	} else if (biBitCount == 32) {
#if 0
		UChar buff[4];
		std::unique_ptr<Scanner> pScanner(CreateScanner(
				vertRevFlag? SCAN_LeftBottomHorz : SCAN_LeftTopHorz));
		if (_format == FORMAT_RGBA) {
			while (stream.Read(sig, buff, 4) == 4) {
				StorePixel(pScanner->GetPointer(), buff[2], buff[1], buff[0], buff[3]);
				if (!pScanner->Next()) break;
			}
		} else {
			while (stream.Read(sig, buff, 4) == 4) {
				StorePixel(pScanner->GetPointer(), buff[2], buff[1], buff[0]);
				if (!pScanner->Next()) break;
			}
		}
		if (sig.IsSignalled()) return false;
#endif
	} else {
		// nothing to do
	}
	if (maskFlag) {
#if 0
		size_t bytesPerLine = (biWidth + 7) / 8;
		size_t bytesPerLineAligned = (bytesPerLine + 3) / 4 * 4;
		size_t bytesAlign = bytesPerLineAligned - bytesPerLine;
		if (GetFormat() == FORMAT_RGBA) {
			// read AND bitmap
			int bitsRest = 0;
			UChar ch;
			int iLine = 0, iPixel = 0;
			int bytesPitch = static_cast<int>(GetBytesPerLine());
			if (vertRevFlag) bytesPitch = -bytesPitch;
			UChar *pLine = GetPointer(vertRevFlag? biHeight - 1 : 0);
			UChar *pPixel = pLine;
			for (;;) {
				if (iPixel >= biWidth) {
					if (++iLine >= biHeight) break;
					iPixel = 0, pLine += bytesPitch, pPixel = pLine;
					stream.Seek(sig, static_cast<long>(bytesAlign), Stream::SeekCur);
					if (sig.IsSignalled()) return false;
					bitsRest = 0;
				}
				if (bitsRest == 0) {
					if (stream.Read(sig, &ch, 1) < 1) break;
					bitsRest = 8;
				}
				UChar idx = ch >> 7;
				ch <<= 1, bitsRest--;
				pPixel[OffsetA] = idx? 0 : 255;
				pPixel += GetBytesPerPixel();
				iPixel++;
			}
		} else {
			// just skip AND bitmap
			long bytes = static_cast<long>((bytesPerLine + 3) / 4 * 4 * GetHeight());
			stream.Seek(sig, bytes, Stream::SeekCur);
		}
		if (sig.IsSignalled()) return false;
#endif
	}
	return true;
}

bool ImageMgrEx::WriteDIB(Stream& stream, const Image& image, int biBitCount, bool maskFlag)
{
	//int biWidth = static_cast<int>(image.GetWidth());
	//int biHeight = static_cast<int>(GetHeight());
	if (biBitCount == 1) {
#if 0
		if (_pPalette.IsNull()) return false;
		size_t bytesPerLine = (biWidth + 7) / 8;
		size_t bytesAlign = (bytesPerLine + 3) / 4 * 4 - bytesPerLine;
		int bitsAccum = 0;
		UChar chAccum = 0x00;
		std::unique_ptr<Scanner> pScanner(CreateScanner(SCAN_LeftBottomHorz));
		for (;;) {
			UChar ch = static_cast<UChar>(
							_pPalette->LookupNearest(pScanner->GetPointer()));
			chAccum |= ch << ((8 - 1) - bitsAccum);
			bitsAccum += 1;
			if (bitsAccum >= 8) {
				stream.Write(sig, &chAccum, 1);
				if (sig.IsSignalled()) return false;
				chAccum = 0x00;
				bitsAccum = 0;
			}
			if (!pScanner->NextPixel()) {
				if (bitsAccum > 0) {
					stream.Write(sig, &chAccum, 1);
					if (sig.IsSignalled()) return false;
					chAccum = 0x00;
					bitsAccum = 0;
				}
				stream.Write(sig, "\x00\x00\x00\x00", bytesAlign);
				if (sig.IsSignalled()) return false;
				if (!pScanner->NextLine()) break;
			}
		}
#endif
	} else if (biBitCount == 4) {
#if 0
		if (_pPalette.IsNull()) return false;
		size_t bytesPerLine = (biWidth + 1) / 2;
		size_t bytesAlign = (bytesPerLine + 3) / 4 * 4 - bytesPerLine;
		int bitsAccum = 0;
		UChar chAccum = 0x00;
		std::unique_ptr<Scanner> pScanner(CreateScanner(SCAN_LeftBottomHorz));
		for (;;) {
			UChar ch = static_cast<UChar>(
							_pPalette->LookupNearest(pScanner->GetPointer()));
			chAccum |= ch << ((8 - 4) - bitsAccum);
			bitsAccum += 4;
			if (bitsAccum >= 8) {
				stream.Write(sig, &chAccum, 1);
				if (sig.IsSignalled()) return false;
				chAccum = 0x00;
				bitsAccum = 0;
			}
			if (!pScanner->NextPixel()) {
				if (bitsAccum > 0) {
					stream.Write(sig, &chAccum, 1);
					if (sig.IsSignalled()) return false;
					chAccum = 0x00;
					bitsAccum = 0;
				}
				stream.Write(sig, "\x00\x00\x00\x00", bytesAlign);
				if (sig.IsSignalled()) return false;
				if (!pScanner->NextLine()) break;
			}
		}
#endif
	} else if (biBitCount == 8) {
#if 0
		if (_pPalette.IsNull()) return false;
		size_t bytesAlign = (biWidth + 3) / 4 * 4 - biWidth;
		std::unique_ptr<Scanner> pScanner(CreateScanner(SCAN_LeftBottomHorz));
		for (;;) {
			UChar ch = static_cast<UChar>(
							_pPalette->LookupNearest(pScanner->GetPointer()));
			stream.Write(sig, &ch, 1);
			if (sig.IsSignalled()) return false;
			if (!pScanner->NextPixel()) {
				stream.Write(sig, "\x00\x00\x00\x00", bytesAlign);
				if (sig.IsSignalled()) return false;
				if (!pScanner->NextLine()) break;
			}
		}
#endif
	} else if (biBitCount == 24) {
#if 0
		size_t bytesAlign = ((3 * biWidth) + 3) / 4 * 4 - 3 * biWidth;
		UChar buff[3];
		std::unique_ptr<Scanner> pScanner(CreateScanner(SCAN_LeftBottomHorz));
		for (;;) {
			buff[0] = pScanner->GetB();
			buff[1] = pScanner->GetG();
			buff[2] = pScanner->GetR();
			stream.Write(sig, buff, 3);
			if (sig.IsSignalled()) return false;
			if (!pScanner->NextPixel()) {
				stream.Write(sig, "\x00\x00\x00\x00", bytesAlign);
				if (sig.IsSignalled()) return false;
				if (!pScanner->NextLine()) break;
			}
		}
#endif
	} else if (biBitCount == 32) {
#if 0
		UChar buff[4];
		std::unique_ptr<Scanner> pScanner(CreateScanner(SCAN_LeftBottomHorz));
		for (;;) {
			buff[0] = pScanner->GetB();
			buff[1] = pScanner->GetG();
			buff[2] = pScanner->GetR();
			buff[3] = pScanner->GetA();
			stream.Write(sig, buff, 4);
			if (sig.IsSignalled()) return false;
			if (!pScanner->Next()) break;
		}
#endif
	} else {
		// nothing to do
	}
	if (maskFlag) {
#if 0
		size_t bytesPerLine = (biWidth + 7) / 8;
		size_t bytesPerLineAligned = (bytesPerLine + 3) / 4 * 4;
		size_t bytesAlign = bytesPerLineAligned - bytesPerLine;
		if (GetFormat() == FORMAT_RGBA) {
			// write AND bitmap
			int bitsAccum = 0;
			UChar chAccum = 0x00;
			std::unique_ptr<Scanner> pScanner(CreateScanner(SCAN_LeftBottomHorz));
			for (;;) {
				UChar ch = (pScanner->GetA() < 128)? 1 : 0;
				chAccum |= ch << ((8 - 1) - bitsAccum);
				bitsAccum += 1;
				if (bitsAccum >= 8) {
					stream.Write(sig, &chAccum, 1);
					if (sig.IsSignalled()) return false;
					chAccum = 0x00;
					bitsAccum = 0;
				}
				if (!pScanner->NextPixel()) {
					if (bitsAccum > 0) {
						stream.Write(sig, &chAccum, 1);
						if (sig.IsSignalled()) return false;
						chAccum = 0x00;
						bitsAccum = 0;
					}
					stream.Write(sig, "\x00\x00\x00\x00", bytesAlign);
					if (sig.IsSignalled()) return false;
					if (!pScanner->NextLine()) break;
				}
			}
		} else {
			char *buff = new char [bytesPerLineAligned];
			::memset(buff, 0x00, bytesPerLineAligned);
			for (size_t y = 0; y < GetHeight(); y++) {
				stream.Write(sig, buff, bytesPerLineAligned);
				if (sig.IsSignalled()) break;
			}
			delete[] buff;
			if (sig.IsSignalled()) return false;
		}
#endif
	}
	return true;
}

Gurax_EndModuleScope(bmp)
