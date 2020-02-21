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
	::printf("check %d %d %d\n", biWidth, biHeight, biBitCount);
	if (!image.Allocate(biWidth, biHeight)) {
		Error::Issue(ErrorType::MemoryError, "failed to allocate memory");
		return false;
	}
	return false;
#if 0

	if (!pImage->ReadDIBPalette(env, stream, biBitCount)) return false;
	if (bfOffBits != 0) {
		stream.Seek(sig, bfOffBits, Stream::SeekSet);
		if (sig.IsSignalled()) return false;
	}
	return pImage->ReadDIB(sig, stream, biWidth, biHeight, biBitCount, false);
#endif
}

bool ImageMgrEx::Write(Stream& stream, const Image& image) const
{
	return false;
}

int ImageMgrEx::CalcDIBBitCount() const
{
#if 0
	if (GetPalette() == nullptr) return static_cast<int>(GetBitsPerPixel());
	size_t nEntries = GetPalette()->CountEntries();
	size_t nBits = 1;
	for ( ; nEntries > static_cast<size_t>(1 << nBits); nBits++) ;
	nBits =
		(nBits == 2 || nBits == 3)? 4 :
		(nBits == 5 || nBits == 6 || nBits == 7)? 8 :
		(nBits > 8)? 8 : nBits;
	return static_cast<int>(nBits);
#endif
	return 0;
}

size_t ImageMgrEx::CalcDIBImageSize(int biBitCount, bool maskFlag) const
{
#if 0
	size_t bytesPerLine = 0;
	if (biBitCount == 1) {
		bytesPerLine = (_width + 7) / 8;
	} else if (biBitCount == 4) {
		bytesPerLine = (_width + 1) / 2;
	} else if (biBitCount == 8) {
		bytesPerLine = _width;
	} else if (biBitCount == 24) {
		bytesPerLine = _width * 3;
	} else if (biBitCount == 32) {
		bytesPerLine = _width * 4;
	}
	size_t bytes = ((bytesPerLine + 3) / 4 * 4) * _height;
	if (maskFlag) {
		size_t bytesPerLine = (_width + 7) / 8;
		bytes += ((bytesPerLine + 3) / 4 * 4) * _height;
	}
	return bytes;
#endif
	return 0;
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

bool ImageMgrEx::WriteDIBPalette(Stream& stream, int biBitCount)
{
#if 0
	Signal &sig = env.GetSignal();
	if (biBitCount == 24 || biBitCount == 32) return true;
	if (!(biBitCount == 1 || biBitCount == 4 || biBitCount == 8)) {
		sig.SetError(ERR_FormatError, "unsupported pixel depth %d", biBitCount);
		return false;
	}
	size_t nEntries = 1 << biBitCount;
	if (_pPalette.IsNull()) {
		_pPalette.reset(new Palette());
		if (biBitCount == 1) {
			_pPalette->Prepare(sig, Gura_Symbol(mono));
		} else if (biBitCount == 4) {
			_pPalette->Prepare(sig, Gura_Symbol(basic));
		} else { // biBitCount == 8
			_pPalette->Prepare(sig, Gura_Symbol(win256));
		}
		if (sig.IsSignalled()) return false;
	}
	size_t idx = 0;
	size_t idxMax = ChooseMin(nEntries, _pPalette->CountEntries());
	UChar buff[4];
	for ( ; idx < idxMax; idx++) {
		const UChar *pEntry = _pPalette->GetEntry(idx);
		buff[0] = GetPixelB(pEntry);
		buff[1] = GetPixelG(pEntry);
		buff[2] = GetPixelR(pEntry);
		buff[3] = 0x00;
		stream.Write(sig, buff, 4);
		if (sig.IsSignalled()) return false;
	}
	::memset(buff, 0x00, 4);
	for (; idx < nEntries; idx++) {
		stream.Write(sig, buff, 4);
		if (sig.IsSignalled()) return false;
	}
#endif
	return true;
}

Gurax_EndModuleScope(bmp)
