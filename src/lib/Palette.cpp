//==============================================================================
// Palette.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Palette
//------------------------------------------------------------------------------
void Palette::Bootup()
{
}

Palette::Palette(size_t n) : _packedTbl(new UInt32[n]), _n(n)
{
}

Palette::Palette(const UInt32* packedTbl, size_t n) : _packedTbl(new UInt32[n]), _n(n)
{
	::memcpy(_packedTbl.get(), packedTbl, sizeof(UInt32) * n);
}

Palette* Palette::Mono()
{
	static const UInt32 packedTbl[] = {
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 0: black
		PackRGBA(0xff, 0xff, 0xff, 0xff),	// 1: white
	};
	return new Palette(packedTbl, 2);
}

Palette* Palette::Basic()
{
	static const UInt32 packedTbl[] = {
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 0: black
		PackRGBA(0x80, 0x00, 0x00, 0xff),	// 1: maroon
		PackRGBA(0x00, 0x80, 0x00, 0xff),	// 2: green
		PackRGBA(0x80, 0x80, 0x00, 0xff),	// 3: olive
		PackRGBA(0x00, 0x00, 0x80, 0xff),	// 4: navy
		PackRGBA(0x80, 0x00, 0x80, 0xff),	// 5: purple
		PackRGBA(0x00, 0x80, 0x80, 0xff),	// 6: teal
		PackRGBA(0x80, 0x80, 0x80, 0xff),	// 7: gray
		PackRGBA(0xc0, 0xc0, 0xc0, 0xff),	// 8: silver
		PackRGBA(0xff, 0x00, 0x00, 0xff),	// 9: red
		PackRGBA(0x00, 0xff, 0x00, 0xff),	// 10: lime
		PackRGBA(0xff, 0xff, 0x00, 0xff),	// 11: yellow
		PackRGBA(0x00, 0x00, 0xff, 0xff),	// 12: blue
		PackRGBA(0xff, 0x00, 0xff, 0xff),	// 13: fuchsia
		PackRGBA(0x00, 0xff, 0xff, 0xff),	// 14: aqua
		PackRGBA(0xff, 0xff, 0xff, 0xff),	// 15: white
	};
	return new Palette(packedTbl, 16);
}

Palette* Palette::WebSafe()
{
	static const UInt32 packedTbl[] = {
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 0
		PackRGBA(0x33, 0x00, 0x00, 0xff),	// 1
		PackRGBA(0x66, 0x00, 0x00, 0xff),	// 2
		PackRGBA(0x99, 0x00, 0x00, 0xff),	// 3
		PackRGBA(0xcc, 0x00, 0x00, 0xff),	// 4
		PackRGBA(0xff, 0x00, 0x00, 0xff),	// 5
		PackRGBA(0x00, 0x33, 0x00, 0xff),	// 6
		PackRGBA(0x33, 0x33, 0x00, 0xff),	// 7
		PackRGBA(0x66, 0x33, 0x00, 0xff),	// 8
		PackRGBA(0x99, 0x33, 0x00, 0xff),	// 9
		PackRGBA(0xcc, 0x33, 0x00, 0xff),	// 10
		PackRGBA(0xff, 0x33, 0x00, 0xff),	// 11
		PackRGBA(0x00, 0x66, 0x00, 0xff),	// 12
		PackRGBA(0x33, 0x66, 0x00, 0xff),	// 13
		PackRGBA(0x66, 0x66, 0x00, 0xff),	// 14
		PackRGBA(0x99, 0x66, 0x00, 0xff),	// 15
		PackRGBA(0xcc, 0x66, 0x00, 0xff),	// 16
		PackRGBA(0xff, 0x66, 0x00, 0xff),	// 17
		PackRGBA(0x00, 0x99, 0x00, 0xff),	// 18
		PackRGBA(0x33, 0x99, 0x00, 0xff),	// 19
		PackRGBA(0x66, 0x99, 0x00, 0xff),	// 20
		PackRGBA(0x99, 0x99, 0x00, 0xff),	// 21
		PackRGBA(0xcc, 0x99, 0x00, 0xff),	// 22
		PackRGBA(0xff, 0x99, 0x00, 0xff),	// 23
		PackRGBA(0x00, 0xcc, 0x00, 0xff),	// 24
		PackRGBA(0x33, 0xcc, 0x00, 0xff),	// 25
		PackRGBA(0x66, 0xcc, 0x00, 0xff),	// 26
		PackRGBA(0x99, 0xcc, 0x00, 0xff),	// 27
		PackRGBA(0xcc, 0xcc, 0x00, 0xff),	// 28
		PackRGBA(0xff, 0xcc, 0x00, 0xff),	// 29
		PackRGBA(0x00, 0xff, 0x00, 0xff),	// 30
		PackRGBA(0x33, 0xff, 0x00, 0xff),	// 31
		PackRGBA(0x66, 0xff, 0x00, 0xff),	// 32
		PackRGBA(0x99, 0xff, 0x00, 0xff),	// 33
		PackRGBA(0xcc, 0xff, 0x00, 0xff),	// 34
		PackRGBA(0xff, 0xff, 0x00, 0xff),	// 35
		PackRGBA(0x00, 0x00, 0x33, 0xff),	// 36
		PackRGBA(0x33, 0x00, 0x33, 0xff),	// 37
		PackRGBA(0x66, 0x00, 0x33, 0xff),	// 38
		PackRGBA(0x99, 0x00, 0x33, 0xff),	// 39
		PackRGBA(0xcc, 0x00, 0x33, 0xff),	// 40
		PackRGBA(0xff, 0x00, 0x33, 0xff),	// 41
		PackRGBA(0x00, 0x33, 0x33, 0xff),	// 42
		PackRGBA(0x33, 0x33, 0x33, 0xff),	// 43
		PackRGBA(0x66, 0x33, 0x33, 0xff),	// 44
		PackRGBA(0x99, 0x33, 0x33, 0xff),	// 45
		PackRGBA(0xcc, 0x33, 0x33, 0xff),	// 46
		PackRGBA(0xff, 0x33, 0x33, 0xff),	// 47
		PackRGBA(0x00, 0x66, 0x33, 0xff),	// 48
		PackRGBA(0x33, 0x66, 0x33, 0xff),	// 49
		PackRGBA(0x66, 0x66, 0x33, 0xff),	// 50
		PackRGBA(0x99, 0x66, 0x33, 0xff),	// 51
		PackRGBA(0xcc, 0x66, 0x33, 0xff),	// 52
		PackRGBA(0xff, 0x66, 0x33, 0xff),	// 53
		PackRGBA(0x00, 0x99, 0x33, 0xff),	// 54
		PackRGBA(0x33, 0x99, 0x33, 0xff),	// 55
		PackRGBA(0x66, 0x99, 0x33, 0xff),	// 56
		PackRGBA(0x99, 0x99, 0x33, 0xff),	// 57
		PackRGBA(0xcc, 0x99, 0x33, 0xff),	// 58
		PackRGBA(0xff, 0x99, 0x33, 0xff),	// 59
		PackRGBA(0x00, 0xcc, 0x33, 0xff),	// 60
		PackRGBA(0x33, 0xcc, 0x33, 0xff),	// 61
		PackRGBA(0x66, 0xcc, 0x33, 0xff),	// 62
		PackRGBA(0x99, 0xcc, 0x33, 0xff),	// 63
		PackRGBA(0xcc, 0xcc, 0x33, 0xff),	// 64
		PackRGBA(0xff, 0xcc, 0x33, 0xff),	// 65
		PackRGBA(0x00, 0xff, 0x33, 0xff),	// 66
		PackRGBA(0x33, 0xff, 0x33, 0xff),	// 67
		PackRGBA(0x66, 0xff, 0x33, 0xff),	// 68
		PackRGBA(0x99, 0xff, 0x33, 0xff),	// 69
		PackRGBA(0xcc, 0xff, 0x33, 0xff),	// 70
		PackRGBA(0xff, 0xff, 0x33, 0xff),	// 71
		PackRGBA(0x00, 0x00, 0x66, 0xff),	// 72
		PackRGBA(0x33, 0x00, 0x66, 0xff),	// 73
		PackRGBA(0x66, 0x00, 0x66, 0xff),	// 74
		PackRGBA(0x99, 0x00, 0x66, 0xff),	// 75
		PackRGBA(0xcc, 0x00, 0x66, 0xff),	// 76
		PackRGBA(0xff, 0x00, 0x66, 0xff),	// 77
		PackRGBA(0x00, 0x33, 0x66, 0xff),	// 78
		PackRGBA(0x33, 0x33, 0x66, 0xff),	// 79
		PackRGBA(0x66, 0x33, 0x66, 0xff),	// 80
		PackRGBA(0x99, 0x33, 0x66, 0xff),	// 81
		PackRGBA(0xcc, 0x33, 0x66, 0xff),	// 82
		PackRGBA(0xff, 0x33, 0x66, 0xff),	// 83
		PackRGBA(0x00, 0x66, 0x66, 0xff),	// 84
		PackRGBA(0x33, 0x66, 0x66, 0xff),	// 85
		PackRGBA(0x66, 0x66, 0x66, 0xff),	// 86
		PackRGBA(0x99, 0x66, 0x66, 0xff),	// 87
		PackRGBA(0xcc, 0x66, 0x66, 0xff),	// 88
		PackRGBA(0xff, 0x66, 0x66, 0xff),	// 89
		PackRGBA(0x00, 0x99, 0x66, 0xff),	// 90
		PackRGBA(0x33, 0x99, 0x66, 0xff),	// 91
		PackRGBA(0x66, 0x99, 0x66, 0xff),	// 92
		PackRGBA(0x99, 0x99, 0x66, 0xff),	// 93
		PackRGBA(0xcc, 0x99, 0x66, 0xff),	// 94
		PackRGBA(0xff, 0x99, 0x66, 0xff),	// 95
		PackRGBA(0x00, 0xcc, 0x66, 0xff),	// 96
		PackRGBA(0x33, 0xcc, 0x66, 0xff),	// 97
		PackRGBA(0x66, 0xcc, 0x66, 0xff),	// 98
		PackRGBA(0x99, 0xcc, 0x66, 0xff),	// 99
		PackRGBA(0xcc, 0xcc, 0x66, 0xff),	// 100
		PackRGBA(0xff, 0xcc, 0x66, 0xff),	// 101
		PackRGBA(0x00, 0xff, 0x66, 0xff),	// 102
		PackRGBA(0x33, 0xff, 0x66, 0xff),	// 103
		PackRGBA(0x66, 0xff, 0x66, 0xff),	// 104
		PackRGBA(0x99, 0xff, 0x66, 0xff),	// 105
		PackRGBA(0xcc, 0xff, 0x66, 0xff),	// 106
		PackRGBA(0xff, 0xff, 0x66, 0xff),	// 107
		PackRGBA(0x00, 0x00, 0x99, 0xff),	// 108
		PackRGBA(0x33, 0x00, 0x99, 0xff),	// 109
		PackRGBA(0x66, 0x00, 0x99, 0xff),	// 110
		PackRGBA(0x99, 0x00, 0x99, 0xff),	// 111
		PackRGBA(0xcc, 0x00, 0x99, 0xff),	// 112
		PackRGBA(0xff, 0x00, 0x99, 0xff),	// 113
		PackRGBA(0x00, 0x33, 0x99, 0xff),	// 114
		PackRGBA(0x33, 0x33, 0x99, 0xff),	// 115
		PackRGBA(0x66, 0x33, 0x99, 0xff),	// 116
		PackRGBA(0x99, 0x33, 0x99, 0xff),	// 117
		PackRGBA(0xcc, 0x33, 0x99, 0xff),	// 118
		PackRGBA(0xff, 0x33, 0x99, 0xff),	// 119
		PackRGBA(0x00, 0x66, 0x99, 0xff),	// 120
		PackRGBA(0x33, 0x66, 0x99, 0xff),	// 121
		PackRGBA(0x66, 0x66, 0x99, 0xff),	// 122
		PackRGBA(0x99, 0x66, 0x99, 0xff),	// 123
		PackRGBA(0xcc, 0x66, 0x99, 0xff),	// 124
		PackRGBA(0xff, 0x66, 0x99, 0xff),	// 125
		PackRGBA(0x00, 0x99, 0x99, 0xff),	// 126
		PackRGBA(0x33, 0x99, 0x99, 0xff),	// 127
		PackRGBA(0x66, 0x99, 0x99, 0xff),	// 128
		PackRGBA(0x99, 0x99, 0x99, 0xff),	// 129
		PackRGBA(0xcc, 0x99, 0x99, 0xff),	// 130
		PackRGBA(0xff, 0x99, 0x99, 0xff),	// 131
		PackRGBA(0x00, 0xcc, 0x99, 0xff),	// 132
		PackRGBA(0x33, 0xcc, 0x99, 0xff),	// 133
		PackRGBA(0x66, 0xcc, 0x99, 0xff),	// 134
		PackRGBA(0x99, 0xcc, 0x99, 0xff),	// 135
		PackRGBA(0xcc, 0xcc, 0x99, 0xff),	// 136
		PackRGBA(0xff, 0xcc, 0x99, 0xff),	// 137
		PackRGBA(0x00, 0xff, 0x99, 0xff),	// 138
		PackRGBA(0x33, 0xff, 0x99, 0xff),	// 139
		PackRGBA(0x66, 0xff, 0x99, 0xff),	// 140
		PackRGBA(0x99, 0xff, 0x99, 0xff),	// 141
		PackRGBA(0xcc, 0xff, 0x99, 0xff),	// 142
		PackRGBA(0xff, 0xff, 0x99, 0xff),	// 143
		PackRGBA(0x00, 0x00, 0xcc, 0xff),	// 144
		PackRGBA(0x33, 0x00, 0xcc, 0xff),	// 145
		PackRGBA(0x66, 0x00, 0xcc, 0xff),	// 146
		PackRGBA(0x99, 0x00, 0xcc, 0xff),	// 147
		PackRGBA(0xcc, 0x00, 0xcc, 0xff),	// 148
		PackRGBA(0xff, 0x00, 0xcc, 0xff),	// 149
		PackRGBA(0x00, 0x33, 0xcc, 0xff),	// 150
		PackRGBA(0x33, 0x33, 0xcc, 0xff),	// 151
		PackRGBA(0x66, 0x33, 0xcc, 0xff),	// 152
		PackRGBA(0x99, 0x33, 0xcc, 0xff),	// 153
		PackRGBA(0xcc, 0x33, 0xcc, 0xff),	// 154
		PackRGBA(0xff, 0x33, 0xcc, 0xff),	// 155
		PackRGBA(0x00, 0x66, 0xcc, 0xff),	// 156
		PackRGBA(0x33, 0x66, 0xcc, 0xff),	// 157
		PackRGBA(0x66, 0x66, 0xcc, 0xff),	// 158
		PackRGBA(0x99, 0x66, 0xcc, 0xff),	// 159
		PackRGBA(0xcc, 0x66, 0xcc, 0xff),	// 160
		PackRGBA(0xff, 0x66, 0xcc, 0xff),	// 161
		PackRGBA(0x00, 0x99, 0xcc, 0xff),	// 162
		PackRGBA(0x33, 0x99, 0xcc, 0xff),	// 163
		PackRGBA(0x66, 0x99, 0xcc, 0xff),	// 164
		PackRGBA(0x99, 0x99, 0xcc, 0xff),	// 165
		PackRGBA(0xcc, 0x99, 0xcc, 0xff),	// 166
		PackRGBA(0xff, 0x99, 0xcc, 0xff),	// 167
		PackRGBA(0x00, 0xcc, 0xcc, 0xff),	// 168
		PackRGBA(0x33, 0xcc, 0xcc, 0xff),	// 169
		PackRGBA(0x66, 0xcc, 0xcc, 0xff),	// 170
		PackRGBA(0x99, 0xcc, 0xcc, 0xff),	// 171
		PackRGBA(0xcc, 0xcc, 0xcc, 0xff),	// 172
		PackRGBA(0xff, 0xcc, 0xcc, 0xff),	// 173
		PackRGBA(0x00, 0xff, 0xcc, 0xff),	// 174
		PackRGBA(0x33, 0xff, 0xcc, 0xff),	// 175
		PackRGBA(0x66, 0xff, 0xcc, 0xff),	// 176
		PackRGBA(0x99, 0xff, 0xcc, 0xff),	// 177
		PackRGBA(0xcc, 0xff, 0xcc, 0xff),	// 178
		PackRGBA(0xff, 0xff, 0xcc, 0xff),	// 179
		PackRGBA(0x00, 0x00, 0xff, 0xff),	// 180
		PackRGBA(0x33, 0x00, 0xff, 0xff),	// 181
		PackRGBA(0x66, 0x00, 0xff, 0xff),	// 182
		PackRGBA(0x99, 0x00, 0xff, 0xff),	// 183
		PackRGBA(0xcc, 0x00, 0xff, 0xff),	// 184
		PackRGBA(0xff, 0x00, 0xff, 0xff),	// 185
		PackRGBA(0x00, 0x33, 0xff, 0xff),	// 186
		PackRGBA(0x33, 0x33, 0xff, 0xff),	// 187
		PackRGBA(0x66, 0x33, 0xff, 0xff),	// 188
		PackRGBA(0x99, 0x33, 0xff, 0xff),	// 189
		PackRGBA(0xcc, 0x33, 0xff, 0xff),	// 190
		PackRGBA(0xff, 0x33, 0xff, 0xff),	// 191
		PackRGBA(0x00, 0x66, 0xff, 0xff),	// 192
		PackRGBA(0x33, 0x66, 0xff, 0xff),	// 193
		PackRGBA(0x66, 0x66, 0xff, 0xff),	// 194
		PackRGBA(0x99, 0x66, 0xff, 0xff),	// 195
		PackRGBA(0xcc, 0x66, 0xff, 0xff),	// 196
		PackRGBA(0xff, 0x66, 0xff, 0xff),	// 197
		PackRGBA(0x00, 0x99, 0xff, 0xff),	// 198
		PackRGBA(0x33, 0x99, 0xff, 0xff),	// 199
		PackRGBA(0x66, 0x99, 0xff, 0xff),	// 200
		PackRGBA(0x99, 0x99, 0xff, 0xff),	// 201
		PackRGBA(0xcc, 0x99, 0xff, 0xff),	// 202
		PackRGBA(0xff, 0x99, 0xff, 0xff),	// 203
		PackRGBA(0x00, 0xcc, 0xff, 0xff),	// 204
		PackRGBA(0x33, 0xcc, 0xff, 0xff),	// 205
		PackRGBA(0x66, 0xcc, 0xff, 0xff),	// 206
		PackRGBA(0x99, 0xcc, 0xff, 0xff),	// 207
		PackRGBA(0xcc, 0xcc, 0xff, 0xff),	// 208
		PackRGBA(0xff, 0xcc, 0xff, 0xff),	// 209
		PackRGBA(0x00, 0xff, 0xff, 0xff),	// 210
		PackRGBA(0x33, 0xff, 0xff, 0xff),	// 211
		PackRGBA(0x66, 0xff, 0xff, 0xff),	// 212
		PackRGBA(0x99, 0xff, 0xff, 0xff),	// 213
		PackRGBA(0xcc, 0xff, 0xff, 0xff),	// 214
		PackRGBA(0xff, 0xff, 0xff, 0xff),	// 215
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 216
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 217
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 218
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 219
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 220
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 221
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 222
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 223
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 224
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 225
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 226
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 227
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 228
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 229
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 230
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 231
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 232
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 233
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 234
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 235
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 236
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 237
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 238
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 239
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 240
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 241
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 242
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 243
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 244
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 245
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 246
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 247
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 248
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 249
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 250
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 251
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 252
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 253
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 254
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 255
	};
	return new Palette(packedTbl, 256);
}

Palette* Palette::Win256()
{
	static const UInt32 packedTbl[] = {
		PackRGBA(0x00, 0x00, 0x00, 0xff),	// 0
		PackRGBA(0x80, 0x00, 0x00, 0xff),	// 1
		PackRGBA(0x00, 0x80, 0x00, 0xff),	// 2
		PackRGBA(0x80, 0x80, 0x00, 0xff),	// 3
		PackRGBA(0x00, 0x00, 0x80, 0xff),	// 4
		PackRGBA(0x80, 0x00, 0x80, 0xff),	// 5
		PackRGBA(0x00, 0x80, 0x80, 0xff),	// 6
		PackRGBA(0xc0, 0xc0, 0xc0, 0xff),	// 7
		PackRGBA(0xc0, 0xdc, 0xc0, 0xff),	// 8
		PackRGBA(0xa6, 0xca, 0xf0, 0xff),	// 9
		PackRGBA(0x40, 0x20, 0x00, 0xff),	// 10
		PackRGBA(0x60, 0x20, 0x00, 0xff),	// 11
		PackRGBA(0x80, 0x20, 0x00, 0xff),	// 12
		PackRGBA(0xa0, 0x20, 0x00, 0xff),	// 13
		PackRGBA(0xc0, 0x20, 0x00, 0xff),	// 14
		PackRGBA(0xe0, 0x20, 0x00, 0xff),	// 15
		PackRGBA(0x00, 0x40, 0x00, 0xff),	// 16
		PackRGBA(0x20, 0x40, 0x00, 0xff),	// 17
		PackRGBA(0x40, 0x40, 0x00, 0xff),	// 18
		PackRGBA(0x60, 0x40, 0x00, 0xff),	// 19
		PackRGBA(0x80, 0x40, 0x00, 0xff),	// 20
		PackRGBA(0xa0, 0x40, 0x00, 0xff),	// 21
		PackRGBA(0xc0, 0x40, 0x00, 0xff),	// 22
		PackRGBA(0xe0, 0x40, 0x00, 0xff),	// 23
		PackRGBA(0x00, 0x60, 0x00, 0xff),	// 24
		PackRGBA(0x20, 0x60, 0x00, 0xff),	// 25
		PackRGBA(0x40, 0x60, 0x00, 0xff),	// 26
		PackRGBA(0x60, 0x60, 0x00, 0xff),	// 27
		PackRGBA(0x80, 0x60, 0x00, 0xff),	// 28
		PackRGBA(0xa0, 0x60, 0x00, 0xff),	// 29
		PackRGBA(0xc0, 0x60, 0x00, 0xff),	// 30
		PackRGBA(0xe0, 0x60, 0x00, 0xff),	// 31
		PackRGBA(0x00, 0x80, 0x00, 0xff),	// 32
		PackRGBA(0x20, 0x80, 0x00, 0xff),	// 33
		PackRGBA(0x40, 0x80, 0x00, 0xff),	// 34
		PackRGBA(0x60, 0x80, 0x00, 0xff),	// 35
		PackRGBA(0x80, 0x80, 0x00, 0xff),	// 36
		PackRGBA(0xa0, 0x80, 0x00, 0xff),	// 37
		PackRGBA(0xc0, 0x80, 0x00, 0xff),	// 38
		PackRGBA(0xe0, 0x80, 0x00, 0xff),	// 39
		PackRGBA(0x00, 0xa0, 0x00, 0xff),	// 40
		PackRGBA(0x20, 0xa0, 0x00, 0xff),	// 41
		PackRGBA(0x40, 0xa0, 0x00, 0xff),	// 42
		PackRGBA(0x60, 0xa0, 0x00, 0xff),	// 43
		PackRGBA(0x80, 0xa0, 0x00, 0xff),	// 44
		PackRGBA(0xa0, 0xa0, 0x00, 0xff),	// 45
		PackRGBA(0xc0, 0xa0, 0x00, 0xff),	// 46
		PackRGBA(0xe0, 0xa0, 0x00, 0xff),	// 47
		PackRGBA(0x00, 0xc0, 0x00, 0xff),	// 48
		PackRGBA(0x20, 0xc0, 0x00, 0xff),	// 49
		PackRGBA(0x40, 0xc0, 0x00, 0xff),	// 50
		PackRGBA(0x60, 0xc0, 0x00, 0xff),	// 51
		PackRGBA(0x80, 0xc0, 0x00, 0xff),	// 52
		PackRGBA(0xa0, 0xc0, 0x00, 0xff),	// 53
		PackRGBA(0xc0, 0xc0, 0x00, 0xff),	// 54
		PackRGBA(0xe0, 0xc0, 0x00, 0xff),	// 55
		PackRGBA(0x00, 0xe0, 0x00, 0xff),	// 56
		PackRGBA(0x20, 0xe0, 0x00, 0xff),	// 57
		PackRGBA(0x40, 0xe0, 0x00, 0xff),	// 58
		PackRGBA(0x60, 0xe0, 0x00, 0xff),	// 59
		PackRGBA(0x80, 0xe0, 0x00, 0xff),	// 60
		PackRGBA(0xa0, 0xe0, 0x00, 0xff),	// 61
		PackRGBA(0xc0, 0xe0, 0x00, 0xff),	// 62
		PackRGBA(0xe0, 0xe0, 0x00, 0xff),	// 63
		PackRGBA(0x00, 0x00, 0x40, 0xff),	// 64
		PackRGBA(0x20, 0x00, 0x40, 0xff),	// 65
		PackRGBA(0x40, 0x00, 0x40, 0xff),	// 66
		PackRGBA(0x60, 0x00, 0x40, 0xff),	// 67
		PackRGBA(0x80, 0x00, 0x40, 0xff),	// 68
		PackRGBA(0xa0, 0x00, 0x40, 0xff),	// 69
		PackRGBA(0xc0, 0x00, 0x40, 0xff),	// 70
		PackRGBA(0xe0, 0x00, 0x40, 0xff),	// 71
		PackRGBA(0x00, 0x20, 0x40, 0xff),	// 72
		PackRGBA(0x20, 0x20, 0x40, 0xff),	// 73
		PackRGBA(0x40, 0x20, 0x40, 0xff),	// 74
		PackRGBA(0x60, 0x20, 0x40, 0xff),	// 75
		PackRGBA(0x80, 0x20, 0x40, 0xff),	// 76
		PackRGBA(0xa0, 0x20, 0x40, 0xff),	// 77
		PackRGBA(0xc0, 0x20, 0x40, 0xff),	// 78
		PackRGBA(0xe0, 0x20, 0x40, 0xff),	// 79
		PackRGBA(0x00, 0x40, 0x40, 0xff),	// 80
		PackRGBA(0x20, 0x40, 0x40, 0xff),	// 81
		PackRGBA(0x40, 0x40, 0x40, 0xff),	// 82
		PackRGBA(0x60, 0x40, 0x40, 0xff),	// 83
		PackRGBA(0x80, 0x40, 0x40, 0xff),	// 84
		PackRGBA(0xa0, 0x40, 0x40, 0xff),	// 85
		PackRGBA(0xc0, 0x40, 0x40, 0xff),	// 86
		PackRGBA(0xe0, 0x40, 0x40, 0xff),	// 87
		PackRGBA(0x00, 0x60, 0x40, 0xff),	// 88
		PackRGBA(0x20, 0x60, 0x40, 0xff),	// 89
		PackRGBA(0x40, 0x60, 0x40, 0xff),	// 90
		PackRGBA(0x60, 0x60, 0x40, 0xff),	// 91
		PackRGBA(0x80, 0x60, 0x40, 0xff),	// 92
		PackRGBA(0xa0, 0x60, 0x40, 0xff),	// 93
		PackRGBA(0xc0, 0x60, 0x40, 0xff),	// 94
		PackRGBA(0xe0, 0x60, 0x40, 0xff),	// 95
		PackRGBA(0x00, 0x80, 0x40, 0xff),	// 96
		PackRGBA(0x20, 0x80, 0x40, 0xff),	// 97
		PackRGBA(0x40, 0x80, 0x40, 0xff),	// 98
		PackRGBA(0x60, 0x80, 0x40, 0xff),	// 99
		PackRGBA(0x80, 0x80, 0x40, 0xff),	// 100
		PackRGBA(0xa0, 0x80, 0x40, 0xff),	// 101
		PackRGBA(0xc0, 0x80, 0x40, 0xff),	// 102
		PackRGBA(0xe0, 0x80, 0x40, 0xff),	// 103
		PackRGBA(0x00, 0xa0, 0x40, 0xff),	// 104
		PackRGBA(0x20, 0xa0, 0x40, 0xff),	// 105
		PackRGBA(0x40, 0xa0, 0x40, 0xff),	// 106
		PackRGBA(0x60, 0xa0, 0x40, 0xff),	// 107
		PackRGBA(0x80, 0xa0, 0x40, 0xff),	// 108
		PackRGBA(0xa0, 0xa0, 0x40, 0xff),	// 109
		PackRGBA(0xc0, 0xa0, 0x40, 0xff),	// 110
		PackRGBA(0xe0, 0xa0, 0x40, 0xff),	// 111
		PackRGBA(0x00, 0xc0, 0x40, 0xff),	// 112
		PackRGBA(0x20, 0xc0, 0x40, 0xff),	// 113
		PackRGBA(0x40, 0xc0, 0x40, 0xff),	// 114
		PackRGBA(0x60, 0xc0, 0x40, 0xff),	// 115
		PackRGBA(0x80, 0xc0, 0x40, 0xff),	// 116
		PackRGBA(0xa0, 0xc0, 0x40, 0xff),	// 117
		PackRGBA(0xc0, 0xc0, 0x40, 0xff),	// 118
		PackRGBA(0xe0, 0xc0, 0x40, 0xff),	// 119
		PackRGBA(0x00, 0xe0, 0x40, 0xff),	// 120
		PackRGBA(0x20, 0xe0, 0x40, 0xff),	// 121
		PackRGBA(0x40, 0xe0, 0x40, 0xff),	// 122
		PackRGBA(0x60, 0xe0, 0x40, 0xff),	// 123
		PackRGBA(0x80, 0xe0, 0x40, 0xff),	// 124
		PackRGBA(0xa0, 0xe0, 0x40, 0xff),	// 125
		PackRGBA(0xc0, 0xe0, 0x40, 0xff),	// 126
		PackRGBA(0xe0, 0xe0, 0x40, 0xff),	// 127
		PackRGBA(0x00, 0x00, 0x80, 0xff),	// 128
		PackRGBA(0x20, 0x00, 0x80, 0xff),	// 129
		PackRGBA(0x40, 0x00, 0x80, 0xff),	// 130
		PackRGBA(0x60, 0x00, 0x80, 0xff),	// 131
		PackRGBA(0x80, 0x00, 0x80, 0xff),	// 132
		PackRGBA(0xa0, 0x00, 0x80, 0xff),	// 133
		PackRGBA(0xc0, 0x00, 0x80, 0xff),	// 134
		PackRGBA(0xe0, 0x00, 0x80, 0xff),	// 135
		PackRGBA(0x00, 0x20, 0x80, 0xff),	// 136
		PackRGBA(0x20, 0x20, 0x80, 0xff),	// 137
		PackRGBA(0x40, 0x20, 0x80, 0xff),	// 138
		PackRGBA(0x60, 0x20, 0x80, 0xff),	// 139
		PackRGBA(0x80, 0x20, 0x80, 0xff),	// 140
		PackRGBA(0xa0, 0x20, 0x80, 0xff),	// 141
		PackRGBA(0xc0, 0x20, 0x80, 0xff),	// 142
		PackRGBA(0xe0, 0x20, 0x80, 0xff),	// 143
		PackRGBA(0x00, 0x40, 0x80, 0xff),	// 144
		PackRGBA(0x20, 0x40, 0x80, 0xff),	// 145
		PackRGBA(0x40, 0x40, 0x80, 0xff),	// 146
		PackRGBA(0x60, 0x40, 0x80, 0xff),	// 147
		PackRGBA(0x80, 0x40, 0x80, 0xff),	// 148
		PackRGBA(0xa0, 0x40, 0x80, 0xff),	// 149
		PackRGBA(0xc0, 0x40, 0x80, 0xff),	// 150
		PackRGBA(0xe0, 0x40, 0x80, 0xff),	// 151
		PackRGBA(0x00, 0x60, 0x80, 0xff),	// 152
		PackRGBA(0x20, 0x60, 0x80, 0xff),	// 153
		PackRGBA(0x40, 0x60, 0x80, 0xff),	// 154
		PackRGBA(0x60, 0x60, 0x80, 0xff),	// 155
		PackRGBA(0x80, 0x60, 0x80, 0xff),	// 156
		PackRGBA(0xa0, 0x60, 0x80, 0xff),	// 157
		PackRGBA(0xc0, 0x60, 0x80, 0xff),	// 158
		PackRGBA(0xe0, 0x60, 0x80, 0xff),	// 159
		PackRGBA(0x00, 0x80, 0x80, 0xff),	// 160
		PackRGBA(0x20, 0x80, 0x80, 0xff),	// 161
		PackRGBA(0x40, 0x80, 0x80, 0xff),	// 162
		PackRGBA(0x60, 0x80, 0x80, 0xff),	// 163
		PackRGBA(0x80, 0x80, 0x80, 0xff),	// 164
		PackRGBA(0xa0, 0x80, 0x80, 0xff),	// 165
		PackRGBA(0xc0, 0x80, 0x80, 0xff),	// 166
		PackRGBA(0xe0, 0x80, 0x80, 0xff),	// 167
		PackRGBA(0x00, 0xa0, 0x80, 0xff),	// 168
		PackRGBA(0x20, 0xa0, 0x80, 0xff),	// 169
		PackRGBA(0x40, 0xa0, 0x80, 0xff),	// 170
		PackRGBA(0x60, 0xa0, 0x80, 0xff),	// 171
		PackRGBA(0x80, 0xa0, 0x80, 0xff),	// 172
		PackRGBA(0xa0, 0xa0, 0x80, 0xff),	// 173
		PackRGBA(0xc0, 0xa0, 0x80, 0xff),	// 174
		PackRGBA(0xe0, 0xa0, 0x80, 0xff),	// 175
		PackRGBA(0x00, 0xc0, 0x80, 0xff),	// 176
		PackRGBA(0x20, 0xc0, 0x80, 0xff),	// 177
		PackRGBA(0x40, 0xc0, 0x80, 0xff),	// 178
		PackRGBA(0x60, 0xc0, 0x80, 0xff),	// 179
		PackRGBA(0x80, 0xc0, 0x80, 0xff),	// 180
		PackRGBA(0xa0, 0xc0, 0x80, 0xff),	// 181
		PackRGBA(0xc0, 0xc0, 0x80, 0xff),	// 182
		PackRGBA(0xe0, 0xc0, 0x80, 0xff),	// 183
		PackRGBA(0x00, 0xe0, 0x80, 0xff),	// 184
		PackRGBA(0x20, 0xe0, 0x80, 0xff),	// 185
		PackRGBA(0x40, 0xe0, 0x80, 0xff),	// 186
		PackRGBA(0x60, 0xe0, 0x80, 0xff),	// 187
		PackRGBA(0x80, 0xe0, 0x80, 0xff),	// 188
		PackRGBA(0xa0, 0xe0, 0x80, 0xff),	// 189
		PackRGBA(0xc0, 0xe0, 0x80, 0xff),	// 190
		PackRGBA(0xe0, 0xe0, 0x80, 0xff),	// 191
		PackRGBA(0x00, 0x00, 0xc0, 0xff),	// 192
		PackRGBA(0x20, 0x00, 0xc0, 0xff),	// 193
		PackRGBA(0x40, 0x00, 0xc0, 0xff),	// 194
		PackRGBA(0x60, 0x00, 0xc0, 0xff),	// 195
		PackRGBA(0x80, 0x00, 0xc0, 0xff),	// 196
		PackRGBA(0xa0, 0x00, 0xc0, 0xff),	// 197
		PackRGBA(0xc0, 0x00, 0xc0, 0xff),	// 198
		PackRGBA(0xe0, 0x00, 0xc0, 0xff),	// 199
		PackRGBA(0x00, 0x20, 0xc0, 0xff),	// 200
		PackRGBA(0x20, 0x20, 0xc0, 0xff),	// 201
		PackRGBA(0x40, 0x20, 0xc0, 0xff),	// 202
		PackRGBA(0x60, 0x20, 0xc0, 0xff),	// 203
		PackRGBA(0x80, 0x20, 0xc0, 0xff),	// 204
		PackRGBA(0xa0, 0x20, 0xc0, 0xff),	// 205
		PackRGBA(0xc0, 0x20, 0xc0, 0xff),	// 206
		PackRGBA(0xe0, 0x20, 0xc0, 0xff),	// 207
		PackRGBA(0x00, 0x40, 0xc0, 0xff),	// 208
		PackRGBA(0x20, 0x40, 0xc0, 0xff),	// 209
		PackRGBA(0x40, 0x40, 0xc0, 0xff),	// 210
		PackRGBA(0x60, 0x40, 0xc0, 0xff),	// 211
		PackRGBA(0x80, 0x40, 0xc0, 0xff),	// 212
		PackRGBA(0xa0, 0x40, 0xc0, 0xff),	// 213
		PackRGBA(0xc0, 0x40, 0xc0, 0xff),	// 214
		PackRGBA(0xe0, 0x40, 0xc0, 0xff),	// 215
		PackRGBA(0x00, 0x60, 0xc0, 0xff),	// 216
		PackRGBA(0x20, 0x60, 0xc0, 0xff),	// 217
		PackRGBA(0x40, 0x60, 0xc0, 0xff),	// 218
		PackRGBA(0x60, 0x60, 0xc0, 0xff),	// 219
		PackRGBA(0x80, 0x60, 0xc0, 0xff),	// 220
		PackRGBA(0xa0, 0x60, 0xc0, 0xff),	// 221
		PackRGBA(0xc0, 0x60, 0xc0, 0xff),	// 222
		PackRGBA(0xe0, 0x60, 0xc0, 0xff),	// 223
		PackRGBA(0x00, 0x80, 0xc0, 0xff),	// 224
		PackRGBA(0x20, 0x80, 0xc0, 0xff),	// 225
		PackRGBA(0x40, 0x80, 0xc0, 0xff),	// 226
		PackRGBA(0x60, 0x80, 0xc0, 0xff),	// 227
		PackRGBA(0x80, 0x80, 0xc0, 0xff),	// 228
		PackRGBA(0xa0, 0x80, 0xc0, 0xff),	// 229
		PackRGBA(0xc0, 0x80, 0xc0, 0xff),	// 230
		PackRGBA(0xe0, 0x80, 0xc0, 0xff),	// 231
		PackRGBA(0x00, 0xa0, 0xc0, 0xff),	// 232
		PackRGBA(0x20, 0xa0, 0xc0, 0xff),	// 233
		PackRGBA(0x40, 0xa0, 0xc0, 0xff),	// 234
		PackRGBA(0x60, 0xa0, 0xc0, 0xff),	// 235
		PackRGBA(0x80, 0xa0, 0xc0, 0xff),	// 236
		PackRGBA(0xa0, 0xa0, 0xc0, 0xff),	// 237
		PackRGBA(0xc0, 0xa0, 0xc0, 0xff),	// 238
		PackRGBA(0xe0, 0xa0, 0xc0, 0xff),	// 239
		PackRGBA(0x00, 0xc0, 0xc0, 0xff),	// 240
		PackRGBA(0x20, 0xc0, 0xc0, 0xff),	// 241
		PackRGBA(0x40, 0xc0, 0xc0, 0xff),	// 242
		PackRGBA(0x60, 0xc0, 0xc0, 0xff),	// 243
		PackRGBA(0x80, 0xc0, 0xc0, 0xff),	// 244
		PackRGBA(0xa0, 0xc0, 0xc0, 0xff),	// 245
		PackRGBA(0xff, 0xfb, 0xf0, 0xff),	// 246
		PackRGBA(0xa0, 0xa0, 0xa4, 0xff),	// 247
		PackRGBA(0x80, 0x80, 0x80, 0xff),	// 248
		PackRGBA(0xff, 0x00, 0x00, 0xff),	// 249
		PackRGBA(0x00, 0xff, 0x00, 0xff),	// 250
		PackRGBA(0xff, 0xff, 0x00, 0xff),	// 251
		PackRGBA(0x00, 0x00, 0xff, 0xff),	// 252
		PackRGBA(0xff, 0x00, 0xff, 0xff),	// 253
		PackRGBA(0x00, 0xff, 0xff, 0xff),	// 254
		PackRGBA(0xff, 0xff, 0xff, 0xff),	// 255
	};
	return new Palette(packedTbl, 256);
}

Palette* Palette::CreateFromSymbol(const Symbol* pSymbol)
{
	if (pSymbol->IsIdentical(Gurax_Symbol(basic))) {
		return Basic();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(mono))) {
		return Mono();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(websafe))) {
		return WebSafe();
	} else if (pSymbol->IsIdentical(Gurax_Symbol(win256))) {
		return Win256();
	}
	Error::Issue(ErrorType::SymbolError, "invalid symbol for Palette");
	return nullptr;
}

void Palette::Fill(const Color& color)
{
	UInt32 packed = color.GetPacked();
	UInt32* p = _packedTbl.get();
	for (size_t i = 0; i < _n; i++, p++) *p = packed;
}

size_t Palette::LookupNearest(UInt8 r, UInt8 g, UInt8 b) const
{
	size_t idxMin = 0;
	Color color(r, g, b);
	int distMin = color.CalcDistSqu(GetColor(idxMin));
	//::printf("%d %d %d  %d %d %d  %d\n", r, g, b, GetColor(idxMin).GetR(), GetColor(idxMin).GetG(), GetColor(idxMin).GetB(), distMin);
	if (distMin == 0) return idxMin;
	for (size_t idx = 1; idx < _n; idx++) {
		int dist = color.CalcDistSqu(GetColor(idx));
		if (distMin > dist) {
			if (dist == 0) return idx;
			idxMin = idx, distMin = dist;
		}
	}
	return idxMin;
}

bool Palette::UpdateByImage(const Image& image, ShrinkMode shrinkMode)
{
	ColorSet colorSet;
	size_t idxBlank = NextBlankIndex(colorSet);
	const UInt8* pSrc = image.GetPointerC();
	size_t nPixels = image.GetMetrics().CountPixels();
	//auto scanner(Image::Scanner::LeftTopHorz(image));
	if (image.IsFormat(Image::Format::RGB)) {
		for (size_t iPixel = 0; iPixel < nPixels; iPixel++, pSrc += Image::Format::RGB.bytesPerPixel) {
			Color color(Image::PixelRGB::GetR(pSrc),
					Image::PixelRGB::GetG(pSrc), Image::PixelRGB::GetB(pSrc), 0xff);
			auto pair = colorSet.insert(color);
			if (!pair.second) {
				// nothing to do as the color already exists.
			} else if (idxBlank < _n) {
				SetColor(idxBlank, color);
				idxBlank++;
			} else {
				return false;
			}
		}
	} else { // Image::Format::RGBA
		for (size_t iPixel = 0; iPixel < nPixels; iPixel++, pSrc += Image::Format::RGBA.bytesPerPixel) {
			Color color(Image::PixelRGBA::GetR(pSrc),
					Image::PixelRGBA::GetG(pSrc), Image::PixelRGBA::GetB(pSrc), 0xff);
			auto pair = colorSet.insert(color);
			if (!pair.second) {
				// nothing to do as the color already exists.
			} else if (idxBlank < _n) {
				SetColor(idxBlank, color);
				idxBlank++;
			} else {
				return false;
			}
		}
	}
	if (shrinkMode != ShrinkMode::None) Shrink(idxBlank, shrinkMode == ShrinkMode::Align);
	return true;
}

bool Palette::UpdateByPalette(const Palette& palette, ShrinkMode shrinkMode)
{
	ColorSet colorSet;
	size_t idxBlank = NextBlankIndex(colorSet);
	for (size_t idx = 0; idx < palette.GetSize(); idx++) {
		Color color(palette.GetPacked(idx));
		auto pair = colorSet.insert(color);
		if (!pair.second) {
			// nothing to do as the color already exists.
		} else if (idxBlank < _n) {
			SetColor(idxBlank, color);
			idxBlank++;
		} else {
			return false;
		}
	}
	if (shrinkMode != ShrinkMode::None) Shrink(idxBlank, shrinkMode == ShrinkMode::Align);
	return true;
}

void Palette::ResizeBuff(size_t nEntries, size_t nEntriesToCopy)
{
	_n = nEntries;
	std::unique_ptr<UInt32[]> packedTbl(new UInt32[nEntries]);
	::memcpy(packedTbl.get(), _packedTbl.get(), sizeof(UInt32) * nEntriesToCopy);
	_packedTbl.reset(packedTbl.release());
	for (size_t idx = nEntriesToCopy; idx < nEntries; idx++) {
		_packedTbl[idx] = Color::black.GetPacked();
	}
}

void Palette::Shrink(size_t nEntries, bool alignFlag)
{
	if (!alignFlag) {
		ResizeBuff(nEntries, nEntries);
		return;
	}
	size_t nEntriesAligned = 1;
	for ( ; nEntries > nEntriesAligned; nEntriesAligned <<= 1) ;
	if (nEntriesAligned < _n) ResizeBuff(nEntriesAligned, nEntries);
}

size_t Palette::NextBlankIndex(ColorSet& colorSet) const
{
	size_t idxMax = 0;
	for (size_t idx = 0; idx < _n; idx++) {
		Color color(GetPacked(idx));
		auto pair = colorSet.insert(color);
		if (pair.second) idxMax = idx;	// determined as a unique color
	}
	return idxMax + 1;
}

bool Palette::IndexSet(const Value& valueIndex, RefPtr<Value> pValue)
{
	if (valueIndex.IsInstanceOf(VTYPE_Number)) {
		const Value_Number& valueIndexEx = dynamic_cast<const Value_Number&>(valueIndex);
		Int pos = valueIndexEx.GetNumber<Int>();
		if (pos < 0) pos += _n;
		if (0 <= pos && static_cast<size_t>(pos) < _n) {
			//valueOwner.Set(pos, pValue.release());
			return true;
		}
		//valueOwner.IssueError_IndexOutOfRange(pos);
	} else if (valueIndex.IsInstanceOf(VTYPE_Bool)) {
		const Value_Bool& valueIndexEx = dynamic_cast<const Value_Bool&>(valueIndex);
		int pos = static_cast<int>(valueIndexEx.GetBool());
		if (static_cast<size_t>(pos) < _n) {
			//valueOwner.Set(pos, pValue.release());
			return true;
		}
		//valueOwner.IssueError_IndexOutOfRange(valueIndexEx.ToString(StringStyle::Quote_NilVisible).c_str());
	} else if (valueIndex.IsInstanceOf(VTYPE_List)) {
		const Value_List& valueIndexEx = dynamic_cast<const Value_List&>(valueIndex);
		if (pValue->IsIterable()) {
			RefPtr<Iterator> pIteratorSrc(pValue->GenIterator());
			for (const Value* pValueIndexEach : valueIndexEx.GetValueOwner()) {
				RefPtr<Value> pValueEach(pIteratorSrc->NextValue());
				if (!pValueIndexEach) break;
				if (!IndexSet(*pValueIndexEach, pValueEach.release())) return false;
			}
		} else {
			for (const Value* pValueIndexEach : valueIndexEx.GetValueOwner()) {
				if (!IndexSet(*pValueIndexEach, pValue->Reference())) return false;
			}
		}
		return true;
	} else if (valueIndex.IsInstanceOf(VTYPE_Iterator)) {
		const Value_Iterator& valueIndexEx = dynamic_cast<const Value_Iterator&>(valueIndex);
		Iterator& iteratorIndex = valueIndexEx.GetIterator();
		if (pValue->IsIterable()) {
			RefPtr<Iterator> pIteratorSrc(pValue->GenIterator());
			if (iteratorIndex.IsInfinite() && pIteratorSrc->IsInfinite()) {
				Error::Issue(ErrorType::IteratorError, "infinite iterator is unacceptable");
				return false;
			}
			for (;;) {
				RefPtr<Value> pValueIndexEach(iteratorIndex.NextValue());
				if (!pValueIndexEach) break;
				RefPtr<Value> pValueEach(pIteratorSrc->NextValue());
				if (!pValueIndexEach) break;
				if (!IndexSet(*pValueIndexEach, pValueEach.release())) return false;
			}
		} else {
			if (iteratorIndex.IsInfinite()) {
				Error::Issue(ErrorType::IteratorError, "infinite iterator is unacceptable");
				return false;
			}
			for (;;) {
				RefPtr<Value> pValueIndexEach(iteratorIndex.NextValue());
				if (!pValueIndexEach) break;
				if (!IndexSet(*pValueIndexEach, pValue->Reference())) return false;
			}
		}
	} else {
		Error::Issue(ErrorType::IndexError, "number or bool value is expected for list indexing");
	}
	return false;
}

bool Palette::IndexGet(const Value& valueIndex, Value** ppValue) const
{
	return false;
}

String Palette::ToString(const StringStyle& ss) const
{
	return String().Format("Palette:%dentries", _n);
}

//------------------------------------------------------------------------------
// PaletteList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PaletteOwner
//------------------------------------------------------------------------------
void PaletteOwner::Clear()
{
	for (Palette* pPalette : *this) Palette::Delete(pPalette);
	clear();
}

}
