//==============================================================================
// Packer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Packer
//------------------------------------------------------------------------------
bool Packer::Pack(const char* format, const ValueList& valListArg)
{
#if 0
	enum {
		STAT_Format,
		STAT_Repeat,
		STAT_Encoding,
	} stat = STAT_Format;
	ValueList::const_iterator pValueArg = valListArg.begin();
	bool bigEndianFlag = IsBigEndian();
	int nRepeat = 1;
	String encoding;
	AutoPtr<Codec> pCodec(Codec::CreateCodecNone(false, false));
	for (const char *p = format; *p != '\0'; ) {
		char ch = *p;
		bool eatNextFlag = true;
		if (stat == STAT_Repeat) {
			if (IsDigit(ch)) {
				nRepeat = nRepeat * 10 + (ch - '0');
			} else {
				eatNextFlag = false;
				stat = STAT_Format;
			}
		} else if (stat == STAT_Encoding) {
			if (ch == '}') {
				if (encoding.empty()) {
					pCodec.reset(Codec::CreateCodecNone(false, false));
				} else {
					pCodec.reset(Codec::CreateCodec(sig, encoding.c_str(), false, false));
					if (sig.IsSignalled()) return false;
				}
				stat = STAT_Format;
			} else {
				encoding.push_back(ch);
			}
		} else if (IsDigit(ch)) {
			nRepeat = 0;
			eatNextFlag = false;
			stat = STAT_Repeat;
		} else if (ch == '*') {
			if (pValueArg == valListArg.end()) {
				sig.SetError(ERR_ValueError, "not enough arguments");
				return false;
			}
			if (!pValueArg->Is_number()) {
				sig.SetError(ERR_ValueError,
								"repeat specifier requires a number value");
				return false;
			}
			nRepeat = pValueArg->GetInt();
			pValueArg++;
		} else if (ch == '{') {
			encoding.clear();
			stat = STAT_Encoding;
		} else if (ch == '@') {
			bigEndianFlag = IsBigEndian();
		} else if (ch == '=') {
			bigEndianFlag = IsBigEndian();
		} else if (ch == '<') {
			bigEndianFlag = false;
		} else if (ch == '>') {
			bigEndianFlag = true;
		} else if (ch == '!') {
			bigEndianFlag = true;
		} else if (ch == 'x') {
			if (!StorePrepare(sig, nRepeat)) return false;
			StoreBuffer(nullptr, nRepeat);
			nRepeat = 1;
		} else if (ch == 'c') {
			if (!StorePrepare(sig, nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, pValueArg++) {
				if (!CheckString(env, valListArg, pValueArg)) return false;
				Store<Int8>(pValueArg->GetString()[0], false);
			}
			nRepeat = 1;
		} else if (ch == 'b') {
			if (!StorePrepare(sig, nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, pValueArg++) {
				if (!CheckNumber(env, valListArg, pValueArg, -128, 127)) return false;
				Store<Int8>(pValueArg->GetInt8(), false);
			}
			nRepeat = 1;
		} else if (ch == 'B') {
			if (!StorePrepare(sig, nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, pValueArg++) {
				if (!CheckNumber(env, valListArg, pValueArg, 0, 255)) return false;
				Store<UInt8>(pValueArg->GetUInt8(), false);
			}
			nRepeat = 1;
		} else if (ch == 'h') {
			if (!StorePrepare(sig, sizeof(Short) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, pValueArg++) {
				if (!CheckNumber(env, valListArg, pValueArg, -32768, 32767)) return false;
				Store<Short>(pValueArg->GetShort(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'H') {
			if (!StorePrepare(sig, sizeof(UInt16) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, pValueArg++) {
				if (!CheckNumber(env, valListArg, pValueArg, 0, 65535)) return false;
				Store<UInt16>(pValueArg->GetUInt16(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'i') {
			if (!StorePrepare(sig, sizeof(Int32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, pValueArg++) {
				if (!CheckNumber(env, valListArg, pValueArg, -2147483648., 2147483647.)) return false;
				Store<Int32>(pValueArg->GetInt32(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'I') {
			if (!StorePrepare(sig, sizeof(UInt32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, pValueArg++) {
				if (!CheckNumber(env, valListArg, pValueArg, 0, 4294967295.)) return false;
				Store<UInt32>(pValueArg->GetUInt32(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'l') {
			if (!StorePrepare(sig, sizeof(Int32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, pValueArg++) {
				if (!CheckNumber(env, valListArg, pValueArg, -2147483648., 2147483647.)) return false;
				Store<Int32>(pValueArg->GetInt32(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'L') {
			if (!StorePrepare(sig, sizeof(UInt32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, pValueArg++) {
				if (!CheckNumber(env, valListArg, pValueArg, 0, 4294967295.)) return false;
				Store<UInt32>(pValueArg->GetUInt32(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'q') {
			if (!StorePrepare(sig, sizeof(Int64) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, pValueArg++) {
				if (!CheckNumber(env, valListArg, pValueArg)) return false;
				Store<Int64>(pValueArg->GetInt64(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'Q') {
			if (!StorePrepare(sig, sizeof(UInt64) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, pValueArg++) {
				if (!CheckNumber(env, valListArg, pValueArg)) return false;
				Store<UInt64>(pValueArg->GetUInt64(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'f') {
			if (!StorePrepare(sig, sizeof(Float) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, pValueArg++) {
				if (!CheckNumber(env, valListArg, pValueArg)) return false;
				Store<Float>(pValueArg->GetFloat(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'd') {
			if (!StorePrepare(sig, sizeof(Double) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, pValueArg++) {
				if (!CheckNumber(env, valListArg, pValueArg)) return false;
				Store<Double>(pValueArg->GetDouble(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 's') {
			if (!StorePrepare(sig, nRepeat)) return false;
			if (!CheckString(env, valListArg, pValueArg)) return false;
			const char *p = pValueArg->GetString();
			int nPacked = 0;
			char chConv;
			for ( ; nPacked < nRepeat && *p != '\0'; p++) {
				Codec::Result result = pCodec->GetEncoder()->FeedChar(*p, chConv);
				if (result == Codec::RESULT_Error) {
					sig.SetError(ERR_CodecError,
						"encoding error. specify a proper coding name by {coding}");
					return false;
				} else if (result == Codec::RESULT_Complete) {
					Store<UInt8>(chConv, false), nPacked++;
					while (pCodec->GetEncoder()->FollowChar(chConv) && nPacked < nRepeat) {
						Store<UInt8>(chConv, false), nPacked++;
					}
				}
			}
			for ( ; nPacked < nRepeat; nPacked++) {
				Store<UInt8>('\0', false);
			}
			pValueArg++;
			nRepeat = 1;
		} else if (ch == 'p') {
			sig.SetError(ERR_ValueError, "sorry, not implemented yet");
			return false;
		} else if (ch == 'P') {
			sig.SetError(ERR_ValueError, "sorry, not implemented yet");
			return false;
		} else if (IsWhite(ch)) {
			// just ignore white characters
		} else {
			sig.SetError(ERR_ValueError, "invalid character in format");
			return false;
		}
		if (eatNextFlag) p++;
	}
#endif
	return true;
}

Value* Packer::Unpack(const char* format, const ValueList& valListArg, bool exceedErrorFlag)
{
#if 0
	enum {
		STAT_Format,
		STAT_Repeat,
		STAT_Encoding,
	} stat = STAT_Format;
	ValueList::const_iterator pValueArg = valListArg.begin();
	Value result;
	Object_list *pObjList = result.InitAsList(env);
	bool bigEndianFlag = IsBigEndian();
	int nRepeat = 1;
	String encoding;
	AutoPtr<Codec> pCodec(Codec::CreateCodecNone(false, false));
	for (const char *p = format; *p != '\0'; ) {
		char ch = *p;
		bool eatNextFlag = true;
		if (stat == STAT_Repeat) {
			if (IsDigit(ch)) {
				nRepeat = nRepeat * 10 + (ch - '0');
			} else {
				eatNextFlag = false;
				stat = STAT_Format;
			}
		} else if (stat == STAT_Encoding) {
			if (ch == '}') {
				if (encoding.empty()) {
					pCodec.reset(Codec::CreateCodecNone(false, false));
				} else {
					pCodec.reset(Codec::CreateCodec(sig, encoding.c_str(), false, false));
					if (sig.IsSignalled()) return Value::Nil;
				}
				stat = STAT_Format;
			} else {
				encoding.push_back(ch);
			}
		} else if (IsDigit(ch)) {
			nRepeat = 0;
			eatNextFlag = false;
			stat = STAT_Repeat;
		} else if (ch == '*') {
			if (pValueArg == valListArg.end()) {
				sig.SetError(ERR_ValueError, "not enough arguments");
				return false;
			}
			if (!pValueArg->Is_number()) {
				sig.SetError(ERR_ValueError,
								"repeat specifier requires a number value");
				return false;
			}
			nRepeat = pValueArg->GetInt();
			pValueArg++;
		} else if (ch == '{') {
			encoding.clear();
			stat = STAT_Encoding;
		} else if (ch == '@') {
			bigEndianFlag = IsBigEndian();
		} else if (ch == '=') {
			bigEndianFlag = IsBigEndian();
		} else if (ch == '<') {
			bigEndianFlag = false;
		} else if (ch == '>') {
			bigEndianFlag = true;
		} else if (ch == '!') {
			bigEndianFlag = true;
		} else if (ch == 'x') {
			const UInt8 *pByte = ExtractPrepare(sig, nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			nRepeat = 1;
		} else if (ch == 'c') {
			const UInt8 *pByte = ExtractPrepare(sig, nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			char str[2];
			str[1] = '\0';
			for (int i = 0; i < nRepeat; i++, pByte++) {
				str[0] = Extract<Int8>(pByte, false);
				pObjList->Add(Value(str));
			}
			nRepeat = 1;
		} else if (ch == 'b') {
			const UInt8 *pByte = ExtractPrepare(sig, nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte++) {
				pObjList->Add(Value(Extract<Int8>(pByte, false)));
			}
			nRepeat = 1;
		} else if (ch == 'B') {
			const UInt8 *pByte = ExtractPrepare(sig, nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte++) {
				pObjList->Add(Value(Extract<UInt8>(pByte, false)));
			}
			nRepeat = 1;
		} else if (ch == 'h') {
			const UInt8 *pByte = ExtractPrepare(sig, sizeof(Int16) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Short)) {
				pObjList->Add(Value(Extract<Int16>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'H') {
			const UInt8 *pByte = ExtractPrepare(sig, sizeof(UInt16) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(UInt16)) {
				pObjList->Add(Value(Extract<UInt16>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'i') {
			const UInt8 *pByte = ExtractPrepare(sig, sizeof(Int32) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Int32)) {
				pObjList->Add(Value(Extract<Int32>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'I') {
			const UInt8 *pByte = ExtractPrepare(sig, sizeof(UInt32) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(UInt32)) {
				pObjList->Add(Value(Extract<UInt32>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'l') {
			const UInt8 *pByte = ExtractPrepare(sig, sizeof(Int32) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Int32)) {
				pObjList->Add(Value(Extract<Int32>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'L') {
			const UInt8 *pByte = ExtractPrepare(sig, sizeof(UInt32) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(UInt32)) {
				pObjList->Add(Value(Extract<UInt32>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'q') {
			const UInt8 *pByte = ExtractPrepare(sig, sizeof(Int64) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Int64)) {
				pObjList->Add(Value(Extract<Int64>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'Q') {
			const UInt8 *pByte = ExtractPrepare(sig, sizeof(UInt64) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(UInt64)) {
				pObjList->Add(Value(Extract<UInt64>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'f') {
			const UInt8 *pByte = ExtractPrepare(sig, sizeof(Float) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Float)) {
				pObjList->Add(Value(Extract<Float>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'd') {
			const UInt8 *pByte = ExtractPrepare(sig, sizeof(Double) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Double)) {
				pObjList->Add(Value(Extract<Double>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 's') {
			const UInt8 *pByte = ExtractPrepare(sig, nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			String str;
			str.reserve(nRepeat);
			char chConv;
			for (int nUnpacked = 0; nUnpacked < nRepeat; nUnpacked++, pByte++) {
				Codec::Result result = pCodec->GetDecoder()->FeedChar(*pByte, chConv);
				if (result == Codec::RESULT_Error) {
					sig.SetError(ERR_CodecError,
						"decoding error. specify a proper coding name by {coding}");
					return false;
				} else if (result == Codec::RESULT_Complete) {
					str.push_back(chConv);
					while (pCodec->GetDecoder()->FollowChar(chConv)) str.push_back(chConv);
				}
			}
			// flush unprocessed characters
			if (pCodec->GetDecoder()->Flush(chConv)) while (pCodec->GetDecoder()->FollowChar(chConv)) ;
			pObjList->Add(Value(str));
			nRepeat = 1;
		} else if (ch == 'p') {
			sig.SetError(ERR_NotImplementedError, "sorry, not implemented yet");
			return Value::Nil;
		} else if (ch == 'P') {
			sig.SetError(ERR_NotImplementedError, "sorry, not implemented yet");
			return Value::Nil;
		} else if (IsWhite(ch)) {
			// just ignore white characters
		} else {
			sig.SetError(ERR_ValueError, "invalid character in format");
			return Value::Nil;
		}
		if (eatNextFlag) p++;
	}
	return result;
#endif
	return Value::nil();
}

bool Packer::PutBuffer(const void* buff, size_t bytes)
{
	if (!StorePrepare(bytes)) return false;
	StoreBuffer(buff, bytes);
	return true;
}

}
