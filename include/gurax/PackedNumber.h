//==============================================================================
// PackedNumber
//==============================================================================
#ifndef GURAX_PACKEDNUMBER_H
#define GURAX_PACKEDNUMBER_H

#define Gurax_PackedUInt16_LE(x) \
UInt8 x##_uint16_b0, x##_uint16_b8

#define Gurax_PackedUInt16_BE(x) \
UInt8 x##_uint16_b8, x##_uint16_b0

#define Gurax_PackedUInt32_LE(x) \
UInt8 x##_uint32_b0, x##_uint32_b8, x##_uint32_b16, x##_uint32_b24

#define Gurax_PackedUInt32_BE(x) \
UInt8 x##_uint32_b24, x##_uint32_b16, x##_uint32_b8, x##_uint32_b0

#define Gurax_PackedUInt64_LE(x) \
UInt8 x##_uint64_b0, x##_uint64_b8, x##_uint64_b16, x##_uint64_b24, \
	x##_uint64_b32, x##_uint64_b40, x##_uint64_b48, x##_uint64_b56

#define Gurax_PackedUInt64_BE(x) \
UInt8 x##_uint64_b56, x##_uint64_b48, x##_uint64_b40, x##_uint64_b32, \
	x##_uint64_b24, x##_uint64_b16, x##_uint64_b8, x##_uint64_b0

#define Gurax_PackedInt16_LE(x) Gurax_PackedUInt16_LE(x)
#define Gurax_PackedInt16_BE(x) Gurax_PackedUInt16_BE(x)

#define Gurax_PackedInt32_LE(x) Gurax_PackedUInt32_LE(x)
#define Gurax_PackedInt32_BE(x) Gurax_PackedUInt32_BE(x)

#define Gurax_PackedInt64_LE(x) Gurax_PackedUInt64_LE(x)
#define Gurax_PackedInt64_BE(x) Gurax_PackedUInt64_BE(x)

#define Gurax_PackUInt16(x, n) ( \
	x##_uint16_b0 = static_cast<UInt8>((static_cast<UInt16>(n) >> 0) & 0xff), \
	x##_uint16_b8 = static_cast<UInt8>((static_cast<UInt16>(n) >> 8) & 0xff) \
)

#define Gurax_PackUInt32(x, n) ( \
	x##_uint32_b0 = static_cast<UInt8>((static_cast<UInt32>(n)  >>  0) & 0xff), \
	x##_uint32_b8 = static_cast<UInt8>((static_cast<UInt32>(n)  >>  8) & 0xff), \
	x##_uint32_b16 = static_cast<UInt8>((static_cast<UInt32>(n) >> 16) & 0xff), \
	x##_uint32_b24 = static_cast<UInt8>((static_cast<UInt32>(n) >> 24) & 0xff) \
)

#define Gurax_PackUInt64(x, n) ( \
	x##_uint64_b0 = static_cast<UInt8>((static_cast<UInt64>(n)  >>  0) & 0xff), \
	x##_uint64_b8 = static_cast<UInt8>((static_cast<UInt64>(n)  >>  8) & 0xff), \
	x##_uint64_b16 = static_cast<UInt8>((static_cast<UInt64>(n) >> 16) & 0xff), \
	x##_uint64_b24 = static_cast<UInt8>((static_cast<UInt64>(n) >> 24) & 0xff), \
	x##_uint64_b32 = static_cast<UInt8>((static_cast<UInt64>(n) >> 32) & 0xff), \
	x##_uint64_b40 = static_cast<UInt8>((static_cast<UInt64>(n) >> 40) & 0xff), \
	x##_uint64_b48 = static_cast<UInt8>((static_cast<UInt64>(n) >> 48) & 0xff), \
	x##_uint64_b56 = static_cast<UInt8>((static_cast<UInt64>(n) >> 56) & 0xff) \
)

#define Gurax_UnpackUInt16(x) ( \
	(static_cast<UInt16>(x##_uint16_b0) << 0) | \
	(static_cast<UInt16>(x##_uint16_b8) << 8) \
)

#define Gurax_UnpackUInt32(x) ( \
	(static_cast<UInt32>(x##_uint32_b0)  <<  0) | \
	(static_cast<UInt32>(x##_uint32_b8)  <<  8) | \
	(static_cast<UInt32>(x##_uint32_b16) << 16) | \
	(static_cast<UInt32>(x##_uint32_b24) << 24) \
)

#define Gurax_UnpackUInt64(x) ( \
	(static_cast<UInt64>(x##_uint64_b0)  <<  0) | \
	(static_cast<UInt64>(x##_uint64_b8)  <<  8) | \
	(static_cast<UInt64>(x##_uint64_b16) << 16) | \
	(static_cast<UInt64>(x##_uint64_b24) << 24) | \
	(static_cast<UInt64>(x##_uint64_b32) << 32) | \
	(static_cast<UInt64>(x##_uint64_b40) << 40) | \
	(static_cast<UInt64>(x##_uint64_b48) << 48) | \
	(static_cast<UInt64>(x##_uint64_b56) << 56) \
)

#define Gurax_PackInt16(x, n) Gurax_PackUInt16(x, n)
#define Gurax_PackInt32(x, n) Gurax_PackUInt32(x, n)
#define Gurax_PackInt64(x, n) Gurax_PackUInt64(x, n)

#define Gurax_UnpackInt16(x) static_cast<Int16>(Gurax_UnpackUInt16(x))
#define Gurax_UnpackInt32(x) static_cast<Int32>(Gurax_UnpackUInt32(x))
#define Gurax_UnpackInt64(x) static_cast<int64>(Gurax_UnpackUInt64(x))

#endif
