//==============================================================================
// Packer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

bool IsBigEndian() { return false; }

//------------------------------------------------------------------------------
// Packer
//------------------------------------------------------------------------------
bool Packer::Pack(const char* format, const ValueList& valListArg)
{
	auto CheckString = [](const ValueList& valListArg, ValueList::const_iterator ppValueArg) {
		if (ppValueArg == valListArg.end()) {
			Error::Issue(ErrorType::ValueError, "not enough argument");
			return false;
		}
		if (!(*ppValueArg)->IsType(VTYPE_String)) {
			Error::Issue(ErrorType::ValueError, "must be a string");
			return false;
		}
		return true;
	};
#if 1
	enum class Stat { Format, Repeat, Encoding } stat = Stat::Format;
	auto ppValueArg = valListArg.begin();
	bool bigEndianFlag = IsBigEndian();
	int nRepeat = 1;
	String encoding;
	RefPtr<Codec> pCodec(Codec::CreateDumb(false, false));
	for (const char* p = format; *p; ) {
		char ch = *p;
		bool eatNextFlag = true;
		if (stat == Stat::Repeat) {
			if (String::IsDigit(ch)) {
				nRepeat = nRepeat * 10 + (ch - '0');
			} else {
				eatNextFlag = false;
				stat = Stat::Format;
			}
		} else if (stat == Stat::Encoding) {
			if (ch == '}') {
				if (encoding.empty()) {
					pCodec.reset(Codec::CreateDumb(false, false));
				} else {
					pCodec.reset(Codec::Create(encoding.c_str(), false, false));
					if (!pCodec) return false;
				}
				stat = Stat::Format;
			} else {
				encoding.push_back(ch);
			}
		} else if (String::IsDigit(ch)) {
			nRepeat = 0;
			eatNextFlag = false;
			stat = Stat::Repeat;
		} else if (ch == '*') {
			if (ppValueArg == valListArg.end()) {
				Error::Issue(ErrorType::ValueError, "not enough arguments");
				return false;
			}
			if (!(*ppValueArg)->IsType(VTYPE_Number)) {
				Error::Issue(ErrorType::ValueError, "repeat specifier requires a number value");
				return false;
			}
			nRepeat = Value_Number::GetNumberNonNeg<int>(**ppValueArg);
			if (Error::IsIssued()) return false;
			ppValueArg++;
		} else if (ch == '{') {
			encoding.clear();
			stat = Stat::Encoding;
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
			if (!StorePrepare(nRepeat)) return false;
			StoreBuffer(nullptr, nRepeat);
			nRepeat = 1;
		} else if (ch == 'c') {
			if (!StorePrepare(nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				if (!CheckString(valListArg, ppValueArg)) return false;
				Store<Int8, false>(Value_String::GetString(**ppValueArg)[0]);
			}
			nRepeat = 1;
#if 0
		} else if (ch == 'b') {
			if (!StorePrepare(nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				if (!CheckNumber(env, valListArg, *ppValueArg, -128, 127)) return false;
				Store<Int8>((*ppValueArg)->GetInt8(), false);
			}
			nRepeat = 1;
		} else if (ch == 'B') {
			if (!StorePrepare(nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				if (!CheckNumber(env, valListArg, ppValueArg, 0, 255)) return false;
				Store<UInt8>((*ppValueArg)->GetUInt8(), false);
			}
			nRepeat = 1;
		} else if (ch == 'h') {
			if (!StorePrepare(sizeof(Short) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				if (!CheckNumber(env, valListArg, ppValueArg, -32768, 32767)) return false;
				Store<Short>((*ppValueArg)->GetShort(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'H') {
			if (!StorePrepare(sizeof(UInt16) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				if (!CheckNumber(env, valListArg, ppValueArg, 0, 65535)) return false;
				Store<UInt16>((*ppValueArg)->GetUInt16(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'i') {
			if (!StorePrepare(sizeof(Int32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				if (!CheckNumber(env, valListArg, ppValueArg, -2147483648., 2147483647.)) return false;
				Store<Int32>((*ppValueArg)->GetInt32(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'I') {
			if (!StorePrepare(sizeof(UInt32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				if (!CheckNumber(env, valListArg, ppValueArg, 0, 4294967295.)) return false;
				Store<UInt32>((*ppValueArg)->GetUInt32(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'l') {
			if (!StorePrepare(sizeof(Int32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				if (!CheckNumber(env, valListArg, ppValueArg, -2147483648., 2147483647.)) return false;
				Store<Int32>((*ppValueArg)->GetInt32(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'L') {
			if (!StorePrepare(sizeof(UInt32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				if (!CheckNumber(env, valListArg, ppValueArg, 0, 4294967295.)) return false;
				Store<UInt32>((*ppValueArg)->GetUInt32(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'q') {
			if (!StorePrepare(sizeof(Int64) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				if (!CheckNumber(env, valListArg, ppValueArg)) return false;
				Store<Int64>((*ppValueArg)->GetInt64(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'Q') {
			if (!StorePrepare(sizeof(UInt64) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				if (!CheckNumber(env, valListArg, ppValueArg)) return false;
				Store<UInt64>((*ppValueArg)->GetUInt64(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'f') {
			if (!StorePrepare(sizeof(Float) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				if (!CheckNumber(env, valListArg, ppValueArg)) return false;
				Store<Float>((*ppValueArg)->GetFloat(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 'd') {
			if (!StorePrepare(sizeof(Double) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				if (!CheckNumber(env, valListArg, ppValueArg)) return false;
				Store<Double>((*ppValueArg)->GetDouble(), bigEndianFlag);
			}
			nRepeat = 1;
		} else if (ch == 's') {
			if (!StorePrepare(nRepeat)) return false;
			if (!CheckString(env, valListArg, ppValueArg)) return false;
			const char* p = (*ppValueArg)->GetString();
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
			ppValueArg++;
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
#endif
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
		Stat::Format,
		Stat::Repeat,
		Stat::Encoding,
	} stat = Stat::Format;
	ValueList::const_iterator pValueArg = valListArg.begin();
	Value result;
	Object_list* pObjList = result.InitAsList(env);
	bool bigEndianFlag = IsBigEndian();
	int nRepeat = 1;
	String encoding;
	AutoPtr<Codec> pCodec(Codec::CreateCodecNone(false, false));
	for (const char* p = format; *p != '\0'; ) {
		char ch = *p;
		bool eatNextFlag = true;
		if (stat == Stat::Repeat) {
			if (IsDigit(ch)) {
				nRepeat = nRepeat * 10 + (ch - '0');
			} else {
				eatNextFlag = false;
				stat = Stat::Format;
			}
		} else if (stat == Stat::Encoding) {
			if (ch == '}') {
				if (encoding.empty()) {
					pCodec.reset(Codec::CreateCodecNone(false, false));
				} else {
					pCodec.reset(Codec::CreateCodec(encoding.c_str(), false, false));
					if (sig.IsSignalled()) return Value::Nil;
				}
				stat = Stat::Format;
			} else {
				encoding.push_back(ch);
			}
		} else if (IsDigit(ch)) {
			nRepeat = 0;
			eatNextFlag = false;
			stat = Stat::Repeat;
		} else if (ch == '*') {
			if (pValueArg == valListArg.end()) {
				sig.SetError(ERR_ValueError, "not enough arguments");
				return false;
			}
			if (!(*ppValueArg)->Is_number()) {
				sig.SetError(ERR_ValueError,
								"repeat specifier requires a number value");
				return false;
			}
			nRepeat = (*ppValueArg)->GetInt();
			pValueArg++;
		} else if (ch == '{') {
			encoding.clear();
			stat = Stat::Encoding;
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
			const UInt8* pByte = ExtractPrepare(nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			nRepeat = 1;
		} else if (ch == 'c') {
			const UInt8* pByte = ExtractPrepare(nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			char str[2];
			str[1] = '\0';
			for (int i = 0; i < nRepeat; i++, pByte++) {
				str[0] = Extract<Int8>(pByte, false);
				pObjList->Add(Value(str));
			}
			nRepeat = 1;
		} else if (ch == 'b') {
			const UInt8* pByte = ExtractPrepare(nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte++) {
				pObjList->Add(Value(Extract<Int8>(pByte, false)));
			}
			nRepeat = 1;
		} else if (ch == 'B') {
			const UInt8* pByte = ExtractPrepare(nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte++) {
				pObjList->Add(Value(Extract<UInt8>(pByte, false)));
			}
			nRepeat = 1;
		} else if (ch == 'h') {
			const UInt8* pByte = ExtractPrepare(sizeof(Int16) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Short)) {
				pObjList->Add(Value(Extract<Int16>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'H') {
			const UInt8* pByte = ExtractPrepare(sizeof(UInt16) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(UInt16)) {
				pObjList->Add(Value(Extract<UInt16>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'i') {
			const UInt8* pByte = ExtractPrepare(sizeof(Int32) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Int32)) {
				pObjList->Add(Value(Extract<Int32>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'I') {
			const UInt8* pByte = ExtractPrepare(sizeof(UInt32) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(UInt32)) {
				pObjList->Add(Value(Extract<UInt32>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'l') {
			const UInt8* pByte = ExtractPrepare(sizeof(Int32) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Int32)) {
				pObjList->Add(Value(Extract<Int32>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'L') {
			const UInt8* pByte = ExtractPrepare(sizeof(UInt32) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(UInt32)) {
				pObjList->Add(Value(Extract<UInt32>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'q') {
			const UInt8* pByte = ExtractPrepare(sizeof(Int64) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Int64)) {
				pObjList->Add(Value(Extract<Int64>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'Q') {
			const UInt8* pByte = ExtractPrepare(sizeof(UInt64) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(UInt64)) {
				pObjList->Add(Value(Extract<UInt64>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'f') {
			const UInt8* pByte = ExtractPrepare(sizeof(Float) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Float)) {
				pObjList->Add(Value(Extract<Float>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 'd') {
			const UInt8* pByte = ExtractPrepare(sizeof(Double) * nRepeat, exceedErrorFlag);
			if (pByte == nullptr) return Value::Nil;
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Double)) {
				pObjList->Add(Value(Extract<Double>(pByte, bigEndianFlag)));
			}
			nRepeat = 1;
		} else if (ch == 's') {
			const UInt8* pByte = ExtractPrepare(nRepeat, exceedErrorFlag);
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
