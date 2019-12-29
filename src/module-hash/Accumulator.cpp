//==============================================================================
// Accumulator.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(hash)

//------------------------------------------------------------------------------
// Accumulator
//------------------------------------------------------------------------------
const Binary& Accumulator::GetDigest()
{
	if (_digest.empty()) Finish();
	return _digest;
}

String Accumulator::GetDigestHex()
{
	String str;
	for (UInt8 ch : GetDigest()) str.Printf("%02x", ch);
	return str;
}

//------------------------------------------------------------------------------
// Accumulator_MD5
//------------------------------------------------------------------------------
Accumulator_MD5::Accumulator_MD5()
{
	_digest.clear();
	::md5_init(&_state);
}

void Accumulator_MD5::Initialize()
{
	_digest.clear();
	::md5_init(&_state);
}

const char* Accumulator_MD5::GetName() const
{
	return "MD5";
}

size_t Accumulator_MD5::DoWrite(const void* buff, size_t len)
{
	::md5_append(&_state, reinterpret_cast<const md5_byte_t *>(buff), static_cast<int>(len));
	return len;
}

void Accumulator_MD5::Finish()
{
	md5_byte_t digest[16];
	::md5_finish(&_state, digest);
	_digest = Binary(reinterpret_cast<UInt8*>(digest), sizeof(digest));
}

//-----------------------------------------------------------------------------
// Accumulator_SHA1 implementation
//-----------------------------------------------------------------------------
Accumulator_SHA1::Accumulator_SHA1()
{
	_digest.clear();
	::sha1_starts(&_ctx);
}

void Accumulator_SHA1::Initialize()
{
	_digest.clear();
	::sha1_starts(&_ctx);
}

const char* Accumulator_SHA1::GetName() const
{
	return "SHA1";
}

size_t Accumulator_SHA1::DoWrite(const void* buff, size_t len)
{
	::sha1_update(&_ctx, reinterpret_cast<uint8*>(const_cast<void*>(buff)),
				  static_cast<uint32>(len));
	return len;
}

void Accumulator_SHA1::Finish()
{
	uint8 digest[20];
	::sha1_finish(&_ctx, digest);
	_digest = Binary(reinterpret_cast<UInt8*>(digest), sizeof(digest));
}

//-----------------------------------------------------------------------------
// Accumulator_CRC32 implementation
//-----------------------------------------------------------------------------
Accumulator_CRC32::Accumulator_CRC32()
{
	_digest.clear();
}

void Accumulator_CRC32::Initialize()
{
	_digest.clear();
	_crc32.Initialize();
}

const char *Accumulator_CRC32::GetName() const
{
	return "CRC32";
}

size_t Accumulator_CRC32::DoWrite(const void* buff, size_t len)
{
	_crc32.Update(buff, len);
	return len;
}

void Accumulator_CRC32::Finish()
{
	UInt8 digest[4];
	UInt32 result = _crc32.GetResult();
	digest[0] = static_cast<UInt8>(result >> 24);
	digest[1] = static_cast<UInt8>(result >> 16);
	digest[2] = static_cast<UInt8>(result >> 8);
	digest[3] = static_cast<UInt8>(result >> 0);
	_digest = Binary(true, digest, sizeof(digest));
}

Value* Accumulator_CRC32::GetValue()
{
	if (_digest.empty()) Finish();
	return new Value_Number(_crc32.GetResult());
}

Gurax_EndModuleScope(hash)
