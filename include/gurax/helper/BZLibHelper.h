//==============================================================================
// BZLibHeader.h
//==============================================================================
#ifndef GURAX_BZLIBHELPER_H
#define GURAX_BZLIBHELPER_H
#include <gurax.h>
#include <bzlib.h>

namespace Gurax {
namespace BZLib {

//------------------------------------------------------------------------------
// Stream_Reader
//------------------------------------------------------------------------------
class Stream_Reader : public Stream {
private:
	RefPtr<Stream> _pStream;
	RefPtr<Memory> _pMemory;
	size_t _bytesSrc;
	size_t _bytesBuff;
	size_t _bytesOut;
	size_t _offsetOut;
	bz_stream _bzstrm;
	char* _buffOut;
	char* _buffIn;
	bool _doneFlag;
public:
	Stream_Reader(Stream* pStream, size_t bytesSrc = -1, size_t bytesBuff = 32768) :
		Stream(Flag::Readable), _pStream(pStream), _bytesSrc(bytesSrc), _bytesBuff(bytesBuff), _bytesOut(0),
		_offsetOut(0), _buffOut(nullptr), _buffIn(nullptr), _doneFlag(false) {
		SetCodec(pStream->GetCodec().Duplicate());
	}
	~Stream_Reader() {
		::BZ2_bzDecompressEnd(&_bzstrm);
	}
	bool Initialize(int verbosity, int small) {
		::memset(&_bzstrm, 0x00, sizeof(_bzstrm));
		_bzstrm.bzalloc = nullptr;
		_bzstrm.bzfree = nullptr;
		_bzstrm.opaque = nullptr;
		_bzstrm.avail_in = 0;
		if (::BZ2_bzDecompressInit(&_bzstrm, verbosity, small) != BZ_OK) {
			Error::Issue(ErrorType::IOError, "bzlib error");
			return false;
		}
		_pMemory.reset(new MemoryHeap(_bytesBuff * 2));
		_buffOut = _pMemory->GetPointerC<char>();
		_buffIn = _pMemory->GetPointerC<char>(_bytesBuff);
		return true;
	}
	virtual const char* GetName() const override {
		return _pStream? _pStream->GetName() : "(invalid)";
	}
	virtual const char* GetIdentifier() const override {
		return _pStream? _pStream->GetIdentifier() : "";
	}
	virtual bool DoClose() override { return true; }
	virtual bool DoWrite(const void* buff, size_t len) override { return false; }
	virtual size_t DoRead(void* buff, size_t bytes) override {
		size_t bytesRead = 0;
		char* buffp = reinterpret_cast<char*>(buff);
		bool continueFlag = true;
		for (size_t bytesRest = bytes; bytesRest > 0 && continueFlag; ) {
			if (_offsetOut >= _bytesOut) {
				_offsetOut = 0;
				_bytesOut = 0;
				if (_doneFlag) break;
				while (_bytesOut == 0) {
					if (_bzstrm.avail_in == 0) {
						size_t bytesRead = _pStream->Read(_buffIn, std::min(_bytesBuff, _bytesSrc));
						if (Error::IsIssued()) {
							::BZ2_bzDecompressEnd(&_bzstrm);
							return 0;
						}
						if (bytesRead == 0) {
							Error::Issue(ErrorType::IOError, "unexpected end of bzip stream");
							return 0;
						}
						if (_bytesSrc != -1) {
							_bytesSrc -= bytesRead;
						}
						_bzstrm.avail_in = static_cast<unsigned int>(bytesRead);
						_bzstrm.next_in = _buffIn;
					}
					_bzstrm.avail_out = static_cast<unsigned int>(_bytesBuff);
					_bzstrm.next_out = _buffOut;
					int ret = ::BZ2_bzDecompress(&_bzstrm);
					_bytesOut = _bytesBuff - _bzstrm.avail_out;
					if (ret == BZ_OK) {
						// nothing to do
					} else if (ret == BZ_STREAM_END) {
						_doneFlag = true;
						continueFlag = false;
						break;
					} else {
						Error::Issue(ErrorType::IOError, "bzlib error");
						::BZ2_bzDecompressEnd(&_bzstrm);
						return 0;
					}
				}
			}
			size_t bytesToCopy = _bytesOut - _offsetOut;
			if (bytesToCopy > bytesRest) bytesToCopy = bytesRest;
			if (buffp != nullptr) {
				::memcpy(buffp + bytesRead, _buffOut + _offsetOut, bytesToCopy);
			}
			_offset += bytesToCopy;
			_offsetOut += bytesToCopy;
			bytesRest -= bytesToCopy;
			bytesRead += bytesToCopy;
		}
		return bytesRead;
	}
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override {
		if (offset >= offsetPrev) {
			size_t bytesToRead = offset - offsetPrev;
			if (bytesToRead == 0) return true;
			return DoRead(nullptr, bytesToRead) == bytesToRead;
		}
		Error::Issue(ErrorType::UnimplementedError, "backward seeking is not supported");
		return false;
	}
	virtual bool DoFlush() override { return true; }
};

//------------------------------------------------------------------------------
// Stream_Writer
//------------------------------------------------------------------------------
class Stream_Writer : public Stream {
private:
	RefPtr<Stream> _pStream;
	RefPtr<Memory> _pMemory;
	size_t _bytesBuff;
	bz_stream _bzstrm;
	char* _buffOut;
	char* _buffIn;
public:
	Stream_Writer(Stream* pStream, size_t bytesBuff = 32768) :
			Stream(Flag::Writable), _pStream(pStream),
			_bytesBuff(bytesBuff), _buffOut(nullptr), _buffIn(nullptr) {
		SetCodec(pStream->GetCodec().Duplicate());
	}
	~Stream_Writer() { Close(); }
	bool Initialize(int blockSize100k, int verbosity, int workFactor) {
		::memset(&_bzstrm, 0x00, sizeof(_bzstrm));
		_bzstrm.bzalloc = nullptr;
		_bzstrm.bzfree = nullptr;
		_bzstrm.opaque = nullptr;
		if (::BZ2_bzCompressInit(&_bzstrm, blockSize100k, verbosity, workFactor) != BZ_OK) {
			Error::Issue(ErrorType::IOError, "bzlib error");
			return false;
		}
		_pMemory.reset(new MemoryHeap(_bytesBuff * 2));
		_buffOut = _pMemory->GetPointerC<char>();
		_buffIn = _pMemory->GetPointerC<char>(_bytesBuff);
		_bzstrm.next_out = _buffOut;
		_bzstrm.avail_out = static_cast<unsigned int>(_bytesBuff);
		return true;
	}
	virtual const char* GetName() const override {
		return _pStream? _pStream->GetName() : "(invalid)";
	}
	virtual const char* GetIdentifier() const override {
		return _pStream? _pStream->GetIdentifier() : "";
	}
	virtual bool DoWrite(const void* buff, size_t bytes) override {
		if (!_pStream) return false;
		_bzstrm.next_in = reinterpret_cast<char*>(const_cast<void*>(buff));
		_bzstrm.avail_in = static_cast<unsigned int>(bytes);
		while (_bzstrm.avail_in > 0) {
			if (_bzstrm.avail_out == 0) {
				_pStream->Write(_buffOut, _bytesBuff);
				if (Error::IsIssued()) return false;
				_bzstrm.next_out = _buffOut;
				_bzstrm.avail_out = static_cast<unsigned int>(_bytesBuff);
			}
			int rtn = ::BZ2_bzCompress(&_bzstrm, BZ_RUN);
			if (rtn != BZ_RUN_OK) {
				Error::Issue(ErrorType::IOError, "bzlib error");
				return false;
			}
		}
		_offset += bytes;
		return true;
	}
	virtual bool DoFlush() override { return true; }
	virtual bool DoClose() override {
		if (!_pStream) return true;
		for (;;) {
			if (_bzstrm.avail_out == 0) {
				_pStream->Write(_buffOut, _bytesBuff);
				if (Error::IsIssued()) return 0;
				_bzstrm.next_out = _buffOut;
				_bzstrm.avail_out = static_cast<unsigned int>(_bytesBuff);
			}
			int rtn = ::BZ2_bzCompress(&_bzstrm, BZ_FINISH);
			if (rtn == BZ_STREAM_END) break;
			if (rtn != BZ_FINISH_OK) {
				Error::Issue(ErrorType::IOError, "bzlib error");
				return false;
			}
		}
		size_t bytesOut = _bytesBuff - _bzstrm.avail_out;
		if (bytesOut > 0) {
			_pStream->Write(_buffOut, bytesOut);
		}
		::BZ2_bzCompressEnd(&_bzstrm);
		if (Error::IsIssued()) return false;
		_pStream.reset(nullptr);
		return true;
	}
	virtual size_t DoRead(void* buff, size_t bytes) override {
		return 0;
	}
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override { return false; }
};

}
}

#endif
