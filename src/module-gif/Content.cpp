//==============================================================================
// Content.cpp
// Specification: spec-gif89a.txt
// <GIF Data Stream> ::=     Header <Logical Screen> <Data>* Trailer
// <Logical Screen> ::=      Logical Screen Descriptor [Global Color Table]
// <Data> ::=                <Graphic Block>  |
//                           <Special-Purpose Block>
// <Graphic Block> ::=       [Graphic Control Extension] <Graphic-Rendering Block>
// <Graphic-Rendering Block> ::=  <Table-Based Image>  |
//                                Plain Text Extension
// <Table-Based Image> ::=   Image Descriptor [Local Color Table] Image Data
// <Special-Purpose Block> ::=    Application Extension  |
//                                Comment Extension
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// Content
//------------------------------------------------------------------------------
Content::Extensions Content::extensionsDefault;

bool Content::Read(Stream& stream, Image::Format format)
{
	if (!ReadBuff(stream, &_header, 6)) return false;
	if (::memcmp(_header.Signature, "GIF", 3) != 0) {
		Error::Issue(ErrorType::FormatError, "Not a GIF file");
		return false;
	}
	if (::memcmp(_header.Version, "87a", 3) != 0 && ::memcmp(_header.Version, "89a", 3) != 0) {
		Error::Issue(ErrorType::FormatError, "unsupported version of Content file");
		return false;
	}
	if (!ReadBuff(stream, &_logicalScreenDescriptor, 7)) return false;
	//_logicalScreenDescriptor.Print();
	if (_logicalScreenDescriptor.GetGlobalColorTableFlag()) {
		int nEntries = 1 << (_logicalScreenDescriptor.GetSizeOfGlobalColorTable() + 1);
		_pPaletteGlobal.reset(new Palette(nEntries));
		if (!ReadColorTable(stream, *_pPaletteGlobal)) return false;
	}
	_entries.Clear();
	GraphicControlExtension graphicControlExtension;
	for (;;) {
		UInt8 imageSeparator;
		size_t bytesRead = stream.Read(&imageSeparator, 1);
		if (bytesRead < 1) break;
		if (imageSeparator == Sep::ImageDescriptor) {
			//::printf("ImageDescriptor\n");
			if (format.IsIdentical(Image::Format::None)) {
				if (!SkipImageDescriptor(stream)) break;
			} else {
				RefPtr<Image> pImage(new Image(format));
				RefPtr<GraphicBlock> pGraphicBlock(new GraphicBlock(graphicControlExtension));
				if (!ReadImageDescriptor(stream, *pImage, *pGraphicBlock)) break;
				_entries.push_back(new Entry(pGraphicBlock.release(), pImage.release()));
			}
		} else if (imageSeparator == Sep::ExtensionIntroducer) {
			UInt8 label;
			if (!ReadBuff(stream, &label, 1)) break;
			//::printf("ExtensionIntroducer - Label:%02x\n", label);
			if (label == GraphicControlExtension::Label) {
				if (!ReadBuff(stream, &graphicControlExtension, 5)) break;
				UInt8 blockTerminator;
				if (!ReadBuff(stream, &blockTerminator, 1)) break;
			} else if (label == CommentExtension::Label) {
				_extensions.commentExtension.validFlag = true;
				if (!ReadDataBlocks(stream, _extensions.commentExtension.CommentData)) break;
			} else if (label == PlainTextExtension::Label) {
				_extensions.plainTextExtension.validFlag = true;
				if (!ReadBuff(stream, &_extensions.plainTextExtension, 13)) break;
				if (!ReadDataBlocks(stream, _extensions.plainTextExtension.PlainTextData)) break;
			} else if (label == ApplicationExtension::Label) {
				ApplicationExtension applicationExtension;
				if (!ReadBuff(stream, &applicationExtension, 12)) break;
				Binary data;
				if (!ReadDataBlocks(stream, data)) break;
				if (::memcmp(applicationExtension.ApplicationIdentifier, "NETSCAPE", 8) == 0 &&
					::memcmp(applicationExtension.AuthenticationCode, "2.0", 3) == 0 &&
					data.size() == 3 && data[0] == 1) {
					_loopCount = (static_cast<UInt16>(data[2]) << 8) + data[1];
				}
			}
			if (Error::IsIssued()) break;
		} else if (imageSeparator == Sep::Trailer) {
			//::printf("Trailer\n");
			break;
		} else {
			Error::Issue(ErrorType::FormatError, "unknown separator %02x", imageSeparator);
			break;
		}
	}
	return !Error::IsIssued();
}

bool Content::Write(Stream& stream, const Color& colorBackground, bool validBackgroundFlag)
{
	if (_entries.empty()) {
		Error::Issue(ErrorType::ValueError, "no image to write");
		return false;
	}
	_pPaletteGlobal.reset(new Palette(256));
	size_t logicalScreenWidth = 0, logicalScreenHeight = 0;
	bool successFlag = true;
	for (Entry* pEntry : _entries) {
		Image& image = pEntry->GetImage();
		const Palette* pPalette = image.GetPalette();
		if (pPalette && pPalette->GetSize() <= 256) {
			if (!_pPaletteGlobal->UpdateByPalette(*pPalette, Palette::ShrinkMode::None)) {
				successFlag = false;
				break;
			}
		} else {
			if (!_pPaletteGlobal->UpdateByImage(image, Palette::ShrinkMode::None)) {
				successFlag = false;
				break;
			}
		}
	}
	if (!successFlag) _pPaletteGlobal.reset(Palette::WebSafe());
	int backgroundColorIndex = -1;
	UInt8 transparentColorIndex = 0;
	UInt8 transparentColorFlag = 0;
	Palette::ColorSet colorSet;
	do {
		size_t idxBlank = _pPaletteGlobal->NextBlankIndex(colorSet);
		if (idxBlank < _pPaletteGlobal->GetSize()) {
			// add an entry for transparent color
			_pPaletteGlobal->SetRGBA(idxBlank, 128, 128, 128, 0);
			transparentColorIndex = static_cast<UInt8>(idxBlank);
			transparentColorFlag = 1;
			idxBlank++;
		}
		_pPaletteGlobal->Shrink(idxBlank, true);
	} while (0);
	if (validBackgroundFlag) {
		backgroundColorIndex = static_cast<int>(_pPaletteGlobal->LookupNearest(colorBackground));
	}
	for (Entry* pEntry : _entries) {
		Image& image = pEntry->GetImage();
		image.SetPalette(Palette::Reference(_pPaletteGlobal.get()));
		ImageDescriptor& imageDescriptor = pEntry->GetGraphicBlock().GetImageDescriptor();
		GraphicControlExtension& graphicControlExtension = pEntry->GetGraphicBlock().GetGraphicControl();
		size_t width = image.GetWidth() + Gurax_UnpackUInt16(imageDescriptor.ImageLeftPosition);
		size_t height = image.GetHeight() + Gurax_UnpackUInt16(imageDescriptor.ImageTopPosition);
		if (logicalScreenWidth < width) logicalScreenWidth = width;
		if (logicalScreenHeight < height) logicalScreenHeight = height;
		graphicControlExtension.TransparentColorIndex = transparentColorIndex;
		graphicControlExtension.PackedFields |= transparentColorFlag;
		if (backgroundColorIndex < 0) {
			backgroundColorIndex = GetPlausibleBackgroundIndex(*_pPaletteGlobal, image);
		}
	}
	if (backgroundColorIndex < 0) backgroundColorIndex = 0;
	do {
		UInt8 globalColorTableFlag = 1;
		UInt8 colorResolution = 7;
		UInt8 sortFlag = 0;
		UInt8 sizeOfGlobalColorTable = 0;
		int nEntries = static_cast<int>(_pPaletteGlobal->GetSize());
		for ( ; nEntries > (1 << sizeOfGlobalColorTable); sizeOfGlobalColorTable++) ;
		sizeOfGlobalColorTable--;
		Gurax_PackUInt16(_logicalScreenDescriptor.LogicalScreenWidth, static_cast<UInt16>(logicalScreenWidth));
		Gurax_PackUInt16(_logicalScreenDescriptor.LogicalScreenHeight, static_cast<UInt16>(logicalScreenHeight));
		_logicalScreenDescriptor.PackedFields =
			(globalColorTableFlag << 7) | (colorResolution << 4) |
			(sortFlag << 3) | (sizeOfGlobalColorTable << 0);
		_logicalScreenDescriptor.BackgroundColorIndex = static_cast<UInt8>(backgroundColorIndex);
		_logicalScreenDescriptor.PixelAspectRatio = 0;
	} while (0);
	// Header
	if (!WriteBuff(stream, &_header, 6)) return false;
	// Logical Screen Descriptor
	if (!WriteBuff(stream, &_logicalScreenDescriptor, 7)) return false;
	// Global Color Table
	if (_logicalScreenDescriptor.GetGlobalColorTableFlag()) {
		if (!WriteColorTable(stream, *_pPaletteGlobal)) return false;
	}
	if (_loopCount >= 0) {
		// Application Extension
		UInt8 buff[2];
		buff[0] = Sep::ExtensionIntroducer;
		buff[1] = ApplicationExtension::Label;
		if (!WriteBuff(stream, buff, 2)) return false;
		ApplicationExtension applicationExtension;
		if (!WriteBuff(stream, &applicationExtension, 12)) return false;
		ApplicationExtension::Data data;
		UInt16 num = static_cast<UInt16>(_loopCount);
		Gurax_PackUInt16(data.LoopCount, num);
		if (!WriteBuff(stream, &data, 4)) return false;
		UInt8 blockSize = 0x00;
		if (!WriteBuff(stream, &blockSize, 1)) return false;
	}
	for (Entry* pEntry : _entries) {
		Image& image = pEntry->GetImage();
		GraphicControlExtension& graphicControlExtension = pEntry->GetGraphicBlock().GetGraphicControl();
		if (!WriteGraphicControl(stream, graphicControlExtension)) return false;
		if (!WriteImageDescriptor(stream, *pEntry)) return false;
	}
	// Trailer
	if (!WriteBuff(stream, &Sep::Trailer, 1)) return false;
	return false;
}

bool Content::ReadDataBlocks(Stream& stream, Binary& binary)
{
	for (;;) {
		UInt8 blockSize;
		if (!ReadBuff(stream, &blockSize, 1)) return false;
		if (blockSize == 0) break;
		char buff[256];
		if (!ReadBuff(stream, buff, blockSize)) return false;
		binary.Append(buff, blockSize);
	}
	return true;
}

bool Content::WriteDataBlocks(Stream& stream, const UInt8* buff, size_t bytes)
{
	for (size_t offset = 0; offset < bytes; ) {
		UInt8 blockSize = static_cast<UInt8>((bytes - offset <= 255)? bytes - offset : 255);
		if (!WriteBuff(stream, &blockSize, 1)) return false;
		if (!WriteBuff(stream, buff + offset, blockSize)) return false;
		offset += blockSize;
	}
	do {
		UInt8 blockSize = 0x00;
		if (!WriteBuff(stream, &blockSize, 1)) return false;
	} while (0);
	return true;
}

bool Content::SkipImageDescriptor(Stream& stream)
{
	ImageDescriptor imageDescriptor;
	if (!ReadBuff(stream, &imageDescriptor, 9)) return false;
	if (imageDescriptor.GetLocalColorTableFlag()) {
		int nEntries = 1 << (imageDescriptor.GetSizeOfLocalColorTable() + 1);
		stream.Seek(nEntries * 3, Stream::SeekMode::Cur);
	}
	UInt8 mininumBitsOfCode;
	if (!ReadBuff(stream, &mininumBitsOfCode, 1)) return false;
	for (;;) {
		UInt8 blockSize;
		if (!ReadBuff(stream, &blockSize, 1)) return false;
		if (blockSize == 0) break;
		if (!stream.Seek(blockSize, Stream::SeekMode::Cur)) return false;
	}
	return true;
}

bool Content::ReadImageDescriptor(Stream& stream, Image& image, GraphicBlock& GraphicBlock)
{
	GraphicControlExtension& graphicControlExtension = GraphicBlock.GetGraphicControl();
	ImageDescriptor& imageDescriptor = GraphicBlock.GetImageDescriptor();
	if (!ReadBuff(stream, &imageDescriptor, 9)) return false;
	//imageDescriptor.Print();
	size_t imageWidth = Gurax_UnpackUInt16(imageDescriptor.ImageWidth);
	size_t imageHeight = Gurax_UnpackUInt16(imageDescriptor.ImageHeight);
	if (!image.Allocate(imageWidth, imageHeight)) return false;
	image.Fill(0xff);
	RefPtr<Palette> pPalette;
	if (imageDescriptor.GetLocalColorTableFlag()) {
		int nEntries = 1 << (static_cast<int>(imageDescriptor.GetSizeOfLocalColorTable()) + 1);
		pPalette.reset(new Palette(nEntries));
		if (!ReadColorTable(stream, *pPalette)) return false;
	} else {
		pPalette.reset(_pPaletteGlobal.Reference());
	}
	image.SetPalette(pPalette.Reference());
	image.SetValueExtra(new Value_GraphicBlock(GraphicBlock.Reference()));
	short transparentColorIndex = graphicControlExtension.TransparentColorIndex;
	if (!graphicControlExtension.GetTransparentColorFlag() || !image.IsFormat(Image::Format::RGBA)) {
		transparentColorIndex = -1;
	}
	const int maximumBitsOfCode = 12;
	UInt8 mininumBitsOfCode;
	if (!ReadBuff(stream, &mininumBitsOfCode, 1)) return false;
	int bitsOfCode = mininumBitsOfCode + 1;
	if (bitsOfCode > maximumBitsOfCode) {
		Error::Issue(ErrorType::FormatError, "illegal code size");
		return false;
	}
	bool interlaceFlag = (imageDescriptor.GetInterlaceFlag() != 0);
	const UInt16 codeInvalid = 0xffff;
	UInt16 codeMaxCeiling = 1 << maximumBitsOfCode;
	UInt16 codeBoundary = 1 << mininumBitsOfCode;
	UInt16 codeClear = codeBoundary;
	UInt16 codeEnd = codeBoundary + 1;
	UInt16 codeMax = codeBoundary + 2;
	UInt16 codeFirst = codeInvalid, codeOld = codeInvalid;
	const size_t bytesCodeTable = codeMaxCeiling * 2;
	const size_t bytesCodeStack = codeMaxCeiling * 2;
	std::unique_ptr<UInt16[]> codeTable(new UInt16 [bytesCodeTable]);
	std::unique_ptr<UInt16[]> codeStack(new UInt16 [bytesCodeStack]);
	UInt16* pCodeStack = codeStack.get();
	do {
		::memset(codeTable.get(), 0x00, bytesCodeTable);
		for (UInt16 code = 0; code < codeBoundary; code++) {
			codeTable[code * 2 + 1] = code;
		}
	} while (0);
	ImageDataBlock imageDataBlock;
	size_t x = 0, y = 0;
	int iPass = 0;
	UInt8* dstp = image.GetPointerC();
	for (;;) {
		UInt16 code = 0;
		if (pCodeStack > codeStack.get()) {
			pCodeStack--;
			code =* pCodeStack;
		} else {
			if (!imageDataBlock.ReadCode(stream, code, bitsOfCode)) break;
			// LZW (Lempel-Ziv-Welch) decompression algorithm
			if (code == codeClear) {
				//::printf("clear\n");
				UInt16 code = 0;
				::memset(codeTable.get(), 0x00, bytesCodeTable);
				for (UInt16 code = 0; code < codeBoundary; code++) {
					codeTable[code * 2 + 1] = code;
				}
				pCodeStack = codeStack.get();
				bitsOfCode = mininumBitsOfCode + 1;
				codeMax = codeBoundary + 2;
				codeFirst = codeOld = codeInvalid;
				continue;
			} else if (code == codeEnd) {
				// skip trailing blocks
				for (;;) {
					UInt8 blockSize;
					if (!ReadBuff(stream, &blockSize, 1)) break;
					if (blockSize == 0) break;
					if (!stream.Seek(blockSize, Stream::SeekMode::Cur)) break;
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
						Error::Issue(ErrorType::FormatError, "invalid GIF format");
						return false;
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
				if (pCodeStack > codeStack.get()) {
					pCodeStack--;
					code = *pCodeStack;
				}
			}
		}
		const Color& src = pPalette->GetColor(code);
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
			dstp = image.GetPointerC(0, y);
		}
		//::printf("+ %3zd,%3zd code = %03x\n", x, y, code);
		*(dstp + 0) = src.GetB();
		*(dstp + 1) = src.GetG();
		*(dstp + 2) = src.GetR();
		if (code == transparentColorIndex) *(dstp + 3) = 0x00;
		dstp += image.GetBytesPerPixel();
		x++;
	}
	return !Error::IsIssued();
}

bool Content::WriteGraphicControl(Stream& stream, const GraphicControlExtension& graphicControlExtension)
{
	const UInt8 buff[] = {
		Sep::ExtensionIntroducer, GraphicControlExtension::Label
	};
	UInt8 blockTerminator = 0x00;
	if (!WriteBuff(stream, buff, 2)) return false;
	if (!WriteBuff(stream, &graphicControlExtension, 5)) return false;
	if (!WriteBuff(stream, &blockTerminator, 1)) return false;
	return true;
}

bool Content::WriteImageDescriptor(Stream& stream, Entry& entry)
{
	const Image& image = entry.GetImage();
	const ImageDescriptor& imageDescriptor = entry.GetGraphicBlock().GetImageDescriptor();
	const GraphicControlExtension& graphicControlExtension = entry.GetGraphicBlock().GetGraphicControl();
	if (!WriteBuff(stream, &Sep::ImageDescriptor, 1)) return false;
	const Palette* pPalette = _pPaletteGlobal.get();
	if (!WriteBuff(stream, &imageDescriptor, 9)) return false;
	if (imageDescriptor.GetLocalColorTableFlag()) {
		if (!WriteColorTable(stream, *pPalette)) return false;
	}
	UInt8 transparentColorIndex = graphicControlExtension.TransparentColorIndex;
	bool transparentColorFlag = (image.IsFormat(Image::Format::RGBA)) && (graphicControlExtension.GetTransparentColorFlag() != 0);
	const int maximumBitsOfCode = 12;
	UInt8 minimumBitsOfCode = 8;
	if (!WriteBuff(stream, &minimumBitsOfCode, 1)) return false;
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
	if (!imageDataBlock.WriteCode(stream, codeClear, bitsOfCode)) return false;
	for (size_t y = 0; y < image.GetHeight(); y++) {
		const UInt8* pPixel = image.GetPointerC(0, y);
		for (size_t x = 0; x < image.GetWidth(); x++, pPixel += image.GetBytesPerPixel()) {
			//::printf("%02x%02x%02x\n", Image::PixelRGB::GetR(pPixel),
			//			Image::PixelRGB::GetG(pPixel), Image::PixelRGB::GetB(pPixel));
			// LZW (Lempel-Ziv-Welch) compression algorithm
			UInt8 k;
			if (transparentColorFlag && Image::PixelRGBA::GetA(pPixel) < 128) {
				k = transparentColorIndex;
			} else {
				k = static_cast<UInt8>(pPalette->LookupNearest(
					Image::PixelRGBA::GetR(pPixel), Image::PixelRGBA::GetG(pPixel), Image::PixelRGBA::GetB(pPixel)));
			}
			//::printf("- %3zd,%3zd code = 0x%02x\n", x, y, k);
			if (word.empty()) {
				word += k;
				code = k;
				continue;
			}
			Binary wordK = word;
			wordK += k;
			TransMap::iterator iter = transMap.find(wordK);
			if (iter != transMap.end()) {
				word = wordK;
				code = iter->second;
				continue;
			}
			if (!imageDataBlock.WriteCode(stream, code, bitsOfCode)) return false;
			transMap[wordK] = codeMax;
			if (codeMax < (1 << bitsOfCode)) {
				codeMax++;
			} else if ((1 << bitsOfCode) < codeMaxCeiling) {
				codeMax++;
				bitsOfCode++;
			} else {
				if (!imageDataBlock.WriteCode(stream, codeClear, bitsOfCode)) return false;
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
	if (!imageDataBlock.WriteCode(stream, code, bitsOfCode)) return false;
	if (!imageDataBlock.WriteCode(stream, codeEnd, bitsOfCode)) return false;
	if (!imageDataBlock.Flush(stream)) return false;
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
	UInt8 buff[3];
	int nEntries = static_cast<int>(palette.GetSize());
	int idx = 0;
	for ( ; idx < nEntries; idx++) {
		const Color& color = palette.GetColor(idx);
		buff[0] = color.GetR();
		buff[1] = color.GetG();
		buff[2] = color.GetB();
		if (!Content::WriteBuff(stream, buff, 3)) return false;
	}
	int nBits = 0;
	for ( ; nEntries > (1 << nBits); nBits++) ;
	::memset(buff, 0x00, 3);
	for ( ; idx < (1 << nBits); idx++) {
		if (!Content::WriteBuff(stream, buff, 3)) return false;
	}
	return true;
}

void Content::AddImage(const Image& image, UInt16 delayTime,
		UInt16 imageLeftPosition, UInt16 imageTopPosition, UInt8 disposalMethod)
{
	RefPtr<GraphicBlock> pGraphicBlock(new GraphicBlock());
	do {
		UInt8 userInputFlag = 0;
		UInt8 transparentColorFlag = 0;
		GraphicControlExtension& graphicControlExtension = pGraphicBlock->GetGraphicControl();
		graphicControlExtension.BlockSize = 4;
		graphicControlExtension.PackedFields = (disposalMethod << 2) | (userInputFlag << 1) | (transparentColorFlag << 0);
		Gurax_PackUInt16(graphicControlExtension.DelayTime, delayTime);
		graphicControlExtension.TransparentColorIndex = 0;
	} while (0);
	do {
		UInt8 localColorTableFlag = 0;
		UInt8 interlaceFlag = 0;
		UInt8 sortFlag = 0;
		UInt8 sizeOfLocalColorTable = 0;
		ImageDescriptor& imageDescriptor = pGraphicBlock->GetImageDescriptor();
		Gurax_PackUInt16(imageDescriptor.ImageLeftPosition, imageLeftPosition);
		Gurax_PackUInt16(imageDescriptor.ImageTopPosition, imageTopPosition);
		UInt16 imageWidth = static_cast<UInt16>(image.GetWidth());
		UInt16 imageHeight = static_cast<UInt16>(image.GetHeight());
		Gurax_PackUInt16(imageDescriptor.ImageWidth, imageWidth);
		Gurax_PackUInt16(imageDescriptor.ImageHeight, imageHeight);
		imageDescriptor.PackedFields = (localColorTableFlag << 7) | (interlaceFlag << 6) |
			(sortFlag << 5) | (sizeOfLocalColorTable << 0);
	} while (0);
	_entries.push_back(new Entry(pGraphicBlock.release(), image.Reference()));
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
	if (disposalMethod == DisposalMethod::Keep) {
		return Gurax_Symbol(keep);
	} else if (disposalMethod == DisposalMethod::Background) {
		return Gurax_Symbol(background);
	} else if (disposalMethod == DisposalMethod::Previous) {
		return Gurax_Symbol(previous);
	} else {
		return Gurax_Symbol(none);
	}
}

UInt8 Content::DisposalMethodFromSymbol(const Symbol* pSymbol)
{
	UInt8 disposalMethod = 0;
	if (pSymbol->IsIdentical(Gurax_Symbol(none))) {
		disposalMethod = DisposalMethod::None;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(keep))) {
		disposalMethod = DisposalMethod::Keep;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(background))) {
		disposalMethod = DisposalMethod::Background;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(previous))) {
		disposalMethod = DisposalMethod::Previous;
	} else {
		Error::Issue(ErrorType::ValueError,
			"invalid symbol for disposal method: %s", pSymbol->GetName());
		return 0;
	}
	return disposalMethod;
}

int Content::GetPlausibleBackgroundIndex(Palette& palette, Image& image)
{
	int histTbl[256];
	::memset(histTbl, 0x00, sizeof(histTbl));
	Image::Scanner scanner = Image::Scanner::CreateByDir(image, Image::ScanDir::LeftTopHorz);
	size_t iColEnd = scanner.GetColNum() - 1;
	size_t iRowEnd = scanner.GetRowNum() - 1;
	// *************************************************
	for (;;) {
		int idx = static_cast<int>(palette.LookupNearest(scanner.GetColor()));
		histTbl[idx]++;
		if (scanner.GetColIndex() >= iColEnd) break;
		scanner.PlusCol();
	}
	for (;;) {
		int idx = static_cast<int>(palette.LookupNearest(scanner.GetColor()));
		histTbl[idx]++;
		if (scanner.GetRowIndex() >= iRowEnd) break;
		scanner.PlusRow();
	}
	for (;;) {
		int idx = static_cast<int>(palette.LookupNearest(scanner.GetColor()));
		histTbl[idx]++;
		if (scanner.GetColIndex() == 0) break;
		scanner.MinusCol();
	}
	for (;;) {
		int idx = static_cast<int>(palette.LookupNearest(scanner.GetColor()));
		histTbl[idx]++;
		if (scanner.GetRowIndex() == 0) break;
		scanner.MinusRow();
	}
	int idxMax = 0;
	int histMax = histTbl[0];
	for (int idx = 1; idx < Gurax_ArraySizeOf(histTbl); idx++) {
		if (histMax < histTbl[idx]) {
			idxMax = idx;
			histMax = histTbl[idx];
		}
	}
	return idxMax;
}

String Content::ToString(const StringStyle& ss) const
{
	return String().Format("gif.Content");
}

//-----------------------------------------------------------------------------
// Content::ImageDataBlock
//-----------------------------------------------------------------------------
Content::ImageDataBlock::ImageDataBlock() : _bitOffset(0), _bitsRead(0)
{
	::memset(_blockData, 0x00, 256);
}

bool Content::ImageDataBlock::ReadCode(Stream& stream, UInt16& code, int bitsOfCode)
{
	for (int bitsAccum = 0; bitsAccum < bitsOfCode; ) {
		int bitsRest = bitsOfCode - bitsAccum;
		if (_bitOffset >= _bitsRead) {
			UInt8 blockSize;
			if (!ReadBuff(stream, &blockSize, 1)) return false;
			if (blockSize == 0) return false;
			if (!ReadBuff(stream, _blockData, blockSize)) return false;
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
	//::printf("ReadCode(0x%04x)\n", code);
	return true;
}

bool Content::ImageDataBlock::WriteCode(Stream& stream, UInt16 code, int bitsOfCode)
{
	//::printf("WriteCode(0x%04x)\n", code);
	const int bitsFull = 8 * 255;
	for (int bitsAccum = 0; bitsAccum < bitsOfCode; ) {
		int bitsRest = bitsOfCode - bitsAccum;
		if (_bitOffset >= bitsFull) {
			UInt8 blockSize = 255;
			if (!Content::WriteBuff(stream, &blockSize, 1)) return false;
			if (!Content::WriteBuff(stream, _blockData, blockSize)) return false;
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
	return true;
}

bool Content::ImageDataBlock::Flush(Stream& stream)
{
	if (_bitOffset > 0) {
		UInt8 blockSize = static_cast<UInt8>((_bitOffset + 7) / 8);
		if (!Content::WriteBuff(stream, &blockSize, 1)) return false;
		if (!Content::WriteBuff(stream, _blockData, blockSize)) return false;
	}
	do {
		UInt8 blockSize = 0x00;
		if (!WriteBuff(stream, &blockSize, 1)) return false;
	} while (0);
	return true;
}

//-----------------------------------------------------------------------------
// Content::EntryOwner
//-----------------------------------------------------------------------------
void Content::EntryOwner::Clear()
{
	for (Entry* pEntry : *this) Entry::Delete(pEntry);
	clear();
}

//------------------------------------------------------------------------------
// Content::Iterator_EachImage
//------------------------------------------------------------------------------
Value* Content::Iterator_EachImage::DoNextValue()
{
	EntryOwner& entries = _pContent->GetEntries();
	if (_idx >= entries.size()) return nullptr;
	Entry* pEntry = entries[_idx++];
	return new Value_Image(pEntry->GetImage().Reference());
}

String Content::Iterator_EachImage::ToString(const StringStyle& ss) const
{
	return String().Format("gif.EachImage");
}

Gurax_EndModuleScope(gif)
