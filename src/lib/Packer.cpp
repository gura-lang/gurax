//==============================================================================
// Packer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

bool IsBigEndian() { return false; }

//------------------------------------------------------------------------------
// Packer
//------------------------------------------------------------------------------
template<typename T> bool PutFunc_T(Packer& packer, const Value& value, bool bigEndianFlag, bool forwardFlag)
{
	if (!value.IsType(VTYPE_Number)) {
		Error::Issue(ErrorType::TypeError, "Number value must be specified");
		return false;
	}
	if (!packer.StorePrepare(sizeof(T))) return false;
	if (bigEndianFlag) {
		packer.Store<T, true>(Value_Number::GetNumber<T>(value), forwardFlag);
	} else {
		packer.Store<T, false>(Value_Number::GetNumber<T>(value), forwardFlag);
	}
	return true;
}

template<> bool PutFunc_T<Bool>(Packer& packer, const Value& value, bool bigEndianFlag, bool forwardFlag)
{
	using T = Bool;
	if (!value.IsType(VTYPE_Bool)) {
		Error::Issue(ErrorType::TypeError, "Bool value must be specified");
		return false;
	}
	if (!packer.StorePrepare(sizeof(T))) return false;
	if (bigEndianFlag) {
		packer.Store<T, true>(Value_Bool::GetBool(value), forwardFlag);
	} else {
		packer.Store<T, false>(Value_Bool::GetBool(value), forwardFlag);
	}
	return true;
}

template<> bool PutFunc_T<Complex>(Packer& packer, const Value& value, bool bigEndianFlag, bool forwardFlag)
{
	using T = Complex;
	T num;
	if (value.IsType(VTYPE_Complex)) {
		num = Value_Complex::GetComplex(value);
	} else if (value.IsType(VTYPE_Number)) {
		num = Value_Number::GetNumber<Double>(value);
	} else {
		Error::Issue(ErrorType::TypeError, "Complex or Number value must be specified");
		return false;
	}
	if (!packer.StorePrepare(sizeof(T))) return false;
	if (bigEndianFlag) {
		packer.Store<T, true>(num, forwardFlag);
	} else {
		packer.Store<T, false>(num, forwardFlag);
	}
	return true;
}

template<typename T> bool GetFunc_T(Packer& packer, RefPtr<Value>& pValue, bool exceedErrorFlag, bool bigEndianFlag, bool forwardFlag)
{
	const UInt8* pByte = packer.ExtractPrepare(sizeof(T), forwardFlag);
	if (!pByte) {
		if (exceedErrorFlag) Error::Issue(ErrorType::RangeError, "exceeds the range");
		pValue.reset(Value::nil());
		return false;
	}
	pValue.reset(new Value_Number(bigEndianFlag? packer.Extract<T, true>(pByte) : packer.Extract<T, false>(pByte)));
	return true;
}

template<> bool GetFunc_T<Bool>(Packer& packer, RefPtr<Value>& pValue, bool exceedErrorFlag, bool bigEndianFlag, bool forwardFlag)
{
	using T = Bool;
	const UInt8* pByte = packer.ExtractPrepare(sizeof(T), forwardFlag);
	if (!pByte) {
		if (exceedErrorFlag) Error::Issue(ErrorType::RangeError, "exceeds the range");
		pValue.reset(Value::nil());
		return false;
	}
	pValue.reset(new Value_Bool(bigEndianFlag? packer.Extract<T, true>(pByte) : packer.Extract<T, false>(pByte)));
	return true;
}

template<> bool GetFunc_T<Complex>(Packer& packer, RefPtr<Value>& pValue, bool exceedErrorFlag, bool bigEndianFlag, bool forwardFlag)
{
	using T = Complex;
	const UInt8* pByte = packer.ExtractPrepare(sizeof(T), forwardFlag);
	if (!pByte) {
		if (exceedErrorFlag) Error::Issue(ErrorType::RangeError, "exceeds the range");
		pValue.reset(Value::nil());
		return false;
	}
	pValue.reset(new Value_Complex(bigEndianFlag? packer.Extract<T, true>(pByte) : packer.Extract<T, false>(pByte)));
	return true;
}

Packer::ElemType Packer::ElemType::None;
Packer::ElemType Packer::ElemType::Bool;
Packer::ElemType Packer::ElemType::Int8;
Packer::ElemType Packer::ElemType::UInt8;
Packer::ElemType Packer::ElemType::Int16;
Packer::ElemType Packer::ElemType::UInt16;
Packer::ElemType Packer::ElemType::Int32;
Packer::ElemType Packer::ElemType::UInt32;
Packer::ElemType Packer::ElemType::Int64;
Packer::ElemType Packer::ElemType::UInt64;
Packer::ElemType Packer::ElemType::Float;
Packer::ElemType Packer::ElemType::Double;
Packer::ElemType Packer::ElemType::Complex;

void Packer::Bootup()
{
	ElemType::None.pSymbol		= Gurax_Symbol(none);
	ElemType::Bool.pSymbol		= Gurax_Symbol(bool_);
	ElemType::Int8.pSymbol		= Gurax_Symbol(int8);
	ElemType::UInt8.pSymbol		= Gurax_Symbol(uint8);
	ElemType::Int16.pSymbol		= Gurax_Symbol(int16);
	ElemType::UInt16.pSymbol	= Gurax_Symbol(uint16);
	ElemType::Int32.pSymbol		= Gurax_Symbol(int32);
	ElemType::UInt32.pSymbol	= Gurax_Symbol(uint32);
	ElemType::Int64.pSymbol		= Gurax_Symbol(int64);
	ElemType::UInt64.pSymbol	= Gurax_Symbol(uint64);
	ElemType::Float.pSymbol		= Gurax_Symbol(float_);
	ElemType::Double.pSymbol	= Gurax_Symbol(double_);
	ElemType::Complex.pSymbol	= Gurax_Symbol(complex);
	ElemType::None.bytes		= 1;
	ElemType::Bool.bytes		= 1;
	ElemType::Int8.bytes		= 1;
	ElemType::UInt8.bytes		= 1;
	ElemType::Int16.bytes		= 2;
	ElemType::UInt16.bytes		= 2;
	ElemType::Int32.bytes		= 4;
	ElemType::UInt32.bytes		= 4;
	ElemType::Int64.bytes		= 8;
	ElemType::UInt64.bytes		= 8;
	ElemType::Float.bytes		= 4;
	ElemType::Double.bytes		= 8;
	ElemType::Complex.bytes		= 16;
	ElemType::None.putFunc		= PutFunc_T<Int8>;
	ElemType::None.getFunc		= GetFunc_T<Int8>;
	ElemType::Bool.putFunc		= PutFunc_T<Bool>;
	ElemType::Bool.getFunc		= GetFunc_T<Bool>;
	ElemType::Int8.putFunc		= PutFunc_T<Int8>;
	ElemType::Int8.getFunc		= GetFunc_T<Int8>;
	ElemType::UInt8.putFunc		= PutFunc_T<UInt8>;
	ElemType::UInt8.getFunc		= GetFunc_T<UInt8>;
	ElemType::Int16.putFunc		= PutFunc_T<Int16>;
	ElemType::Int16.getFunc		= GetFunc_T<Int16>;
	ElemType::UInt16.putFunc	= PutFunc_T<UInt16>;
	ElemType::UInt16.getFunc	= GetFunc_T<UInt16>;
	ElemType::Int32.putFunc		= PutFunc_T<Int32>;
	ElemType::Int32.getFunc		= GetFunc_T<Int32>;
	ElemType::UInt32.putFunc	= PutFunc_T<UInt32>;
	ElemType::UInt32.getFunc	= GetFunc_T<UInt32>;
	ElemType::Int64.putFunc		= PutFunc_T<Int64>;
	ElemType::Int64.getFunc		= GetFunc_T<Int64>;
	ElemType::UInt64.putFunc	= PutFunc_T<UInt64>;
	ElemType::UInt64.getFunc	= GetFunc_T<UInt64>;
	ElemType::Float.putFunc		= PutFunc_T<Float>;
	ElemType::Float.getFunc		= GetFunc_T<Float>;
	ElemType::Double.putFunc	= PutFunc_T<Double>;
	ElemType::Double.getFunc	= GetFunc_T<Double>;
	ElemType::Complex.putFunc	= PutFunc_T<Complex>;
	ElemType::Complex.getFunc	= GetFunc_T<Complex>;
}

bool Packer::Put(const ElemType& elemType, const Value& value, const Attribute& attr)
{
	bool bigEndianFlag = attr.IsSet(Gurax_Symbol(be));
	bool forwardFlag = attr.IsSet(Gurax_Symbol(fwd));
	return Put(elemType, value, bigEndianFlag, forwardFlag);
}

bool Packer::Get(const ElemType& elemType, RefPtr<Value>& pValue, const Attribute& attr)
{
	bool bigEndianFlag = attr.IsSet(Gurax_Symbol(be));
	bool forwardFlag = attr.IsSet(Gurax_Symbol(fwd));
	bool exceedErrorFlag = false;
	return Get(elemType, pValue, exceedErrorFlag, bigEndianFlag, forwardFlag);
}

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
			StoreBuffer(nullptr, nRepeat, true);
			nRepeat = 1;
		} else if (ch == 'c') {
			if (!StorePrepare(nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				const char* str = GetString(valListArg, ppValueArg);
				if (!str) return false;
				Store<Int8, false>(str[0], true);
			}
			nRepeat = 1;
		} else if (ch == 'b') {
			if (!StorePrepare(nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Int8 num = static_cast<Int8>(GetNumberRanged(valListArg, ppValueArg, -128, 127));
				if (Error::IsIssued()) return false;
				Store<Int8, false>(num, true);
			}
			nRepeat = 1;
		} else if (ch == 'B') {
			if (!StorePrepare(nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				UInt8 num = static_cast<UInt8>(GetNumberRanged(valListArg, ppValueArg, 0, 255));
				if (Error::IsIssued()) return false;
				Store<UInt8, false>(num, true);
			}
			nRepeat = 1;
		} else if (ch == 'h') {
			if (!StorePrepare(sizeof(Int16) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Int16 num = static_cast<Int16>(GetNumberRanged(valListArg, ppValueArg, -32768, 32767));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<Int16, true>(num, true); } else { Store<Int16, false>(num, true); }
			}
			nRepeat = 1;
		} else if (ch == 'H') {
			if (!StorePrepare(sizeof(UInt16) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				UInt16 num = static_cast<UInt16>(GetNumberRanged(valListArg, ppValueArg, 0, 65535));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<UInt16, true>(num, true); } else { Store<UInt16, false>(num, true); }
			}
			nRepeat = 1;
		} else if (ch == 'i') {
			if (!StorePrepare(sizeof(Int32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Int32 num = static_cast<Int32>(GetNumberRanged(valListArg, ppValueArg, -2147483648., 2147483647.));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<Int32, true>(num, true); } else { Store<Int32, false>(num, true); }
			}
			nRepeat = 1;
		} else if (ch == 'I') {
			if (!StorePrepare(sizeof(UInt32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				UInt32 num = static_cast<UInt32>(GetNumberRanged(valListArg, ppValueArg, 0, 4294967295.));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<UInt32, true>(num, true); } else { Store<UInt32, false>(num, true); }
			}
			nRepeat = 1;
		} else if (ch == 'l') {
			if (!StorePrepare(sizeof(Int32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Int32 num = static_cast<Int32>(GetNumberRanged(valListArg, ppValueArg, -2147483648., 2147483647.));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<Int32, true>(num, true); } else { Store<Int32, false>(num, true); }
			}
			nRepeat = 1;
		} else if (ch == 'L') {
			if (!StorePrepare(sizeof(UInt32) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				UInt32 num = static_cast<UInt32>(GetNumberRanged(valListArg, ppValueArg, 0, 4294967295.));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<UInt32, true>(num, true); } else { Store<UInt32, false>(num, true); }
			}
			nRepeat = 1;
		} else if (ch == 'q') {
			if (!StorePrepare(sizeof(Int64) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Int64 num = static_cast<Int64>(GetNumber(valListArg, ppValueArg));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<Int64, true>(num, true); } else { Store<Int64, false>(num, true); }
			}
			nRepeat = 1;
		} else if (ch == 'Q') {
			if (!StorePrepare(sizeof(UInt64) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				UInt64 num = static_cast<UInt64>(GetNumber(valListArg, ppValueArg));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<UInt64, true>(num, true); } else { Store<UInt64, false>(num, true); }
			}
			nRepeat = 1;
		} else if (ch == 'f') {
			if (!StorePrepare(sizeof(Float) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Float num = static_cast<Float>(GetNumber(valListArg, ppValueArg));
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<Float, true>(num, true); } else { Store<Float, false>(num, true); }
			}
			nRepeat = 1;
		} else if (ch == 'd') {
			if (!StorePrepare(sizeof(Double) * nRepeat)) return false;
			for (int i = 0; i < nRepeat; i++, ppValueArg++) {
				Double num = GetNumber(valListArg, ppValueArg);
				if (Error::IsIssued()) return false;
				if (bigEndianFlag) { Store<Double, true>(num, true); } else { Store<Double, false>(num, true); }
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
				Codec::Result rtn = pCodec->GetEncoder().FeedChar(*p, buffRtn, &cnt);
				if (rtn == Codec::Result::Error) {
					Error::Issue(ErrorType::CodecError,
						"encoding error. specify a proper coding name by {coding}");
					return false;
				} else if (rtn == Codec::Result::Complete) {
					for (size_t i = 0; i < cnt && nPacked < nRepeat; i++, nPacked++) {
						Store<UInt8, false>(buffRtn[i], true);
					}
				}
			}
			for ( ; nPacked < nRepeat; nPacked++) {
				Store<UInt8, false>('\0', true);
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
			const UInt8* pByte = ExtractPrepare(nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(sizeof(Int16) * nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(sizeof(UInt16) * nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(sizeof(Int32) * nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(sizeof(UInt32) * nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(sizeof(Int32) * nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(sizeof(UInt32) * nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(sizeof(Int64) * nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(sizeof(UInt64) * nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(sizeof(Float) * nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(sizeof(Double) * nRepeat, true);
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
			const UInt8* pByte = ExtractPrepare(nRepeat, true);
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
				Codec::Result rtn = pCodec->GetDecoder().FeedData(*pByte, &codeUTF32);
				if (rtn == Codec::Result::Complete) {
					if (codeUTF32 == 0) break;
					str.AppendUTF32(codeUTF32);
				} else if (rtn == Codec::Result::CompleteSingle) {
					if (codeUTF32 == 0) break;
					str += static_cast<char>(codeUTF32 & 0xff);
				} else if (rtn == Codec::Result::Error) {
					Error::Issue(ErrorType::CodecError, "decoding error. specify a proper coding name by {coding}");
					return Value::nil();
				}
			}
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
	StoreBuffer(buff, bytes, true);
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

const Packer::ElemType& Packer::SymbolToElemType(const Symbol* pSymbol)
{
	return
		pSymbol->IsIdentical(Gurax_Symbol(bool_))? 		ElemType::Bool :
		pSymbol->IsIdentical(Gurax_Symbol(int8))? 		ElemType::Int8 :
		pSymbol->IsIdentical(Gurax_Symbol(uint8))? 		ElemType::UInt8 :
		pSymbol->IsIdentical(Gurax_Symbol(int16))? 		ElemType::Int16 :
		pSymbol->IsIdentical(Gurax_Symbol(uint16))? 	ElemType::UInt16 :
		pSymbol->IsIdentical(Gurax_Symbol(int32))? 		ElemType::Int32 :
		pSymbol->IsIdentical(Gurax_Symbol(uint32))? 	ElemType::UInt32 :
		pSymbol->IsIdentical(Gurax_Symbol(int64))? 		ElemType::Int64 :
		pSymbol->IsIdentical(Gurax_Symbol(uint64))? 	ElemType::UInt64 :
		pSymbol->IsIdentical(Gurax_Symbol(float_))? 	ElemType::Float :
		pSymbol->IsIdentical(Gurax_Symbol(double_))?	ElemType::Double :
		ElemType::None;
}

}
