//==============================================================================
// ZLibHeader.h
//==============================================================================
#ifndef GURAX_ZLIBHELPER_H
#define GURAX_ZLIBHELPER_H
#include <gurax.h>
#include <zlib.h>

namespace Gurax {
namespace ZLib {

//------------------------------------------------------------------------------
// GZHeader
// see RFC 1952 (GZIP file format specification version 4.3) for specification
//------------------------------------------------------------------------------
class GZHeader {
public:
	struct Fields {
		UInt8 Identification1;
		UInt8 Identification2;
		UInt8 CompressionMethod;
		UInt8 Flags;
		Gurax_PackedUInt32_LE(ModificationTime);
		UInt8 ExtraFlags;
		UInt8 OperatingSystem;
		enum { Size = 10 };
		bool GetFTEXT() const { return (Flags & (1 << 0))? true : false; }
		bool GetFHCRC() const { return (Flags & (1 << 1))? true : false; }
		bool GetFEXTRA() const { return (Flags & (1 << 2))? true : false; }
		bool GetFNAME() const { return (Flags & (1 << 3))? true : false; }
		bool GetFCOMMENT() const { return (Flags & (1 << 4))? true : false; }
	};
private:
	Fields _fields;
	Binary _extra;
	String _fileName;
	String _comment;
public:
	GZHeader() {
		::memset(&_fields, 0x00, Fields::Size);
		_fields.Identification1		= 0x1f;
		_fields.Identification2		= 0x8b;
		_fields.CompressionMethod	= 0x08;
		_fields.Flags				= 0x00;
		_fields.ExtraFlags			= 0x00;
		_fields.OperatingSystem		= 0x00;
	}
	bool Read(Stream &stream) {
		if (stream.Read(sig, &_fields, Fields::Size) < Fields::Size) {
			SetError_InvalidFormat(sig);
			return false;
		}
		if (_fields.Identification1 != 0x1f || _fields.Identification2 != 0x8b) {
			SetError_InvalidFormat(sig);
			return false;
		}
		if (_fields.GetFEXTRA()) {
			struct {
				Gurax_PackedUInt16_LE(ExtraLength);
			} fields;
			if (stream.Read(sig, &fields, 2) < 2) {
				SetError_InvalidFormat(sig);
				return false;
			}
			unsigned short ExtraLength = Gurax_UnpackUInt16(fields.ExtraLength);
			if (!stream.Seek(sig, ExtraLength, Stream::SeekCur)) {
				SetError_InvalidFormat(sig);
				return false;
			}
		}
		if (_fields.GetFNAME()) {
			char ch;
			for (;;) {
				if (stream.Read(sig, &ch, 1) < 1) {
					SetError_InvalidFormat(sig);
					return false;
				}
				if (ch == '\0') break;
				_fileName += ch;
			}
		}
		if (_fields.GetFCOMMENT()) {
			char ch;
			for (;;) {
				if (stream.Read(sig, &ch, 1) < 1) {
					SetError_InvalidFormat(sig);
					return false;
				}
				if (ch == '\0') break;
				_comment += ch;
			}
		}
		if (_fields.GetFHCRC()) {
			if (!stream.Seek(sig, 2, Stream::SeekCur)) {
				SetError_InvalidFormat(sig);
				return false;
			}
		}
		return true;
	}
	bool Write(Stream &stream) {
		if (stream.Write(sig, &_fields, Fields::Size) < Fields::Size) {
			SetError_InvalidFormat(sig);
			return false;
		}
		if (_fields.GetFEXTRA()) {
			struct {
				Gurax_PackedUInt16_LE(ExtraLength);
			} fields;
			Gurax_PackUInt16(fields.ExtraLength, static_cast<unsigned short>(_extra.size()));
			if (stream.Write(sig, &fields, 2) < 2) {
				SetError_InvalidFormat(sig);
				return false;
			}
		}
		if (_fields.GetFNAME()) {
			size_t bytes = _fileName.size() + 1;
			if (stream.Write(sig, _fileName.c_str(), bytes) < bytes) {
				SetError_InvalidFormat(sig);
				return false;
			}
		}
		if (_fields.GetFCOMMENT()) {
			size_t bytes = _comment.size() + 1;
			if (stream.Write(sig, _comment.c_str(), bytes) < bytes) {
				SetError_InvalidFormat(sig);
				return false;
			}
		}
		if (_fields.GetFHCRC()) {
			unsigned short crc16 = 0x0000;
			struct {
				Gurax_PackedUInt16_LE(CRC16);
			} fields;
			Gurax_PackUInt16(fields.CRC16, crc16);
			if (stream.Write(sig, &fields, 2) < 2) {
				SetError_InvalidFormat(sig);
				return false;
			}
		}
		return true;
	}
	Fields &GetFields() { return _fields; }
	const char *GetFileName() const { return _fileName.c_str(); }
	const char *GetComment() const { return _comment.c_str(); }
	void SetModificationTime(unsigned long time) {
		Gurax_PackUInt32(_fields.ModificationTime, time);
	}
	void SetExtra(const Binary &extra) {
		_extra = extra;
		_fields.Flags |= (1 << 2);
	}
	void SetFileName(const char *fileName) {
		_fileName = fileName;
		_fields.Flags |= (1 << 3);
	}
	void SetComment(const char *comment) {
		_comment = comment;
		_fields.Flags |= (1 << 4);
	}
private:
	void SetError_InvalidFormat() {
		sig.SetError(ERR_FormatError, "invalid gzip format");
	}
};

//------------------------------------------------------------------------------
// Stream_Inflater
//------------------------------------------------------------------------------
class Stream_Inflater : public Stream {
private:
	RefPtr<Stream> _pStream;
	RefPtr<Memory> _pMemory;
	size_t _bytesSrc;
	size_t _bytesBuff;
	size_t _bytesOut;
	size_t _offsetOut;
	z_stream _zstrm;
	UInt8 *_buffOut;
	UInt8 *_buffIn;
	bool _doneFlag;
public:
	Stream_Inflater(Stream *pStream, size_t bytesSrc, size_t bytesBuff = 32768) :
			Stream(Flag::Readable), _pStream(pStream), _bytesSrc(bytesSrc),
			_bytesBuff(bytesBuff), _bytesOut(0),
			_offsetOut(0), _buffOut(nullptr), _buffIn(nullptr), _doneFlag(false) {
		CopyCodec(pStream);
	}
	~Stream_Inflater() {
		::inflateEnd(&_zstrm);
	}
	bool Initialize(int windowBits = 15) {
		::memset(&_zstrm, 0x00, sizeof(_zstrm));
		_zstrm.zalloc = Z_NULL;
		_zstrm.zfree = Z_NULL;
		_zstrm.opaque = Z_NULL;
		_zstrm.avail_in = 0;
		if (::inflateInit2(&_zstrm, windowBits) != Z_OK) {
			sig.SetError(ERR_IOError, "%s",
						(_zstrm.msg == nullptr)? "zlib error" : _zstrm.msg);
			return false;
		}
		_pMemory.reset(new MemoryHeap(_bytesBuff * 2));
		_buffOut = reinterpret_cast<UInt8 *>(_pMemory->GetPointer(0));
		_buffIn = reinterpret_cast<UInt8 *>(_pMemory->GetPointer(_bytesBuff));
		return true;
	}
	virtual const char *GetName() const {
		return (_pStream.IsNull())? "(invalid)" : _pStream->GetName();
	}
	virtual const char *GetIdentifier() const {
		return (_pStream.IsNull())? nullptr : _pStream->GetIdentifier();
	}
	virtual size_t DoWrite(const void *buff, size_t len) {
		return 0;
	}
	virtual size_t DoRead(void *buff, size_t bytes) {
		size_t bytesRead = 0;
		char *buffp = reinterpret_cast<char *>(buff);
		bool continueFlag = true;
		for (size_t bytesRest = bytes; bytesRest > 0 && continueFlag; ) {
			if (_offsetOut >= _bytesOut) {
				_offsetOut = 0;
				_bytesOut = 0;
				if (_doneFlag) break;
				while (_bytesOut == 0) {
					if (_zstrm.avail_in == 0) {
						size_t bytesRead = _pStream->Read(sig,
										_buffIn, ChooseMin(_bytesBuff, _bytesSrc));
						if (Error::IsIssued()) {
							::inflateEnd(&_zstrm);
							return 0;
						}
						if (bytesRead == 0) {
							sig.SetError(ERR_IOError, "unexpected end of gzip stream");
							return 0;
						}
						if (_bytesSrc != InvalidSize) {
							_bytesSrc -= bytesRead;
						}
						_zstrm.avail_in = static_cast<uInt>(bytesRead);
						_zstrm.next_in = _buffIn;
					}
					_zstrm.avail_out = static_cast<uInt>(_bytesBuff);
					_zstrm.next_out = _buffOut;
					int ret = ::inflate(&_zstrm, Z_NO_FLUSH);
					_bytesOut = _bytesBuff - _zstrm.avail_out;
					if (ret == Z_OK) {
						// nothing to do
					} else if (ret == Z_STREAM_END) {
						_doneFlag = true;
						continueFlag = false;
					} else {
						sig.SetError(ERR_IOError, "%s",
							(_zstrm.msg == nullptr)? "zlib error" : _zstrm.msg);
						::inflateEnd(&_zstrm);
						return 0;
					}
				}
			}
			size_t bytesToCopy = _bytesOut - _offsetOut;
			if (bytesToCopy > bytesRest) bytesToCopy = bytesRest;
			if (buffp != nullptr) {
				::memcpy(buffp + bytesRead, _buffOut + _offsetOut, bytesToCopy);
			}
			_offsetOut += bytesToCopy;
			bytesRest -= bytesToCopy;
			bytesRead += bytesToCopy;
		}
		return bytesRead;
	}
	virtual bool DoSeek(long offset, size_t offsetPrev, SeekMode seekMode) {
		if (seekMode == SeekSet) {
			if (static_cast<size_t>(offset) >= offsetPrev) {
				size_t bytesToRead = static_cast<size_t>(offset) - offsetPrev;
				if (bytesToRead == 0) return true;
				return DoRead(sig, nullptr, bytesToRead) == static_cast<size_t>(bytesToRead);
			}
		} else if (seekMode == SeekCur) {
			if (offset == 0) {
				return true;
			} else if (offset > 0) {
				return DoRead(sig, nullptr, offset) == static_cast<size_t>(offset);
			}
		}
		sig.SetError(ERR_SystemError, "backward seeking is not supported");
		return false;
	}
	virtual bool DoFlush() {
		return false;
	}
	virtual bool DoClose() {
		return true;
	}
};

//------------------------------------------------------------------------------
// Stream_Deflater
//------------------------------------------------------------------------------
class Stream_Deflater : public Stream {
private:
	RefPtr<Stream> _pStream;
	RefPtr<Memory> _pMemory;
	size_t _bytesBuff;
	size_t _offsetOut;
	z_stream _zstrm;
	UInt8 *_buffOut;
	UInt8 *_buffIn;
public:
	Stream_Deflater(Stream *pStream, size_t bytesBuff = 32768) :
			Stream(Flag::Writable), _pStream(pStream),
			_bytesBuff(bytesBuff), _offsetOut(0), _buffOut(nullptr), _buffIn(nullptr) {
		CopyCodec(pStream);
	}
	~Stream_Deflater() {
		DoClose(_sig);
	}
	bool Initialize(int level, int windowBits, int memLevel, int strategy) {
		::memset(&_zstrm, 0x00, sizeof(_zstrm));
		_zstrm.zalloc = Z_NULL;
		_zstrm.zfree = Z_NULL;
		_zstrm.opaque = Z_NULL;
		if (::deflateInit2(&_zstrm, level,
							Z_DEFLATED, windowBits, memLevel, strategy) != Z_OK) {
			sig.SetError(ERR_IOError, "%s",
						(_zstrm.msg == nullptr)? "zlib error" : _zstrm.msg);
			return false;
		}
		_pMemory.reset(new MemoryHeap(_bytesBuff * 2));
		_buffOut = reinterpret_cast<UInt8 *>(_pMemory->GetPointer(0));
		_buffIn = reinterpret_cast<UInt8 *>(_pMemory->GetPointer(_bytesBuff));
		_zstrm.next_out = _buffOut;
		_zstrm.avail_out = static_cast<uInt>(_bytesBuff);
		return true;
	}
	virtual const char *GetName() const {
		return (_pStream.IsNull())? "(invalid)" : _pStream->GetName();
	}
	virtual const char *GetIdentifier() const {
		return (_pStream.IsNull())? nullptr : _pStream->GetIdentifier();
	}
	virtual size_t DoWrite(const void *buff, size_t len) {
		if (_pStream.IsNull()) return 0;
		_zstrm.next_in = reinterpret_cast<Bytef *>(const_cast<void *>(buff));
		_zstrm.avail_in = static_cast<uInt>(len);
		while (_zstrm.avail_in > 0) {
			if (_zstrm.avail_out == 0) {
				_pStream->Write(sig, _buffOut, _bytesBuff);
				if (Error::IsIssued()) return 0;
				_zstrm.next_out = _buffOut;
				_zstrm.avail_out = static_cast<uInt>(_bytesBuff);
			}
			if (::deflate(&_zstrm, Z_NO_FLUSH) != Z_OK) {
				sig.SetError(ERR_IOError, "%s",
						(_zstrm.msg == nullptr)? "zlib error" : _zstrm.msg);
				return 0;
			}
		}
		return len;
	}
	virtual bool DoFlush() {
		return DoClose(sig);
	}
	virtual bool DoClose() {
		if (_pStream.IsNull()) return true;
		for (;;) {
			if (_zstrm.avail_out == 0) {
				_pStream->Write(sig, _buffOut, _bytesBuff);
				if (Error::IsIssued()) return 0;
				_zstrm.next_out = _buffOut;
				_zstrm.avail_out = static_cast<uInt>(_bytesBuff);
			}
			int rtn = ::deflate(&_zstrm, Z_FINISH);
			if (rtn == Z_STREAM_END) break;
			if (rtn != Z_OK) {
				sig.SetError(ERR_IOError, "%s",
						(_zstrm.msg == nullptr)? "zlib error" : _zstrm.msg);
				return false;
			}
		}
		size_t bytesOut = _bytesBuff - _zstrm.avail_out;
		if (bytesOut > 0) {
			_pStream->Write(sig, _buffOut, bytesOut);
		}
		::deflateEnd(&_zstrm);
		if (Error::IsIssued()) return false;
		bool rtn = _pStream->Flush(sig);
		_pStream.reset(nullptr);
		return rtn;
	}
	virtual size_t DoRead(void *buff, size_t bytes) {
		return 0;
	}
	virtual bool DoSeek(long offset, size_t offsetPrev, SeekMode seekMode) {
		return false;
	}
};

}
}

#endif
