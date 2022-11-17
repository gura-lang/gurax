//==============================================================================
// CRC32.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// CRC32
//------------------------------------------------------------------------------
void CRC32::Update(const void* buff, size_t bytes)
{
	static UInt32* tbl = nullptr;
	if (!tbl) {
		const UInt32 CRC32_POLY = 0xedb88320; // CRC-32-IEEE 802.3
		tbl = new UInt32 [256];
		for (UInt32 i = 0; i < 256; i++){
			UInt32 x = i;
			for (int j = 0; j < 8; j++) {
				x = (x & 1)? ((x >> 1) ^ CRC32_POLY) : (x >> 1);
				tbl[i] = x;
			}
		}
	}
	const UInt8* buffp = reinterpret_cast<const UInt8*>(buff);
	for (size_t i = 0; i < bytes; i++, buffp++) {
		_crc32 = ((_crc32 >> 8) & 0x00ffffff) ^ tbl[(_crc32 ^ *buffp) & 0xff];
	}
	_bytes += bytes;
}

}
