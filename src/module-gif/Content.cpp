//==============================================================================
// Content.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// Content
//------------------------------------------------------------------------------
Content::Content()
{
}

Content::~Content()
{
}

bool Content::Read(Stream& stream, Image* pImageTgt, Image::Format format)
{
#if 0
	Signal &sig = env.GetSignal();
	if (!ReadBuff(sig, stream, &_header, 6)) return false;
	if (::memcmp(_header.Signature, "GIF", 3) != 0) {
		sig.SetError(ERR_FormatError, "Not a GIF file");
		return false;
	}
	if (::memcmp(_header.Version, "87a", 3) != 0 &&
							::memcmp(_header.Version, "89a", 3) != 0) {
		sig.SetError(ERR_FormatError, "unsupported version of Content file");
		return false;
	}
	if (!ReadBuff(sig, stream, &_logicalScreenDescriptor, 7)) return false;
	if (_logicalScreenDescriptor.GlobalColorTableFlag()) {
		int nEntries = 1 << (_logicalScreenDescriptor.SizeOfGlobalColorTable() + 1);
		_pPaletteGlobal.reset(new Palette());
		_pPaletteGlobal->AllocBuff(nEntries);
		if (!ReadColorTable(sig, stream, _pPaletteGlobal.get())) return false;
	}
	GetList().clear();
	GraphicControlExtension graphicControl;
	do {
		// set default values
		graphicControl.BlockSize = 4;
		graphicControl.PackedFields = (1 << 2) | (0 << 1) | (0 << 0);
		Gura_PackUInt16(graphicControl.DelayTime, 0);
		graphicControl.TransparentColorIndex = 0;
	} while (0);
	for (;;) {
		UInt8 imageSeparator;
		size_t bytesRead = stream.Read(sig, &imageSeparator, 1);
		if (bytesRead < 1) break;
		//::printf("%02x\n", imageSeparator);
		if (imageSeparator == SEP_ImageDescriptor) {
			if (pImageTgt != nullptr) {
				ReadImageDescriptor(env, sig, stream, graphicControl, pImageTgt, nullptr);
				break;
			} else if (format == Image::FORMAT_None) {
				if (!SkipImageDescriptor(sig, stream)) break;
			} else {
				AutoPtr<Object_image> pObjImage(new Object_image(env, new Image(format)));
				Value valueGIF;
				if (!ReadImageDescriptor(env, sig, stream,
						graphicControl, pObjImage->GetImage(), &valueGIF)) break;
				pObjImage->AssignValue(Gura_UserSymbol(gif), valueGIF, EXTRA_Public);
				GetList().push_back(Value(pObjImage.release()));
			}
		} else if (imageSeparator == SEP_ExtensionIntroducer) {
			UInt8 label;
			if (!ReadBuff(sig, stream, &label, 1)) break;
			//::printf("%02x - %02x\n", imageSeparator, label);
			if (label == GraphicControlExtension::Label) {
				if (!ReadBuff(sig, stream, &graphicControl, 5)) break;
				UInt8 blockTerminator;
				if (!ReadBuff(sig, stream, &blockTerminator, 1)) break;
			} else if (label == CommentExtension::Label) {
				_exts.comment.validFlag = true;
				if (!ReadDataBlocks(sig, stream, _exts.comment.CommentData)) break;
			} else if (label == PlainTextExtension::Label) {
				_exts.plainText.validFlag = true;
				if (!ReadBuff(sig, stream, &_exts.plainText, 13)) break;
				if (!ReadDataBlocks(sig, stream, _exts.plainText.PlainTextData)) break;
			} else if (label == ApplicationExtension::Label) {
				_exts.application.validFlag = true;
				if (!ReadBuff(sig, stream, &_exts.application, 12)) break;
				if (!ReadDataBlocks(sig, stream, _exts.application.ApplicationData)) break;
			}
			if (sig.IsSignalled()) break;
		} else if (imageSeparator == SEP_Trailer) {
			//::printf("%02x\n", imageSeparator);
			break;
		} else {
			sig.SetError(ERR_FormatError, "unknown separator %02x", imageSeparator);
			break;
		}
	}
	return !sig.IsSignalled();
#endif
	return false;
}

bool Content::Write(Stream& stream, const Color& colorBackground, bool validBackgroundFlag, UInt16 loopCount)
{
#if 0
	Signal &sig = env.GetSignal();
	if (GetList().empty()) {
		sig.SetError(ERR_ValueError, "no image to write");
		return false;
	}
	_pPaletteGlobal.reset(new Palette());
	_pPaletteGlobal->AllocBuff(256);
	size_t logicalScreenWidth = 0, logicalScreenHeight = 0;
	ValueList &valList = GetList();
	foreach (ValueList, pValue, valList) {
		if (!pValue->Is_image()) continue;
		const Object_image* pObjImage = Object_image::GetObject(*pValue);
		const Image* pImage = pObjImage->GetImage();
		const Palette* pPalette = pImage->GetPalette();
		if (pPalette != nullptr && pPalette->CountEntries() <= 256) {
			if (_pPaletteGlobal->UpdateByPalette(pPalette, Palette::ShrinkNone)) {
				// nothing to do
			} else if (_pPaletteGlobal->Prepare(sig, Gura_Symbol(websafe))) {
				break;
			} else {
				return false;
			}
		} else if (_pPaletteGlobal->UpdateByImage(pImage, Palette::ShrinkNone)) {
			// nothing to do
		} else if (_pPaletteGlobal->Prepare(sig, Gura_Symbol(websafe))) {
			break;
		} else {
			return false;
		}
	}
	int backgroundColorIndex = -1;
	UInt8 transparentColorIndex = 0;
	UInt8 transparentColorFlag = 0;
	do {
		size_t idxBlank = _pPaletteGlobal->NextBlankIndex();
		if (idxBlank < _pPaletteGlobal->CountEntries()) {
			// add an entry for transparent color
			_pPaletteGlobal->SetEntry(idxBlank, 128, 128, 128, 0);
			transparentColorIndex = static_cast<UInt8>(idxBlank);
			transparentColorFlag = 1;
			idxBlank++;
		}
		_pPaletteGlobal->Shrink(idxBlank, true);
	} while (0);
	if (validBackgroundFlag) {
		backgroundColorIndex = static_cast<int>(
				_pPaletteGlobal->LookupNearest(colorBackground));
	}
	foreach (ValueList, pValue, valList) {
		if (!pValue->Is_image()) continue;
		Object_image* pObjImage = Object_image::GetObject(*pValue);
		Image* pImage = pObjImage->GetImage();
		if (!pImage->CheckValid(sig)) return false;
		pImage->SetPalette(Palette::Reference(_pPaletteGlobal.get()));
		ImageDescriptor* pImageDescriptor = GetImageDescriptor(pObjImage);
		size_t width = pImage->GetWidth() +
						Gura_UnpackUInt16(pImageDescriptor->ImageLeftPosition);
		size_t height = pImage->GetHeight() +
						Gura_UnpackUInt16(pImageDescriptor->ImageTopPosition);
		if (logicalScreenWidth < width) logicalScreenWidth = width;
		if (logicalScreenHeight < height) logicalScreenHeight = height;
		GraphicControlExtension* pGraphicControl = GetGraphicControl(pObjImage);
		pGraphicControl->TransparentColorIndex = transparentColorIndex;
		pGraphicControl->PackedFields |= transparentColorFlag;
		if (backgroundColorIndex < 0) {
			backgroundColorIndex = GetPlausibleBackgroundIndex(
											_pPaletteGlobal.get(), pImage);
		}
	}
	if (backgroundColorIndex < 0) backgroundColorIndex = 0;
	do {
		UInt8 globalColorTableFlag = 1;
		UInt8 colorResolution = 7;
		UInt8 sortFlag = 0;
		UInt8 sizeOfGlobalColorTable = 0;
		int nEntries = static_cast<int>(_pPaletteGlobal->CountEntries());
		for ( ; nEntries > (1 << sizeOfGlobalColorTable); sizeOfGlobalColorTable++) ;
		sizeOfGlobalColorTable--;
		Gura_PackUInt16(_logicalScreenDescriptor.LogicalScreenWidth,
						static_cast<UInt16>(logicalScreenWidth));
		Gura_PackUInt16(_logicalScreenDescriptor.LogicalScreenHeight,
						static_cast<UInt16>(logicalScreenHeight));
		_logicalScreenDescriptor.PackedFields =
				(globalColorTableFlag << 7) | (colorResolution << 4) |
				(sortFlag << 3) | (sizeOfGlobalColorTable << 0);
		_logicalScreenDescriptor.BackgroundColorIndex =
						static_cast<UInt8>(backgroundColorIndex);
		_logicalScreenDescriptor.PixelAspectRatio = 0;
	} while (0);
	do {
		_exts.application.validFlag = true;
		_exts.application.BlockSize = 11;
		::memcpy(_exts.application.ApplicationIdentifier, "NETSCAPE", 8);
		::memcpy(_exts.application.AuthenticationCode, "2.0", 3);
		UInt8 applicationData[3];
		applicationData[0] = 0x01;
		applicationData[1] = static_cast<UInt8>(loopCount & 0xff);
		applicationData[2] = static_cast<UInt8>((loopCount >> 8) & 0xff);
		_exts.application.ApplicationData =
						Binary(reinterpret_cast<char* >(applicationData), 3);
	} while (0);
	// Header
	if (!WriteBuff(sig, stream, &_header, 6)) return false;
	// Logical Screen Descriptor
	if (!WriteBuff(sig, stream, &_logicalScreenDescriptor, 7)) return false;
	// Global Color Table
	if (_logicalScreenDescriptor.GlobalColorTableFlag()) {
		if (!WriteColorTable(sig, stream, _pPaletteGlobal.get())) return false;
	}
	if (_exts.application.validFlag) {
		// Application
		const UInt8 buff[] = {
			SEP_ExtensionIntroducer, ApplicationExtension::Label
		};
		if (!WriteBuff(sig, stream, &buff, 2)) return false;
		if (!WriteBuff(sig, stream, &_exts.application, 12)) return false;
		if (!WriteDataBlocks(sig, stream, _exts.application.ApplicationData)) return false;
	}
	foreach (ValueList, pValue, GetList()) {
		if (!pValue->Is_image()) continue;
		Object_image* pObjImage = Object_image::GetObject(*pValue);
		Image* pImage = pObjImage->GetImage();
		GraphicControlExtension* pGraphicControl = GetGraphicControl(pObjImage);
		if (pGraphicControl == nullptr) continue;
		if (!WriteGraphicControl(sig, stream, *pGraphicControl)) return false;
		if (!WriteImageDescriptor(env, sig, stream, *pGraphicControl, pObjImage)) return false;
	}
	do {
		// Trailer
		const UInt8 buff[] = { SEP_Trailer };
		if (!WriteBuff(sig, stream, buff, 1)) return false;
	} while (0);
#endif
	return false;
}

bool Content::ReadDataBlocks(Stream& stream, Binary& binary)
{
#if 0
	for (;;) {
		UInt8 blockSize;
		if (!ReadBuff(sig, stream, &blockSize, 1)) return false;
		if (blockSize == 0) break;
		char buff[256];
		if (!ReadBuff(sig, stream, buff, blockSize)) return false;
		binary.append(buff, blockSize);
	}
#endif
	return true;
}

bool Content::WriteDataBlocks(Stream& stream, const Binary& binary)
{
#if 0
	size_t size = binary.size();
	for (size_t offset = 0; offset < size; ) {
		UInt8 blockSize =
			static_cast<UInt8>((size - offset <= 255)? size - offset : 255);
		if (!WriteBuff(sig, stream, &blockSize, 1)) return false;
		if (!WriteBuff(sig, stream, binary.data() + offset, blockSize)) return false;
		offset += blockSize;
	}
	do {
		UInt8 blockSize = 0x00;
		if (!WriteBuff(sig, stream, &blockSize, 1)) return false;
	} while (0);
#endif
	return true;
}

bool Content::SkipImageDescriptor(Stream& stream)
{
#if 0
	ImageDescriptor imageDescriptor;
	if (!ReadBuff(sig, stream, &imageDescriptor, 9)) return false;
	if (imageDescriptor.LocalColorTableFlag()) {
		int nEntries = 1 << (imageDescriptor.SizeOfLocalColorTable() + 1);
		stream.Seek(sig, nEntries * 3, Stream::SeekCur);
	}
	UInt8 mininumBitsOfCode;
	if (!ReadBuff(sig, stream, &mininumBitsOfCode, 1)) return false;
	for (;;) {
		UInt8 blockSize;
		if (!ReadBuff(sig, stream, &blockSize, 1)) return false;
		if (blockSize == 0) break;
		if (!stream.Seek(sig, blockSize, Stream::SeekCur)) return false;
	}
#endif
	return true;
}

bool Content::ReadImageDescriptor(Stream& stream, const GraphicControlExtension& graphicControl, Image* pImage, Value* pValueGIF)
{
#if 0
	ImageDescriptor imageDescriptor;
	if (!ReadBuff(sig, stream, &imageDescriptor, 9)) return false;
	size_t imageWidth = Gura_UnpackUInt16(imageDescriptor.ImageWidth);
	size_t imageHeight = Gura_UnpackUInt16(imageDescriptor.ImageHeight);
	if (!pImage->AllocBuffer(sig, imageWidth, imageHeight, 0xff)) return false;
	Palette* pPalette = nullptr;
	if (imageDescriptor.LocalColorTableFlag()) {
		size_t nEntries = 1 << (imageDescriptor.SizeOfLocalColorTable() + 1);
		pPalette = pImage->CreateEmptyPalette(env, nEntries);
		if (!ReadColorTable(sig, stream, pPalette)) return false;
	} else {
		pPalette = Palette::Reference(_pPaletteGlobal.get());
		pImage->SetPalette(pPalette);
	}
	if (pValueGIF != nullptr) {
		AutoPtr<Object_GraphicControl> pObjGraphicControl(
								new Object_GraphicControl(graphicControl));
		AutoPtr<Object_ImageDescriptor> pObjImageDescriptor(
								new Object_ImageDescriptor(imageDescriptor));
		*pValueGIF = Value(new Object_imgprop(pObjGraphicControl.release(), pObjImageDescriptor.release()));
	}
	short transparentColorIndex = graphicControl.TransparentColorIndex;
	if (!graphicControl.TransparentColorFlag() ||
					pImage->GetFormat() != Image::FORMAT_RGBA) {
		transparentColorIndex = -1;
	}
	const int maximumBitsOfCode = 12;
	UInt8 mininumBitsOfCode;
	if (!ReadBuff(sig, stream, &mininumBitsOfCode, 1)) return false;
	int bitsOfCode = mininumBitsOfCode + 1;
	if (bitsOfCode > maximumBitsOfCode) {
		sig.SetError(ERR_FormatError, "illegal code size");
		return false;
	}
	bool interlaceFlag = (imageDescriptor.InterlaceFlag() != 0);
	const UInt16 codeInvalid = 0xffff;
	UInt16 codeMaxCeiling = 1 << maximumBitsOfCode;
	UInt16 codeBoundary = 1 << mininumBitsOfCode;
	UInt16 codeClear = codeBoundary;
	UInt16 codeEnd = codeBoundary + 1;
	UInt16 codeMax = codeBoundary + 2;
	UInt16 codeFirst = codeInvalid, codeOld = codeInvalid;
	const size_t bytesCodeTable = codeMaxCeiling * 2;
	const size_t bytesCodeStack = codeMaxCeiling * 2;
	UInt16* codeTable = new UInt16 [bytesCodeTable];
	UInt16* codeStack = new UInt16 [bytesCodeStack];
	UInt16* pCodeStack = codeStack;
	do {
		::memset(codeTable, 0x00, bytesCodeTable);
		for (UInt16 code = 0; code < codeBoundary; code++) {
			codeTable[code * 2 + 1] = code;
		}
	} while (0);
	ImageDataBlock imageDataBlock;
	size_t x = 0, y = 0;
	int iPass = 0;
	UInt8* dstp = pImage->GetPointer(0);
	for (;;) {
		UInt16 code = 0;
		if (pCodeStack > codeStack) {
			pCodeStack--;
			code =* pCodeStack;
		} else {
			if (!imageDataBlock.ReadCode(sig, stream, code, bitsOfCode)) break;
			// LZW (Lempel-Ziv-Welch) decompression algorithm
			if (code == codeClear) {
				//::printf("clear\n");
				UInt16 code = 0;
				::memset(codeTable, 0x00, bytesCodeTable);
				for (UInt16 code = 0; code < codeBoundary; code++) {
					codeTable[code * 2 + 1] = code;
				}
				pCodeStack = codeStack;
				bitsOfCode = mininumBitsOfCode + 1;
				codeMax = codeBoundary + 2;
				codeFirst = codeOld = codeInvalid;
				continue;
			} else if (code == codeEnd) {
				// skip trailing blocks
				for (;;) {
					UInt8 blockSize;
					if (!ReadBuff(sig, stream, &blockSize, 1)) break;
					if (blockSize == 0) break;
					if (!stream.Seek(sig, blockSize, Stream::SeekCur)) break;
				}
				break;
			} else if (codeFirst == codeInvalid) {
				codeFirst = codeOld = code;
			} else {
				UInt16 codeIn = code;
				if (code >= codeMax) {
					*pCodeStack++ = codeFirst;
					code = codeOld;
				}
				while (code >= codeBoundary) {
					*pCodeStack++ = codeTable[code * 2 + 1];
					if (code == codeTable[code * 2 + 0]) {
						sig.SetError(ERR_FormatError, "invalid GIF format");
						goto done;
					}
					code = codeTable[code * 2 + 0];
				}
				codeFirst = codeTable[code * 2 + 1];
				*pCodeStack++ = codeFirst;
				if (codeMax < codeMaxCeiling) {
					codeTable[codeMax * 2 + 0] = codeOld;
					codeTable[codeMax * 2 + 1] = codeFirst;
					codeMax++;
					if (codeMax >= (1 << bitsOfCode) &&
											(1 << bitsOfCode) < codeMaxCeiling) {
						bitsOfCode++;
					}
				}
				codeOld = codeIn;
				if (pCodeStack > codeStack) {
					pCodeStack--;
					code = *pCodeStack;
				}
			}
		}
		const UInt8* srcp = pPalette->GetEntry(code);
		if (x >= imageWidth) {
			x = 0;
			if (interlaceFlag) {
				static const int yStepTbl[] = { 8, 8, 4, 2, };
				y += yStepTbl[iPass];
				if (y >= imageHeight) {
					static const int yTbl[] = { 4, 2, 1, };
					if (iPass >= 3) break;
					y = yTbl[iPass++];
				}
			} else {
				y++;
				if (y >= imageHeight) break;
			}
			dstp = pImage->GetPointer(y);
		}
		//::printf("+ %3d,%3d code = %03x\n", x, y, code);
		*(dstp + 0) = *srcp++;
		*(dstp + 1) = *srcp++;
		*(dstp + 2) = *srcp++;
		if (code == transparentColorIndex) *(dstp + 3) = 0x00;
		dstp += pImage->GetBytesPerPixel();
		x++;
	}
done:
	delete[] codeTable;
	delete[] codeStack;
	return !sig.IsSignalled();
#endif
	return false;
}

bool Content::WriteGraphicControl(Stream& stream, const GraphicControlExtension& graphicControl)
{
	const UInt8 buff[] = {
		Sep::ExtensionIntroducer, GraphicControlExtension::Label
	};
	UInt8 blockTerminator = 0x00;
	if (!WriteBuff(stream, buff, 2)) return false;
	if (!WriteBuff(stream, &graphicControl, 5)) return false;
	if (!WriteBuff(stream, &blockTerminator, 1)) return false;
	return true;
}

bool Content::WriteImageDescriptor(Stream& stream, const GraphicControlExtension& graphicControl, Image& image)
{
#if 0
	Image* pImage = pObjImage->GetImage();
	do {
		const UInt8 buff[] = { SEP_ImageDescriptor };
		if (!WriteBuff(sig, stream, buff, 1)) return false;
	} while (0);
	const Palette* pPalette = _pPaletteGlobal.get();
	ImageDescriptor* pImageDescriptor = GetImageDescriptor(pObjImage);
	if (pImageDescriptor == nullptr) {
		return false;
	}
	if (!WriteBuff(sig, stream, pImageDescriptor, 9)) return false;
	if (pImageDescriptor->LocalColorTableFlag()) {
		if (!WriteColorTable(sig, stream, pPalette)) return false;
	}
	UInt8 transparentColorIndex = graphicControl.TransparentColorIndex;
	bool transparentColorFlag = (pImage->GetFormat() == Image::FORMAT_RGBA) &&
					(graphicControl.TransparentColorFlag() != 0);
	const int maximumBitsOfCode = 12;
	UInt8 minimumBitsOfCode = 8;
	if (!WriteBuff(sig, stream, &minimumBitsOfCode, 1)) return false;
	Binary word;
	int bitsOfCode = minimumBitsOfCode + 1;
	UInt16 code = 0x0000;
	UInt16 codeBoundary = 1 << minimumBitsOfCode;
	UInt16 codeClear = codeBoundary;
	UInt16 codeEnd = codeBoundary + 1;
	UInt16 codeMax = codeBoundary + 2;
	UInt16 codeMaxCeiling = 1 << maximumBitsOfCode;
	TransMap transMap;
	ImageDataBlock imageDataBlock;
	if (!imageDataBlock.WriteCode(sig, stream, codeClear, bitsOfCode)) return false;
	for (size_t y = 0; y < pImage->GetHeight(); y++) {
		const UInt8* pPixel = pImage->GetPointer(y);
		for (size_t x = 0; x < pImage->GetWidth();
							x++, pPixel += pImage->GetBytesPerPixel()) {
			// LZW (Lempel-Ziv-Welch) compression algorithm
			UInt8 k;
			if (transparentColorFlag && Image::GetPixelA(pPixel) < 128) {
				k = transparentColorIndex;
			} else {
				k = static_cast<UInt8>(pPalette->LookupNearest(pPixel));
			}
			//::printf("- %3d,%3d code = %03x\n", x, y, k);
			if (word.empty()) {
				word += k;
				code = k;
				continue;
			}
			Binary wordK = word + static_cast<char>(k);
			TransMap::iterator iter = transMap.find(wordK);
			if (iter != transMap.end()) {
				word = wordK;
				code = iter->second;
				continue;
			}
			if (!imageDataBlock.WriteCode(sig, stream, code, bitsOfCode)) return false;
			transMap[wordK] = codeMax;
			if (codeMax < (1 << bitsOfCode)) {
				codeMax++;
			} else if ((1 << bitsOfCode) < codeMaxCeiling) {
				codeMax++;
				bitsOfCode++;
			} else {
				if (!imageDataBlock.WriteCode(sig, stream,
										codeClear, bitsOfCode)) return false;
				//::printf("clear\n");
				transMap.clear();
				codeMax = codeBoundary + 2;
				bitsOfCode = minimumBitsOfCode + 1;
			}
			word.clear();
			word += k;
			code = k;
		}
	}
	if (!imageDataBlock.WriteCode(sig, stream, code, bitsOfCode)) return false;
	if (!imageDataBlock.WriteCode(sig, stream, codeEnd, bitsOfCode)) return false;
	if (!imageDataBlock.Flush(sig, stream)) return false;
#endif
	return true;
}

bool Content::ReadBuff(Stream& stream, void* buff, size_t bytes)
{
	size_t bytesRead = stream.Read(buff, bytes);
	if (Error::IsIssued()) return false;
	if (bytesRead < bytes) {
		Error::Issue(ErrorType::FormatError, "invalid GIF format");
		return false;
	}
	return true;
}

bool Content::WriteBuff(Stream& stream, const void* buff, size_t bytes)
{
	return stream.Write(buff, bytes);
}

bool Content::ReadColorTable(Stream& stream, Palette& palette)
{
	UInt8 buff[3];
	size_t nEntries = palette.GetSize();
	for (size_t idx = 0; idx < nEntries; idx++) {
		if (!Content::ReadBuff(stream, buff, 3)) return false;
		palette.SetRGB(idx, buff[0], buff[1], buff[2]);
	}
	return true;
}

bool Content::WriteColorTable(Stream& stream, const Palette& palette)
{
#if 0
	UInt8 buff[3];
	int nEntries = static_cast<int>(pPalette->CountEntries());
	int idx = 0;
	for ( ; idx < nEntries; idx++) {
		const UInt8 *pEntry = pPalette->GetEntry(idx);
		buff[0] = *(pEntry + Image::OffsetR);
		buff[1] = *(pEntry + Image::OffsetG);
		buff[2] = *(pEntry + Image::OffsetB);
		if (!Content::WriteBuff(sig, stream, buff, 3)) return false;
	}
	int nBits = 0;
	for ( ; nEntries > (1 << nBits); nBits++) ;
	::memset(buff, 0x00, 3);
	for ( ; idx < (1 << nBits); idx++) {
		if (!Content::WriteBuff(sig, stream, buff, 3)) return false;
	}
#endif
	return true;
}

void Content::AddImage(const Value& value, UInt16 delayTime,
		UInt16 imageLeftPosition, UInt16 imageTopPosition,
		UInt8 disposalMethod)
{
#if 0
	Object_image* pObjImage = Object_image::GetObject(value);
	Image* pImage = pObjImage->GetImage();
	AutoPtr<Object_GraphicControl> pObjGraphicControl;
	AutoPtr<Object_ImageDescriptor> pObjImageDescriptor;
	do {
		Content::GraphicControlExtension graphicControl;
		Content::GraphicControlExtension graphicControlOrg;
		Content::GraphicControlExtension* pGraphicControl = GetGraphicControl(pObjImage);
		if (pGraphicControl != nullptr) {
			graphicControlOrg = *pGraphicControl;
		}
		graphicControl.PackedFields =
			(disposalMethod << 2) |
			(graphicControlOrg.UserInputFlag() << 1) |
			(graphicControlOrg.TransparentColorFlag() << 0);
		Gura_PackUInt16(graphicControl.DelayTime, delayTime);
		graphicControl.TransparentColorIndex = graphicControlOrg.TransparentColorIndex;
		pObjGraphicControl.reset(new Object_GraphicControl(graphicControl));
	} while (0);
	do {
		Content::ImageDescriptor imageDescriptor;
		Content::ImageDescriptor imageDescriptorOrg;
		Content::ImageDescriptor* pImageDescriptor = GetImageDescriptor(pObjImage);
		if (pImageDescriptor != nullptr) {
			imageDescriptorOrg = *pImageDescriptor;
		}
		Gura_PackUInt16(imageDescriptor.ImageLeftPosition, imageLeftPosition);
		Gura_PackUInt16(imageDescriptor.ImageTopPosition, imageTopPosition);
		Gura_PackUInt16(imageDescriptor.ImageWidth,
					static_cast<UInt16>(pImage->GetWidth()));
		Gura_PackUInt16(imageDescriptor.ImageHeight,
					static_cast<UInt16>(pImage->GetHeight()));
		imageDescriptor.PackedFields =
			(imageDescriptorOrg.LocalColorTableFlag() << 7) |
			(imageDescriptorOrg.InterlaceFlag() << 6) |
			(imageDescriptorOrg.SortFlag() << 5) |
			(imageDescriptorOrg.SizeOfLocalColorTable() << 0);
		pObjImageDescriptor.reset(new Object_ImageDescriptor(imageDescriptor));
	} while (0);
	pObjImage->AssignValue(Gura_UserSymbol(gif), Value(new Object_imgprop(
		pObjGraphicControl.release(), pObjImageDescriptor.release())), EXTRA_Public);
	GetList().push_back(value);
#endif
}

void Content::Dump(UInt8* data, int bytes)
{
	for (int i = 0; i < bytes; i++) {
		int iCol = i % 16;
		::printf((iCol == 0)? "%02x" : (iCol == 15)? " %02x\n" : " %02x", data[i]);
	}
	if (bytes % 16 != 0) ::printf("\n");
}

const Symbol* Content::DisposalMethodToSymbol(UInt8 disposalMethod)
{
#if 0
	if (disposalMethod == 0) {
		return Gura_UserSymbol(none);
	} else if (disposalMethod == 1) {
		return Gura_UserSymbol(keep);
	} else if (disposalMethod == 2) {
		return Gura_UserSymbol(background);
	} else if (disposalMethod == 3) {
		return Gura_UserSymbol(previous);
	} else {
		return Gura_UserSymbol(none);
	}
#endif
	return nullptr;
}

UInt8 Content::DisposalMethodFromSymbol(const Symbol* pSymbol)
{
#if 0
	UInt8 disposalMethod;
	if (pSymbol->IsIdentical(Gura_UserSymbol(none))) {
		disposalMethod = 0;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(keep))) {
		disposalMethod = 1;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(background))) {
		disposalMethod = 2;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(previous))) {
		disposalMethod = 3;
	} else {
		sig.SetError(ERR_ValueError, "invalid symbol for disposal method: %s",
															pSymbol->GetName());
		return 0;
	}
	return disposalMethod;
#endif
	return 0;
}

Content::GraphicControlExtension* Content::GetGraphicControl(const Image& image)
{
#if 0
	const Value* pValue = pObjImage->LookupValue(Gura_UserSymbol(gif), ENVREF_NoEscalate);
	if (pValue == nullptr || !pValue->IsType(VTYPE_imgprop)) return nullptr;
	return Object_imgprop::GetObject(*pValue)->GetGraphicControl();
#endif
	return nullptr;
}

Content::ImageDescriptor* Content::GetImageDescriptor(const Image& image)
{
#if 0
	const Value* pValue = pObjImage->LookupValue(Gura_UserSymbol(gif), ENVREF_NoEscalate);
	if (pValue == nullptr || !pValue->IsType(VTYPE_imgprop)) return nullptr;
	return Object_imgprop::GetObject(*pValue)->GetImageDescriptor();
#endif
	return nullptr;
}

int Content::GetPlausibleBackgroundIndex(Palette* pPalette, Image* pImage)
{
#if 0
	int histTbl[256];
	::memset(histTbl, 0x00, sizeof(histTbl));
	std::unique_ptr<Image::Scanner> pScanner(pImage->CreateScanner());
	size_t iPixelEnd = pScanner->CountPixels() - 1;
	size_t iLineEnd = pScanner->CountLines() - 1;
	for (;;) {
		int idx = static_cast<int>(pPalette->LookupNearest(pScanner->GetPointer()));
		histTbl[idx]++;
		if (pScanner->GetPixelIdx() >= iPixelEnd) break;
		pScanner->FwdPixel();
	}
	for (;;) {
		int idx = static_cast<int>(pPalette->LookupNearest(pScanner->GetPointer()));
		histTbl[idx]++;
		if (pScanner->GetLineIdx() >= iLineEnd) break;
		pScanner->FwdLine();
	}
	for (;;) {
		int idx = static_cast<int>(pPalette->LookupNearest(pScanner->GetPointer()));
		histTbl[idx]++;
		if (pScanner->GetPixelIdx() == 0) break;
		pScanner->BwdPixel();
	}
	for (;;) {
		int idx = static_cast<int>(pPalette->LookupNearest(pScanner->GetPointer()));
		histTbl[idx]++;
		if (pScanner->GetLineIdx() == 0) break;
		pScanner->BwdLine();
	}
	int idxMax = 0;
	int histMax = histTbl[0];
	for (int idx = 1; idx < ArraySizeOf(histTbl); idx++) {
		if (histMax < histTbl[idx]) {
			idxMax = idx;
			histMax = histTbl[idx];
		}
	}
	return idxMax;
#endif
	return 0;
}

//-----------------------------------------------------------------------------
// Content::ImageDataBlock
//-----------------------------------------------------------------------------
Content::ImageDataBlock::ImageDataBlock() : _bitOffset(0), _bitsRead(0)
{
	::memset(_blockData, 0x00, 256);
}

bool Content::ImageDataBlock::ReadCode(Stream& stream,
										UInt16& code, int bitsOfCode)
{
#if 0
	for (int bitsAccum = 0; bitsAccum < bitsOfCode; ) {
		int bitsRest = bitsOfCode - bitsAccum;
		if (_bitOffset >= _bitsRead) {
			UInt8 blockSize;
			if (!ReadBuff(sig, stream, &blockSize, 1)) return false;
			if (blockSize == 0) return false;
			if (!ReadBuff(sig, stream, _blockData, blockSize)) return false;
			_bitsRead = blockSize * 8;
			_bitOffset = 0;
		}
		UInt16 ch = static_cast<UInt16>(_blockData[_bitOffset >> 3]);
		int bitsRight = _bitOffset & 7;
		int bitsLeft = 8 - bitsRight;
		if (bitsRest < bitsLeft) {
			code |= ((ch >> bitsRight) & ((1 << bitsRest) - 1)) << bitsAccum;
			_bitOffset += bitsRest;
			break;
		} else {
			code |= (ch >> bitsRight) << bitsAccum;
			bitsAccum += bitsLeft;
			_bitOffset += bitsLeft;
		}
	}
#endif
	return true;
}

bool Content::ImageDataBlock::WriteCode(Stream& stream,
										UInt16 code, int bitsOfCode)
{
#if 0
	const int bitsFull = 8 * 255;
	for (int bitsAccum = 0; bitsAccum < bitsOfCode; ) {
		int bitsRest = bitsOfCode - bitsAccum;
		if (_bitOffset >= bitsFull) {
			UInt8 blockSize = 255;
			if (!Content::WriteBuff(sig, stream, &blockSize, 1)) return false;
			if (!Content::WriteBuff(sig, stream, _blockData, blockSize)) return false;
			::memset(_blockData, 0x00, 256);
			_bitOffset -= bitsFull;
		}
		int bitsRight = _bitOffset & 7;
		int bitsLeft = 8 - bitsRight;
		_blockData[_bitOffset >> 3] |= static_cast<UInt8>(code << bitsRight);
		if (bitsRest < bitsLeft) {
			_bitOffset += bitsRest;
			break;
		} else {
			code >>= bitsLeft;
			bitsAccum += bitsLeft;
			_bitOffset += bitsLeft;
		}
	}
#endif
	return true;
}

bool Content::ImageDataBlock::Flush(Stream& stream)
{
#if 0
	if (_bitOffset > 0) {
		UInt8 blockSize = static_cast<UInt8>((_bitOffset + 7) / 8);
		if (!Content::WriteBuff(sig, stream, &blockSize, 1)) return false;
		if (!Content::WriteBuff(sig, stream, _blockData, blockSize)) return false;
	}
	do {
		UInt8 blockSize = 0x00;
		if (!WriteBuff(sig, stream, &blockSize, 1)) return false;
	} while (0);
#endif
	return true;
}

String Content::ToString(const StringStyle& ss) const
{
	return String().Format("gif.Content");
}

Gurax_EndModuleScope(gif)
