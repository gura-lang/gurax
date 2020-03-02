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
	BitmapFileHeader bfh;
	return stream.Read(&bfh, BitmapFileHeader::bytes) == BitmapFileHeader::bytes &&
		Gurax_UnpackUInt16(bfh.bfType) != 0x4d42;
}

bool ImageMgrEx::IsResponsibleExtName(const char* extName) const
{
	return ::strcasecmp(extName, ".bmp") == 0;
}

bool ImageMgrEx::Read(Stream& stream, Image& image) const
{
	BitmapFileHeader bfh;
	BitmapInfoHeader bih;
	if (stream.Read(&bfh, BitmapFileHeader::bytes) < BitmapFileHeader::bytes) {
		IssueError_InvalidFormat();
		return false;
	}
	if (stream.Read(&bih, BitmapInfoHeader::bytes) < BitmapInfoHeader::bytes) {
		IssueError_InvalidFormat();
		return false;
	}
	if (Gurax_UnpackUInt16(bfh.bfType) != 0x4d42) {
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
	UInt32 bfOffBits = Gurax_UnpackUInt32(bfh.bfOffBits);
	if (bfOffBits > 0 && !stream.SetOffset(bfOffBits)) return false;
	return ReadDIB(stream, image, biWidth, biHeight, biBitCount, false);
}

bool ImageMgrEx::Write(Stream& stream, const Image& image) const
{
	bool maskFlag = false;
	int biWidth = static_cast<int>(image.GetWidth());
	int biHeight = static_cast<int>(image.GetHeight());
	int biBitCount = CalcDIBBitCount(image);
	UInt32 biSizeImage = CalcDIBImageSize(biWidth, biHeight, biBitCount, maskFlag);
	do {
		BitmapFileHeader bfh;
		::memset(&bfh, 0x00, BitmapFileHeader::bytes);
		UInt32 bfOffBits = BitmapFileHeader::bytes + BitmapInfoHeader::bytes;
		bfOffBits += CalcDIBPaletteSize(biBitCount);
		UInt32 bfSize = biSizeImage + bfOffBits;
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
		Gurax_PackUInt32(bih.biSizeImage,		biSizeImage);
		Gurax_PackUInt32(bih.biXPelsPerMeter,	13780);
		Gurax_PackUInt32(bih.biYPelsPerMeter,	13780);
		Gurax_PackUInt32(bih.biClrUsed,			0);
		Gurax_PackUInt32(bih.biClrImportant,	0);
		if (stream.Write(&bih, BitmapInfoHeader::bytes) < BitmapInfoHeader::bytes) {
			Error::Issue(ErrorType::StreamError, "failed to write bitmap data");
			return false;
		}
	} while (0);
	RefPtr<Palette> pPalette(Palette::Reference(image.GetPalette()));
	if (pPalette && pPalette->GetSize() == (1 << biBitCount)) {
		// nothing to do
	} else if (biBitCount == 2) {
		pPalette.reset(Palette::Mono()->Reference());
	} else if (biBitCount == 4) {
		pPalette.reset(Palette::Basic()->Reference());
	} else if (biBitCount == 8) {
		pPalette.reset(Palette::Win256()->Reference());
	}
	if (pPalette && !WriteDIBPalette(stream, *pPalette, biBitCount)) return false;
	return WriteDIB(stream, image, pPalette.get(), biBitCount, false);
}

int ImageMgrEx::CalcDIBBitCount(const Image& image)
{
	const Palette* pPalette = image.GetPalette();
	if (!pPalette) return 24;
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
				if (!stream.Seek(static_cast<long>(bytesAlign), Stream::SeekMode::Cur)) {
					IssueError_InvalidFormat();
					return false;
				}
				bitsRest = 0;
			}
			if (bitsRest == 0) {
				if (stream.Read(&ch, 1) < 1) {
					IssueError_InvalidFormat();
					return false;
				}
				bitsRest = 8;
			}
			UInt8 idx = ch >> 7;
			ch <<= 1, bitsRest--;
			const Color& color = pPalette->GetColor(idx);
			Image::SetColorRGB(pPixel, color);
			pPixel += image.GetBytesPerPixel();
			iPixel++;
		}
	} else if (biBitCount == 4) {
		size_t bytesPerLine = (biWidth + 1) / 2;
		size_t bytesAlign = (bytesPerLine + 3) / 4 * 4 - bytesPerLine;
		UInt8 ch;
		Image::Scanner scanner(
			vertRevFlag? Image::Scanner::LeftBottomHorz(image) : Image::Scanner::LeftTopHorz(image));
		if (stream.Read(&ch, 1) < 1) {
			IssueError_InvalidFormat();
			return false;
		}
		int bitsRest = 8;
		for (;;) {
			UInt8 idx = ch >> 4;
			ch <<= 4, bitsRest -= 4;
			const Color& color = pPalette->GetColor(idx);
			Image::SetColorRGB(scanner.GetPointer(), color);
			if (!scanner.NextCol()) {
				if (!scanner.NextRow()) break;
				if (!stream.Seek(static_cast<long>(bytesAlign), Stream::SeekMode::Cur)) return false;
				bitsRest = 0;
			}
			if (bitsRest == 0) {
				if (stream.Read(&ch, 1) < 1) {
					IssueError_InvalidFormat();
					return false;
				}
				bitsRest = 8;
			}
		}
	} else if (biBitCount == 8) {
		size_t bytesAlign = (biWidth + 3) / 4 * 4 - biWidth;
		UInt8 ch;
		Image::Scanner scanner(
			vertRevFlag? Image::Scanner::LeftBottomHorz(image) : Image::Scanner::LeftTopHorz(image));
		if (stream.Read(&ch, 1) < 1) {
			IssueError_InvalidFormat();
			return false;
		}
		for (;;) {
			const Color& color = pPalette->GetColor(ch);
			Image::SetColorRGB(scanner.GetPointer(), color);
			if (!scanner.NextCol()) {
				if (!scanner.NextRow()) break;
				if (!stream.Seek(static_cast<long>(bytesAlign), Stream::SeekMode::Cur)) {
					IssueError_InvalidFormat();
					return false;
				}
			}
			if (stream.Read(&ch, 1) < 1) {
				IssueError_InvalidFormat();
				return false;
			}
		}
	} else if (biBitCount == 24) {
		size_t bytesAlign = (3 * biWidth + 3) / 4 * 4 - 3 * biWidth;
		UInt8 buff[3];
		Image::Scanner scanner(
			vertRevFlag? Image::Scanner::LeftBottomHorz(image) : Image::Scanner::LeftTopHorz(image));
		for (;;) {
			if (stream.Read(buff, 3) < 3) {
				IssueError_InvalidFormat();
				return false;
			}
			Image::SetRGB(scanner.GetPointer(), buff[2], buff[1], buff[0]);
			if (!scanner.NextCol()) {
				if (!scanner.NextRow()) break;
				if (!stream.Seek(static_cast<long>(bytesAlign), Stream::SeekMode::Cur)) {
					IssueError_InvalidFormat();
					return false;
				}
			}
		}
	} else if (biBitCount == 32) {
		UInt8 buff[4];
		Image::Scanner scanner(
			vertRevFlag? Image::Scanner::LeftBottomHorz(image) : Image::Scanner::LeftTopHorz(image));
		if (image.IsFormat(Image::Format::RGBA)) {
			while (stream.Read(buff, 4) == 4) {
				Image::SetRGBA(scanner.GetPointer(), buff[2], buff[1], buff[0], buff[3]);
				if (!scanner.Next()) break;
			}
		} else if (image.IsFormat(Image::Format::RGB)) {
			while (stream.Read(buff, 4) == 4) {
				Image::SetRGB(scanner.GetPointer(), buff[2], buff[1], buff[0]);
				if (!scanner.Next()) break;
			}
		}
	} else {
		// nothing to do
	}
	if (maskFlag) {
		size_t bytesPerLine = (biWidth + 7) / 8;
		size_t bytesPerLineAligned = (bytesPerLine + 3) / 4 * 4;
		size_t bytesAlign = bytesPerLineAligned - bytesPerLine;
		if (image.IsFormat(Image::Format::RGBA)) {
			// read AND bitmap
			int bitsRest = 0;
			UInt8 ch;
			int iLine = 0, iPixel = 0;
			int bytesPitch = static_cast<int>(image.GetBytesPerLine());
			if (vertRevFlag) bytesPitch = -bytesPitch;
			UInt8 *pLine = image.GetPointer(0, vertRevFlag? biHeight - 1 : 0);
			UInt8 *pPixel = pLine;
			for (;;) {
				if (iPixel >= biWidth) {
					if (++iLine >= biHeight) break;
					iPixel = 0, pLine += bytesPitch, pPixel = pLine;
					if (!stream.Seek(static_cast<long>(bytesAlign), Stream::SeekMode::Cur)) {
						IssueError_InvalidFormat();
						return false;
					}
					bitsRest = 0;
				}
				if (bitsRest == 0) {
					if (stream.Read(&ch, 1) < 1) {
						IssueError_InvalidFormat();
						return false;
					}
					bitsRest = 8;
				}
				UInt8 idx = ch >> 7;
				ch <<= 1, bitsRest--;
				pPixel[Image::offsetA] = idx? 0 : 255;
				pPixel += image.GetBytesPerPixel();
				iPixel++;
			}
		} else {
			// just skip AND bitmap
			long bytes = static_cast<long>((bytesPerLine + 3) / 4 * 4 * image.GetHeight());
			if (!stream.Seek(bytes, Stream::SeekMode::Cur)) {
				IssueError_InvalidFormat();
				return false;
			}
		}
	}
	return true;
}

bool ImageMgrEx::WriteDIB(Stream& stream, const Image& image, const Palette* pPalette, int biBitCount, bool maskFlag)
{
	int biWidth = static_cast<int>(image.GetWidth());
	int biHeight = static_cast<int>(image.GetHeight());
	if (biBitCount == 1) {
		size_t bytesPerLine = (biWidth + 7) / 8;
		size_t bytesAlign = (bytesPerLine + 3) / 4 * 4 - bytesPerLine;
		int bitsAccum = 0;
		UInt8 chAccum = 0x00;
		Image::Scanner scanner(Image::Scanner::LeftBottomHorz(image));
		for (;;) {
			const UInt8* p = scanner.GetPointer();
			UInt8 ch = static_cast<UInt8>(
				pPalette->LookupNearest(Image::GetR(p), Image::GetG(p), Image::GetB(p)));
			chAccum |= ch << ((8 - 1) - bitsAccum);
			bitsAccum += 1;
			if (bitsAccum >= 8) {
				if (stream.Write(&chAccum, 1) < 1) {
					IssueError_FailToWrite();
					return false;
				}
				chAccum = 0x00;
				bitsAccum = 0;
			}
			if (!scanner.NextCol()) {
				if (bitsAccum > 0) {
					if (stream.Write(&chAccum, 1) < 1) {
						IssueError_FailToWrite();
						return false;
					}
					chAccum = 0x00;
					bitsAccum = 0;
				}
				if (stream.Write("\x00\x00\x00\x00", bytesAlign) < bytesAlign) {
					IssueError_FailToWrite();
					return false;
				}
				if (!scanner.NextRow()) break;
			}
		}
	} else if (biBitCount == 4) {
		size_t bytesPerLine = (biWidth + 1) / 2;
		size_t bytesAlign = (bytesPerLine + 3) / 4 * 4 - bytesPerLine;
		int bitsAccum = 0;
		UInt8 chAccum = 0x00;
		Image::Scanner scanner(Image::Scanner::LeftBottomHorz(image));
		for (;;) {
			const UInt8* p = scanner.GetPointer();
			UInt8 ch = static_cast<UInt8>(
				pPalette->LookupNearest(Image::GetR(p), Image::GetG(p), Image::GetB(p)));
			chAccum |= ch << ((8 - 4) - bitsAccum);
			bitsAccum += 4;
			if (bitsAccum >= 8) {
				if (stream.Write(&chAccum, 1) < 1) {
					IssueError_FailToWrite();
					return false;
				}
				chAccum = 0x00;
				bitsAccum = 0;
			}
			if (!scanner.NextCol()) {
				if (bitsAccum > 0) {
					if (stream.Write(&chAccum, 1) < 1) {
						IssueError_FailToWrite();
						return false;
					}
					chAccum = 0x00;
					bitsAccum = 0;
				}
				if (stream.Write("\x00\x00\x00\x00", bytesAlign) < bytesAlign) {
					IssueError_FailToWrite();
					return false;
				}
				if (!scanner.NextRow()) break;
			}
		}
	} else if (biBitCount == 8) {
		size_t bytesAlign = (biWidth + 3) / 4 * 4 - biWidth;
		Image::Scanner scanner(Image::Scanner::LeftBottomHorz(image));
		for (;;) {
			const UInt8* p = scanner.GetPointer();
			UInt8 ch = static_cast<UInt8>(
				pPalette->LookupNearest(Image::GetR(p), Image::GetG(p), Image::GetB(p)));
			if (stream.Write(&ch, 1) < 1) {
				IssueError_FailToWrite();
				return false;
			}
			if (!scanner.NextCol()) {
				if (stream.Write("\x00\x00\x00\x00", bytesAlign) < bytesAlign) {
					IssueError_FailToWrite();
					return false;
				}
				if (!scanner.NextRow()) break;
			}
		}
	} else if (biBitCount == 24) {
		size_t bytesAlign = ((3 * biWidth) + 3) / 4 * 4 - 3 * biWidth;
		UInt8 buff[3];
		Image::Scanner scanner(Image::Scanner::LeftBottomHorz(image));
		for (;;) {
			const UInt8* p = scanner.GetPointer();
			buff[0] = Image::GetB(p);
			buff[1] = Image::GetG(p);
			buff[2] = Image::GetR(p);
			if (stream.Write(buff, 3) < 3) {
				IssueError_FailToWrite();
				return false;
			}
			if (!scanner.NextCol()) {
				if (stream.Write("\x00\x00\x00\x00", bytesAlign) < bytesAlign) {
					IssueError_FailToWrite();
					return false;
				}
				if (!scanner.NextRow()) break;
			}
		}
	} else if (biBitCount == 32) {
		UInt8 buff[4];
		buff[3] = 0x00;
		Image::Scanner scanner(Image::Scanner::LeftBottomHorz(image));
		for (;;) {
			const UInt8* p = scanner.GetPointer();
			buff[0] = Image::GetB(p);
			buff[1] = Image::GetG(p);
			buff[2] = Image::GetR(p);
			if (stream.Write(buff, 4) < 4) {
				IssueError_FailToWrite();
				return false;
			}
			if (!scanner.Next()) break;
		}
	} else {
		// nothing to do
	}
	if (maskFlag) {
		size_t bytesPerLine = (biWidth + 7) / 8;
		size_t bytesPerLineAligned = (bytesPerLine + 3) / 4 * 4;
		size_t bytesAlign = bytesPerLineAligned - bytesPerLine;
		if (image.IsFormat(Image::Format::RGBA)) {
			// write AND bitmap
			int bitsAccum = 0;
			UInt8 chAccum = 0x00;
			Image::Scanner scanner(Image::Scanner::LeftBottomHorz(image));
			for (;;) {
				const UInt8* p = scanner.GetPointer();
				UInt8 ch = (Image::GetA(p) < 128)? 1 : 0;
				chAccum |= ch << ((8 - 1) - bitsAccum);
				bitsAccum += 1;
				if (bitsAccum >= 8) {
					if (stream.Write(&chAccum, 1) < 1) {
						IssueError_FailToWrite();
						return false;
					}
					chAccum = 0x00;
					bitsAccum = 0;
				}
				if (!scanner.NextCol()) {
					if (bitsAccum > 0) {
						if (stream.Write(&chAccum, 1) < 1) {
							IssueError_FailToWrite();
							return false;
						}
						chAccum = 0x00;
						bitsAccum = 0;
					}
					if (stream.Write("\x00\x00\x00\x00", bytesAlign) < bytesAlign) {
						IssueError_FailToWrite();
						return false;
					}
					if (!scanner.NextRow()) break;
				}
			}
		} else {
			std::unique_ptr<UInt8[]> buff(new UInt8 [bytesPerLineAligned]);
			::memset(buff.get(), 0x00, bytesPerLineAligned);
			for (size_t y = 0; y < biHeight; y++) {
				if (stream.Write(buff.get(), bytesPerLineAligned) < bytesPerLineAligned) {
					IssueError_FailToWrite();
					return false;
				}
			}
		}
	}
	return true;
}

Gurax_EndModuleScope(bmp)
