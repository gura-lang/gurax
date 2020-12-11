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
	auto GetString = [](const ValueList& valListArg, ValueList::const_iterator ppValueArg) -> const char* {
		if (ppValueArg == valListArg.end()) {
			Error::Issue(ErrorType::ValueError, "not enough argument");
			return nullptr;
		}
		if (!(*ppValueArg)->IsType(VTYPE_String)) {
			Error::Issue(ErrorType::ValueError, "must be a String");
			return nullptr;
		}
		return Value_String::GetString(**ppValueArg);
	};
	auto GetNumber = [](const ValueList& valListArg, ValueList::const_iterator ppValueArg) -> Double {
		if (ppValueArg == valListArg.end()) {
			Error::Issue(ErrorType::ValueError, "not enough argument");
			return 0;
		}
		if (!(*ppValueArg)->IsType(VTYPE_Number)) {
			Error::Issue(ErrorType::ValueError, "must be a Number");
			return 0;
		}
		return Value_Number::GetNumber<Double>(**ppValueArg);
	};
	auto GetNumberRanged = [](const ValueList& valListArg, ValueList::const_iterator ppValueArg,
								Double numMin, Double numMax) -> Double {
		if (ppValueArg == valListArg.end()) {
			Error::Issue(ErrorType::ValueError, "not enough argument");
			return 0;
		}
		if (!(*ppValueArg)->IsType(VTYPE_Number)) {
			Error::Issue(ErrorType::ValueError, "must be a Number");
			return 0;
		}
		return Value_Number::GetNumberRanged<Double>(**ppValueArg, numMin, numMax);
	};
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
				const char* str = GetString(valListArg, ppValueArg);
				if (!str) return false;
				Store<Int8, false>(str[0]);
			}
			nRepeat = 1;
		} else if (ch == 'b') {
			if (!StorePrepare(nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Int8 num = static_cast<Int8>(GetNumberRanged(valListArg, ppValueArg, -128, 127));
				if (Error::IsIssued()) return false;
				Store<Int8, false>(num);
			}
			nRepeat = 1;
		} else if (ch == 'B') {
			if (!StorePrepare(nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				UInt8 num = static_cast<UInt8>(GetNumberRanged(valListArg, ppValueArg, 0, 255));
				if (Error::IsIssued()) return false;
				Store<UInt8, false>(num);
			}
			nRepeat = 1;
		} else if (ch == 'h') {
			if (!StorePrepare(sizeof(Int16) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Int16 num = static_cast<Int16>(GetNumberRanged(valListArg, ppValueArg, -32768, 32767));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<Int16, true>(num); } else { Store<Int16, false>(num); }
			}
			nRepeat = 1;
		} else if (ch == 'H') {
			if (!StorePrepare(sizeof(UInt16) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				UInt16 num = static_cast<UInt16>(GetNumberRanged(valListArg, ppValueArg, 0, 65535));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<UInt16, true>(num); } else { Store<UInt16, false>(num); }
			}
			nRepeat = 1;
		} else if (ch == 'i') {
			if (!StorePrepare(sizeof(Int32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Int32 num = static_cast<Int32>(GetNumberRanged(valListArg, ppValueArg, -2147483648., 2147483647.));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<Int32, true>(num); } else { Store<Int32, false>(num); }
			}
			nRepeat = 1;
		} else if (ch == 'I') {
			if (!StorePrepare(sizeof(UInt32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				UInt32 num = static_cast<UInt32>(GetNumberRanged(valListArg, ppValueArg, 0, 4294967295.));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<UInt32, true>(num); } else { Store<UInt32, false>(num); }
			}
			nRepeat = 1;
		} else if (ch == 'l') {
			if (!StorePrepare(sizeof(Int32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Int32 num = static_cast<Int32>(GetNumberRanged(valListArg, ppValueArg, -2147483648., 2147483647.));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<Int32, true>(num); } else { Store<Int32, false>(num); }
			}
			nRepeat = 1;
		} else if (ch == 'L') {
			if (!StorePrepare(sizeof(UInt32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				UInt32 num = static_cast<UInt32>(GetNumberRanged(valListArg, ppValueArg, 0, 4294967295.));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<UInt32, true>(num); } else { Store<UInt32, false>(num); }
			}
			nRepeat = 1;
		} else if (ch == 'q') {
			if (!StorePrepare(sizeof(Int64) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Int64 num = static_cast<Int64>(GetNumber(valListArg, ppValueArg));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<Int64, true>(num); } else { Store<Int64, false>(num); }
			}
			nRepeat = 1;
		} else if (ch == 'Q') {
			if (!StorePrepare(sizeof(UInt64) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				UInt64 num = static_cast<UInt64>(GetNumber(valListArg, ppValueArg));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<UInt64, true>(num); } else { Store<UInt64, false>(num); }
			}
			nRepeat = 1;
		} else if (ch == 'f') {
			if (!StorePrepare(sizeof(Float) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Float num = static_cast<Float>(GetNumber(valListArg, ppValueArg));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<Float, true>(num); } else { Store<Float, false>(num); }
			}
			nRepeat = 1;
		} else if (ch == 'd') {
			if (!StorePrepare(sizeof(Double) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Double num = GetNumber(valListArg, ppValueArg);
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<Double, true>(num); } else { Store<Double, false>(num); }
			}
			nRepeat = 1;
		} else if (ch == 's') {
			if (!StorePrepare(nRepeat)) return false;
			const char* str = GetString(valListArg, ppValueArg);
			if (!str) return false;
			int nPacked = 0;
			UInt8 buffRtn[Codec::Encoder::BuffSize];
			size_t cnt = 0;
			for (const char* p = str; nPacked < nRepeat && *p; p++) {
				Codec::Result result = pCodec->GetEncoder().FeedChar(*p, buffRtn, &cnt);
				if (result == Codec::Result::Error) {
					Error::Issue(ErrorType::CodecError,
						"encoding error. specify a proper coding name by {coding}");
					return false;
				} else if (result == Codec::Result::Complete) {
					for (size_t i = 0; i < cnt && nPacked < nRepeat; i++, nPacked++) {
						Store<UInt8, false>(buffRtn[i]);
					}
				}
			}
			for ( ; nPacked < nRepeat; nPacked++) {
				Store<UInt8, false>('\0');
			}
			ppValueArg++;
			nRepeat = 1;
		} else if (ch == 'p') {
			Error::Issue(ErrorType::UnimplementedError, "sorry, not implemented yet");
			return false;
		} else if (ch == 'P') {
			Error::Issue(ErrorType::UnimplementedError, "sorry, not implemented yet");
			return false;
		} else if (String::IsWhite(ch)) {
			// just ignore white characters
		} else {
			Error::Issue(ErrorType::FormatError, "invalid character in format");
			return false;
		}
		if (eatNextFlag) p++;
	}
	return true;
}

Value* Packer::Unpack(const char* format, const ValueList& valListArg, bool exceedErrorFlag)
{
	auto IssueError_ExceedRange = []() {
		Error::Issue(ErrorType::RangeError, "exceeds the range");
	};
	enum class Stat { Format, Repeat, Encoding } stat = Stat::Format;
	auto ppValueArg = valListArg.begin();
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
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
					if (!pCodec) return Value::nil();
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
				return Value::nil();
			}
			if (!(*ppValueArg)->IsType(VTYPE_Number)) {
				Error::Issue(ErrorType::ValueError, "repeat specifier requires a number value");
				return Value::nil();
			}
			nRepeat = Value_Number::GetNumberNonNeg<int>(**ppValueArg);
			if (Error::IsIssued()) return Value::nil();
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
			const UInt8* pByte = ExtractPrepare(nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			nRepeat = 1;
		} else if (ch == 'c') {
			const UInt8* pByte = ExtractPrepare(nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			char str[2];
			str[1] = '\0';
			for (int i = 0; i < nRepeat; i++, pByte++) {
				str[0] = Extract<Int8, false>(pByte);
				pValueOwner->Add(new Value_String(str));
			}
			nRepeat = 1;
		} else if (ch == 'b') {
			const UInt8* pByte = ExtractPrepare(nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			for (int i = 0; i < nRepeat; i++, pByte++) {
				Int8 num = Extract<Int8, false>(pByte);
				pValueOwner->Add(new Value_Number(num));
			}
			nRepeat = 1;
		} else if (ch == 'B') {
			const UInt8* pByte = ExtractPrepare(nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			for (int i = 0; i < nRepeat; i++, pByte++) {
				UInt8 num = Extract<UInt8, false>(pByte);
				pValueOwner->Add(new Value_Number(num));
			}
			nRepeat = 1;
		} else if (ch == 'h') {
			const UInt8* pByte = ExtractPrepare(sizeof(Int16) * nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Int16)) {
				Int16 num = bigEndianFlag? Extract<Int16, true>(pByte) : Extract<Int16, false>(pByte);
				pValueOwner->Add(new Value_Number(num));
			}
			nRepeat = 1;
		} else if (ch == 'H') {
			const UInt8* pByte = ExtractPrepare(sizeof(UInt16) * nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(UInt16)) {
				UInt16 num = bigEndianFlag? Extract<UInt16, true>(pByte) : Extract<UInt16, false>(pByte);
				pValueOwner->Add(new Value_Number(num));
			}
			nRepeat = 1;
		} else if (ch == 'i') {
			const UInt8* pByte = ExtractPrepare(sizeof(Int32) * nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Int32)) {
				Int32 num = bigEndianFlag? Extract<Int32, true>(pByte) : Extract<Int32, false>(pByte);
				pValueOwner->Add(new Value_Number(num));
			}
			nRepeat = 1;
		} else if (ch == 'I') {
			const UInt8* pByte = ExtractPrepare(sizeof(UInt32) * nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(UInt32)) {
				UInt32 num = bigEndianFlag? Extract<UInt32, true>(pByte) : Extract<UInt32, false>(pByte);
				pValueOwner->Add(new Value_Number(num));
			}
			nRepeat = 1;
		} else if (ch == 'l') {
			const UInt8* pByte = ExtractPrepare(sizeof(Int32) * nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Int32)) {
				Int32 num = bigEndianFlag? Extract<Int32, true>(pByte) : Extract<Int32, false>(pByte);
				pValueOwner->Add(new Value_Number(num));
			}
			nRepeat = 1;
		} else if (ch == 'L') {
			const UInt8* pByte = ExtractPrepare(sizeof(UInt32) * nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(UInt32)) {
				UInt32 num = bigEndianFlag? Extract<UInt32, true>(pByte) : Extract<UInt32, false>(pByte);
				pValueOwner->Add(new Value_Number(num));
			}
			nRepeat = 1;
		} else if (ch == 'q') {
			const UInt8* pByte = ExtractPrepare(sizeof(Int64) * nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Int64)) {
				Int64 num = bigEndianFlag? Extract<Int64, true>(pByte) : Extract<Int64, false>(pByte);
				pValueOwner->Add(new Value_Number(num));
			}
			nRepeat = 1;
		} else if (ch == 'Q') {
			const UInt8* pByte = ExtractPrepare(sizeof(UInt64) * nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(UInt64)) {
				UInt64 num = bigEndianFlag? Extract<UInt64, true>(pByte) : Extract<UInt64, false>(pByte);
				pValueOwner->Add(new Value_Number(num));
			}
			nRepeat = 1;
		} else if (ch == 'f') {
			const UInt8* pByte = ExtractPrepare(sizeof(Float) * nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Float)) {
				Float num = bigEndianFlag? Extract<Float, true>(pByte) : Extract<Float, false>(pByte);
				pValueOwner->Add(new Value_Number(num));
			}
			nRepeat = 1;
		} else if (ch == 'd') {
			const UInt8* pByte = ExtractPrepare(sizeof(Double) * nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			for (int i = 0; i < nRepeat; i++, pByte += sizeof(Double)) {
				Float num = bigEndianFlag? Extract<Double, true>(pByte) : Extract<Double, false>(pByte);
				pValueOwner->Add(new Value_Number(num));
			}
			nRepeat = 1;
		} else if (ch == 's') {
			const UInt8* pByte = ExtractPrepare(nRepeat);
			if (pByte) {
				// nothing to do
			} else if (exceedErrorFlag) {
				IssueError_ExceedRange();
				return Value::nil();
			} else {
				break;
			}
			String str;
			str.reserve(nRepeat);
			UInt32 codeUTF32 = 0;
			for (int nUnpacked = 0; nUnpacked < nRepeat; nUnpacked++, pByte++) {
				Codec::Result result = pCodec->GetDecoder().FeedData(*pByte, &codeUTF32);
				if (result == Codec::Result::Error) {
					Error::Issue(ErrorType::CodecError, "decoding error. specify a proper coding name by {coding}");
					return Value::nil();
				} else if (result == Codec::Result::Complete) {
					str.AppendUTF32(codeUTF32);
				}
			}
			// flush unprocessed characters
			//if (pCodec->GetDecoder().Flush(chConv)) while (pCodec->GetDecoder().FollowChar(chConv)) ;
			pValueOwner->Add(new Value_String(str));
			nRepeat = 1;
		} else if (ch == 'p') {
			Error::Issue(ErrorType::UnimplementedError, "sorry, not implemented yet");
			return Value::nil();
		} else if (ch == 'P') {
			Error::Issue(ErrorType::UnimplementedError, "sorry, not implemented yet");
			return Value::nil();
		} else if (String::IsWhite(ch)) {
			// just ignore white characters
		} else {
			Error::Issue(ErrorType::FormatError, "invalid character in format");
			return Value::nil();
		}
		if (eatNextFlag) p++;
	}
	return pValueOwner->empty()? Value::nil() : new Value_List(pValueOwner.release());
}

bool Packer::PutBuffer(const void* buff, size_t bytes)
{
	if (!StorePrepare(bytes)) return false;
	StoreBuffer(buff, bytes);
	return true;
}

bool Packer::PutPointer(const Pointer& pointer)
{
	return PutBuffer(pointer.GetPointerC<void>(), pointer.GetBytesAvailable());
}

bool Packer::PutPointer(const Pointer& pointer, size_t bytes)
{
	return PutBuffer(pointer.GetPointerC<void>(), bytes);
}

}
