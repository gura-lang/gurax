//==============================================================================
// ImageExtension.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// ImageMgrEx
//------------------------------------------------------------------------------
bool ImageMgrEx::IsResponsible(Stream& stream) const
{
	char buff[3];
	return stream.Read(buff, 3) == 3 && ::memcmp(buff, "GIF", 3) == 0;
}

bool ImageMgrEx::IsResponsibleExtName(const char* extName) const
{
	return ::strcasecmp(extName, ".gif") == 0;
}

bool ImageMgrEx::Read(Stream& stream, Image& image) const
{
	return ReadStream(stream, image);
}

bool ImageMgrEx::Write(Stream& stream, const Image& image) const
{
	return WriteStream(stream, image);
}

bool ImageMgrEx::ReadStream(Stream& stream, Image& image)
{
	RefPtr<Content> pContent(new Content());
	if (!pContent->Read(stream, image.GetFormat())) return false;
	Content::EntryOwner& entries = pContent->GetEntries();
	if (entries.empty()) {
		Error::Issue(ErrorType::FormatError, "no images found in GIF file");
		return false;
	}
	image.CopyRef(entries.front()->GetImage());
	return true;
}

bool ImageMgrEx::WriteStream(Stream& stream, const Image& image)
{
	RefPtr<Content> pContent(new Content());
	do {
		UInt16 imageLeftPosition = 0;
		UInt16 imageTopPosition = 0;
		UInt16 delayTime = 0;
		UInt8 disposalMethod = Content::DisposalMethod::None;
		pContent->AddImage(image, imageLeftPosition, imageTopPosition, delayTime, disposalMethod);
	} while (0);
	do {
		const Color& colorBackground = Color::zero;
		bool validBackgroundFlag = false;
		pContent->Write(stream, colorBackground, validBackgroundFlag);
	} while (0);
	return true;
}

Gurax_EndModuleScope(gif)
