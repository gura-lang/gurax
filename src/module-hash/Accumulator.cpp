//==============================================================================
// Accumulator.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(hash)

//------------------------------------------------------------------------------
// Accumulator
//------------------------------------------------------------------------------

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

const Binary& Accumulator_MD5::GetDigest()
{
	if (_digest.empty()) Finish();
	return _digest;
}

Gurax_EndModuleScope(hash)
