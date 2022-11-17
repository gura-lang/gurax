//==============================================================================
// CRC32.h
//==============================================================================
#ifndef GURAX_CRC32_H
#define GURAX_CRC32_H
#include "Common.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// CRC32
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE CRC32 {
private:
	UInt32 _crc32;
	size_t _bytes;
public:
	CRC32() : _crc32(0xffffffff), _bytes(0) {}
	void Initialize() { _crc32 = 0xffffffff, _bytes = 0; }
	void Update(const void* buff, size_t bytes);
	UInt32 GetResult() const { return ~_crc32 & 0xffffffff; }
	size_t GetBytes() const { return _bytes; }
};

}

#endif
