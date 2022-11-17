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
	Stream(flags, Codec::CreateDumb(), offset)
{
}

Stream::Stream(Flags flags, Codec* pCodec, size_t offset) :
	_flags(flags), _offset(offset), _pCodec(pCodec)
{
	_decodeBuff.cnt = 0;
	_decodeBuff.idx = 0;
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
	if (_decodeBuff.idx < _decodeBuff.cnt) return _decodeBuff.buff[_decodeBuff.idx++];
	_decodeBuff.idx = 0;
	UInt32 codeUTF32 = 0;
	for (;;) {
		int chRaw = DoGetChar();
		if (chRaw < 0) return '\0';
		Codec::Result rtn = decoder.FeedData(static_cast<UInt8>(chRaw), &codeUTF32);
		if (rtn == Codec::Result::Complete) {
			if (codeUTF32 == 0) break;
			String::UTF32ToUTF8(codeUTF32, _decodeBuff.buff, &_decodeBuff.cnt);
			return _decodeBuff.buff[_decodeBuff.idx++];
		} else if (rtn == Codec::Result::CompleteSingle) {
			if (codeUTF32 == 0) break;
			return static_cast<char>(codeUTF32 & 0xff);
		} else if (rtn == Codec::Result::Error) {
			Error::Issue(ErrorType::CodecError, "not a valid character of %s", GetCodec().GetName());
			return -1;
		}
	}
	return '\0';
}

bool Stream::PutChar(char ch)
{
	UInt8 buffRtn[Codec::Encoder::BuffSize];
	size_t cnt = 0;
	Codec::Encoder& encoder = GetCodec().GetEncoder();
	Codec::Result rtn = encoder.FeedChar(ch, buffRtn, &cnt);
	if (rtn == Codec::Result::Error) return false;
	if (rtn == Codec::Result::Complete) {
		for (size_t i = 0; i < cnt; i++) {
			if (!DoPutChar(buffRtn[i])) return false;
		}
	}
	return true;
}

Stream& Stream::Print(const char* str)
{
	UInt8 buffRtn[Codec::Encoder::BuffSize];
	size_t cnt = 0;
	Codec::Encoder& encoder = GetCodec().GetEncoder();
	for (const char* p = str; *p != '\0'; ++p) {
		char ch = *p;
		Codec::Result rtn = encoder.FeedChar(ch, buffRtn, &cnt);
		if (rtn == Codec::Result::Error) return *this;
		if (rtn == Codec::Result::Complete) {
			for (size_t i = 0; i < cnt; i++) {
				if (!DoPutChar(buffRtn[i])) return *this;
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
	FormatterEx(*this).FormatV(format, ap);
	return *this;
}

Stream& Stream::Printf(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	return PrintfV(format, ap);
}

Stream& Stream::Printf(const String& format, ...)
{
	va_list ap;
	va_start(ap, &format);
	return PrintfV(format, ap);
}

Stream& Stream::PrintValueList(const char* format, const ValueList& valueList)
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

Iterator* Stream::ReadLines(size_t nLines, bool includeEOLFlag)
{
	return new Iterator_ReadLines(Reference(), nLines, includeEOLFlag);
}

Stream& Stream::SkipLines(size_t nLines)
{
	if (nLines == 0) return *this;
	while (char ch = GetChar()) {
		if (ch == '\n') {
			nLines--;
			if (nLines == 0) break;
		}
	}
	return *this;
}

String Stream::ReadText()
{
	String str;
	while (char ch = GetChar()) str += ch;
	return str;
}

Binary Stream::Read(size_t len)
{
	Binary buff(len, '\0');
	size_t lenRead = Read(&buff[0], len);
	buff.resize(lenRead);
	return buff;
}

BinaryReferable* Stream::ReadAsReferable(size_t len)
{
	RefPtr<BinaryReferable> pBuff(new BinaryReferable(len, '\0'));
	Binary& buff = pBuff->GetBinary();
	size_t lenRead = Read(&buff[0], len);
	buff.resize(lenRead);
	return pBuff.release();
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
	if (!ReadToBinary(pBuff->GetBinary())) return nullptr;
	return new Stream_Binary(Stream::Flag::Readable, pBuff.release());
}

void Stream::Dump(const void* buff, size_t bytes, const DumpStyle& ds)
{
	if (bytes == 0) return;
	const int nCols = 16;
	int iCol = 0;
	size_t addrOffset = ds.GetAddrOffset();
	size_t nDigitsAddrMin = ds.GetDigitsAddrMin();
	size_t nDigitsAddr = (String().Format("%llx", addrOffset + bytes - 1).size() + 1) / 2 * 2;
	if (nDigitsAddr < nDigitsAddrMin) nDigitsAddr = nDigitsAddrMin;
	String strLine, strASCII;
	const UInt8* p = reinterpret_cast<const UInt8*>(buff);
	for (size_t i = 0; i < bytes; ++i, ++p) {
		UInt8 data = *p;
		if (iCol > 0) {
			strLine += ' ';
		} else if (ds.IsAddrInfo()) {
			strLine.Format("%0*llx  ", nDigitsAddr, addrOffset + i);
		}
		strLine.Format(ds.IsUpperCase()? "%02X" : "%02x", data);
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

bool Stream::ReadToBinary(Binary& buff, size_t bytesUnit)
{
	RefPtr<Memory> pMemory(new MemoryHeap(bytesUnit));
	UInt8* buffWork = pMemory->GetPointerC<UInt8>();
	size_t bytesRead;
	while ((bytesRead = Read(buffWork, bytesUnit)) > 0) {
		buff.append(buffWork, bytesRead);
	}
	return !Error::IsIssued();
}

bool Stream::PipeToStream(Stream& streamDst, size_t bytesUnit)
{
	RefPtr<Memory> pMemory(new MemoryHeap(bytesUnit));
	UInt8* buffWork = pMemory->GetPointerC<UInt8>();
	size_t bytesRead;
	while ((bytesRead = Read(buffWork, bytesUnit)) > 0) {
		if (!streamDst.Write(buffWork, bytesRead)) break;
	}
	return !Error::IsIssued();
}

bool Stream::PipeToStreamCooked(Stream& streamDst)
{
	for (;;) {
		char ch = GetChar();
		if (ch == '\0') break;
		streamDst.PutChar(ch);
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
	return DoWrite(&ch, sizeof(ch));
}

String Stream::ToString(const StringStyle& ss) const
{
	String str;
	str += "Stream:";
	str += GetName();
	if (GetFlags() & Flag::Readable) str += ":r";
	if (GetFlags() & Flag::Writable) str += ":w";
	str.Format(":codec=%s", GetCodec().GetName());
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
Iterator_ReadLines::Iterator_ReadLines(Stream* pStream, size_t nLines, bool includeEOLFlag) :
	_pStream(pStream), _nLines(nLines), _includeEOLFlag(includeEOLFlag), _doneFlag(false)
{
}

Value* Iterator_ReadLines::DoNextValue()
{
	if (_doneFlag || static_cast<size_t>(_idxCur) >= _nLines) return nullptr;
	String str;
	if (!GetStream().ReadLine(str, _includeEOLFlag)) {
		_doneFlag = true;
		return nullptr;
	}
	return new Value_String(std::move(str));
}

String Iterator_ReadLines::ToString(const StringStyle& ss) const
{
	String str = "ReadlLines";
	if (_nLines != static_cast<size_t>(-1)) str.Format(":nLines=%zu", _nLines);
	return str;
}

}
