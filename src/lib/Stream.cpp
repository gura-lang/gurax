//==============================================================================
// Stream.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream
//------------------------------------------------------------------------------
RefPtr<Stream> Stream::Dumb;
RefPtr<Stream> Stream::CIn;
RefPtr<Stream> Stream::COut;
RefPtr<Stream> Stream::CErr;

Stream::Stream(Flags flags, size_t offset) :
	_flags(flags), _offset(offset), _pCodec(CodecFactory::Dumb->CreateCodec(true, false))
{
}

void Stream::Bootup()
{
	Dumb.reset(new Stream_Dumb());
	CIn.reset(new Stream_Console(Stream::Flag::Readable, stdin, "CIn"));
	COut.reset(new Stream_Console(Stream::Flag::Writable, stdout, "COut"));
	CErr.reset(new Stream_Console(Stream::Flag::Writable, stderr, "CErr"));
}

Stream* Stream::Open(const char* pathName, OpenFlags openFlags)
{
	if (*pathName == '>') {
		pathName++;
		openFlags = (openFlags & ~OpenFlag::Read) | OpenFlag::Write;
		if (*pathName == '>') {
			pathName++;
			openFlags |= OpenFlag::Append;
		}
	}
	Directory::Type typeWouldBe = (openFlags & OpenFlag::Write)? Directory::Type::Item : Directory::Type::None;
	RefPtr<Directory> pDirectory(PathMgr::OpenDirectory(pathName, typeWouldBe));
	if (!pDirectory) return nullptr;
	return pDirectory->OpenStream(openFlags);
}

bool Stream::CheckReadable() const
{
	if (IsReadable()) return true;
	Error::Issue(ErrorType::StreamError, "the steram must be readable");
	return false;
}

bool Stream::CheckWritable() const
{
	if (IsWritable()) return true;
	Error::Issue(ErrorType::StreamError, "the steram must be writable");
	return false;
}

char Stream::GetChar()
{
	Codec::Decoder& decoder = GetCodec().GetDecoder();
	char chConv = '\0';
	if (decoder.FollowChar(chConv)) return chConv;
	for (;;) {
		int chRaw = DoGetChar();
		if (chRaw < 0) return '\0';
		Codec::Result rtn = decoder.FeedChar(static_cast<UChar>(chRaw), chConv);
		if (rtn == Codec::Result::Error) {
			Error::Issue(ErrorType::CodecError, "not a valid character of %s", GetCodec().GetEncoding());
			return -1;
		}
		if (rtn == Codec::Result::Complete) break;
	}
	return chConv;
}

String Stream::ReadChar()
{
	String str;
	Codec::Decoder& decoder = GetCodec().GetDecoder();
	char chConv = '\0';
	for (;;) {
		int ch = DoGetChar();
		if (ch < 0) break;
		Codec::Result rtn = decoder.FeedChar(static_cast<UChar>(ch), chConv);
		if (rtn == Codec::Result::Error) {
			Error::Issue(ErrorType::CodecError, "not a valid character of %s", GetCodec().GetEncoding());
			return String::Empty;
		}
		if (rtn == Codec::Result::Complete) {
			str += chConv;
			break;
		}
	}
	while (decoder.FollowChar(chConv)) str += chConv;
	return str;
}

bool Stream::PutChar(char ch)
{
	char chConv = '\0';
	Codec::Encoder& encoder = GetCodec().GetEncoder();
	Codec::Result rtn = encoder.FeedChar(ch, chConv);
	if (rtn == Codec::Result::Error) return false;
	if (rtn == Codec::Result::Complete) {
		if (!DoPutChar(chConv)) return false;
		while (encoder.FollowChar(chConv)) {
			if (!DoPutChar(chConv)) return false;
		}
	}
	return true;
}

Stream& Stream::Print(const char* str)
{
	char chConv = '\0';
	Codec::Encoder& encoder = GetCodec().GetEncoder();
	for (const char* p = str; *p != '\0'; ++p) {
		char ch = *p;
		Codec::Result rtn = encoder.FeedChar(ch, chConv);
		if (rtn == Codec::Result::Error) return *this;
		if (rtn == Codec::Result::Complete) {
			if (!DoPutChar(chConv)) return *this;
			while (encoder.FollowChar(chConv)) {
				if (!DoPutChar(chConv)) return *this;
			}
		}
	}
	return *this;
}

Stream& Stream::Print(StringPicker&& strPicker)
{
	while (const char* str = strPicker.Pick()) Print(str);
	return *this;
}

Stream& Stream::Println(const char* str)
{
	Print(str);
	PutChar('\n');
	return *this;
}

Stream& Stream::Println(StringPicker&& strPicker)
{
	Print(std::move(strPicker));
	PutChar('\n');
	return *this;
}

Stream& Stream::PrintfV(const char* format, va_list ap)
{
	FormatterEx(*this).Format(format, ap);
	return *this;
}

Stream& Stream::Printf(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	return PrintfV(format, ap);
}

Stream& Stream::PrintFmt(const char* format, const ValueList& valueList)
{
	FormatterEx(*this).Format(format, valueList);
	return *this;
}

bool Stream::ReadLine(String& str, bool includeEOLFlag)
{
	char ch = GetChar();
	if (!ch) return false;
	for ( ; ch; ch = GetChar()) {
		if (ch == '\n') {
			if (includeEOLFlag) str += ch;
			break;
		}
		str += ch;
	}
	return true;
}

Iterator* Stream::ReadLines(bool includeEOLFlag)
{
	return new Iterator_ReadLines(Reference(), includeEOLFlag);
}

Binary Stream::Read(size_t len)
{
	Binary buff(len, '\0');
	size_t lenRead = Read(&buff[0], len);
	buff.resize(lenRead);
	return buff;
}

Stream& Stream::ReadAll(Binary& buff)
{
	const int bytesWork = 65536;
	RefPtr<Memory> pMemory(new MemoryHeap(bytesWork));
	UInt8* buffWork = pMemory->GetPointer<UInt8>();
	size_t bytesRead;
	while ((bytesRead = Read(buffWork, bytesWork)) > 0) {
		buff.append(buffWork, bytesRead);
	}
	return *this;
}

Binary Stream::ReadAll()
{
	Binary buff;
	ReadAll(buff);
	return buff;
}

Stream::OpenFlags Stream::ModeToOpenFlags(const char* mode)
{
	const char* p = mode;
	char chFirst = *p++;
	OpenFlags openFlags =
		(chFirst == 'r')? OpenFlag::Read :
		(chFirst == 'w')? OpenFlag::Write :
		(chFirst == 'a')? OpenFlag::Append : OpenFlag::None;
	if (openFlags == OpenFlag::None) {
		Error::Issue(ErrorType::ValueError, "invalid open mode");
		return OpenFlag::None;
	}
	char chSecond = *p++;
	if (chSecond == 'b') chSecond = *p++;
	if (chSecond == '\0') {
		// nothing to do
	} else if (chSecond == '+') {
		openFlags =
			(chFirst == 'r')? (OpenFlag::Read | OpenFlag::Write) :
			(chFirst == 'w')? (OpenFlag::Write | OpenFlag::Append) :
			(chFirst == 'a')? (OpenFlag::Append | OpenFlag::Read) : OpenFlag::None;
	} else {
		Error::Issue(ErrorType::ValueError, "invalid open mode");
		return OpenFlag::None;
	}
	return openFlags;
}

Stream* Stream::CreateBwdSeekable()
{
	if (IsBwdSeekable()) return Reference();
	RefPtr<BinaryReferable> pBuff(new BinaryReferable());
	ReadAll(pBuff->GetBinary());
	if (Error::IsIssued()) return nullptr;
	return new Stream_Binary(Stream::Flag::Readable, pBuff.release());
}

void Stream::Dump(const void* buff, size_t bytes, const StringStyle& ss)
{
	const int nCols = 16;
	int iCol = 0;
	char str[64];
	String strLine, strASCII;
	const UInt8* p = reinterpret_cast<const UInt8*>(buff);
	for (size_t i = 0; i < bytes; ++i, ++p) {
		UInt8 data = *p;
		if (iCol > 0) strLine += ' ';
		::sprintf(str, ss.IsUpperCase()? "%02X" : "%02x", data);
		strLine += str;
		strASCII += (0x20 <= data && data < 0x7f)? data : '.';
		iCol++;
		if (iCol == nCols) {
			strLine += "  ";
			strLine += strASCII;
			Println(strLine.c_str());
			if (Error::IsIssued()) return;
			strLine.clear();
			strASCII.clear();
			iCol = 0;
		}
	}
	if (iCol > 0) {
		for ( ; iCol < nCols; iCol++) strLine += "   ";
		strLine += "  ";
		strLine += strASCII;
		Println(strLine.c_str());
	}
}

bool Stream::Seek(long offsetRel, SeekMode seekMode)
{
	size_t offset;
	if (seekMode == SeekMode::Set) {
		offset = static_cast<size_t>(offsetRel);
	} else {
		offset = (seekMode == SeekMode::Cur)? _offset : DoGetBytes();
		if (offsetRel < 0 && offset < static_cast<size_t>(-offsetRel)) {
			Error::Issue(ErrorType::RangeError, "seeking point is out of range");
			return false;
		}
		offset += offsetRel;
	}
	if (!DoSeek(offset, _offset)) return false;
	_offset = offset;
	return true;
}

bool Stream::SetOffset(size_t offset)
{
	if (!DoSeek(offset, _offset)) return false;
	_offset = offset;
	return true;
}

bool Stream::ReadToStream(Stream& streamDst, size_t bytesUnit)
{
	if (!CheckReadable() || !streamDst.CheckWritable()) return false;
	RefPtr<Memory> pMemory(new MemoryHeap(bytesUnit));
	char* buff = pMemory->GetPointer<char>();
	for (;;) {
		size_t bytesRead = Read(buff, bytesUnit);
		if (bytesRead == 0) break;
		if (streamDst.Write(buff, bytesRead) < bytesRead) break;
	}
	return !Error::IsIssued();
}

bool Stream::DoSeek(size_t offset, size_t offsetPrev)
{
	Error::Issue(ErrorType::IOError, "seeking is not supported");
	return false;
}

int Stream::DoGetChar()
{
	UInt8 ch;
	return (DoRead(&ch, sizeof(ch)) > 0)? static_cast<int>(ch) : -1;
}

bool Stream::DoPutChar(char ch)
{
	return DoWrite(&ch, sizeof(ch)) > 0;
}

String Stream::ToString(const StringStyle& ss) const
{
	String str;
	str += GetName();
	if (GetFlags() & Flag::Readable) str += ":r";
	if (GetFlags() & Flag::Writable) str += ":w";
	str.Printf(":encoding=%s", GetCodec().GetEncoding());
	if (GetCodec().GetAddcrFlag()) str += ":addcr";
	if (GetCodec().GetDelcrFlag()) str += ":delcr";
	return str;
}

//------------------------------------------------------------------------------
// Stream::Attribute
//------------------------------------------------------------------------------
#if 0
Stream::Attribute::Attribute(const struct stat& sb) :
	_pDateTimeC(OAL::CreateDateTime(sb.st_ctime)),
	_pDateTimeM(OAL::CreateDateTime(sb.st_mtime)),
	_pDateTimeA(OAL::CreateDateTime(sb.st_atime)),
	_bytes(sb.st_size), _uid(sb.st_uid), _gid(sb.st_gid)
{
}
#endif

//------------------------------------------------------------------------------
// Iterator_ReadLines
//------------------------------------------------------------------------------
Iterator_ReadLines::Iterator_ReadLines(Stream* pStream, bool includeEOLFlag) :
	_pStream(pStream), _includeEOLFlag(includeEOLFlag), _doneFlag(false)
{
}

Value* Iterator_ReadLines::DoNextValue()
{
	if (_doneFlag) return nullptr;
	String str;
	if (!GetStream().ReadLine(str, _includeEOLFlag)) {
		_doneFlag = true;
		return nullptr;
	}
	return new Value_String(str);
}

String Iterator_ReadLines::ToString(const StringStyle& ss) const
{
	return "";
}

}
