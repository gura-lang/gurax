//==============================================================================
// Tag.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Tag
//------------------------------------------------------------------------------
Tag::Tag(UInt16 tagId, UInt16 typeId, const Symbol* pSymbol) :
	_tagId(tagId), _typeId(typeId), _pSymbol(pSymbol), _posPointer(0), _orderHint(0),
	_pValue(Value::nil()), _pValueCooked(Value::nil())
{
}

Tag* Tag::Create(const Symbol* pSymbolOfIFD, const Symbol* pSymbol)
{
	const TagInfo* pTagInfo = TagInfo::LookupBySymbol(pSymbolOfIFD, pSymbol);
	if (!pTagInfo) {
		Error::Issue(ErrorType::SymbolError, "invalid symbol: %s", pSymbol->GetName());
		return nullptr;
	}
	//return Tag::Create(pTagInfo->tagId, pTagInfo->typeId, Symbol::Add(pTagInfo->name));
	return Tag::Create(pTagInfo->tagId, pTagInfo->typeId, pSymbol);
}

Tag* Tag::Create(UInt16 tagId, UInt16 typeId, const Symbol* pSymbol)
{
#if 0
	if (pTagInfo && pTagInfo->nameForIFD) {
		return new Tag_IFD(tagId, Symbol::Add(pTagInfo->nameForIFD));
	}
	const Symbol* pSymbol = pTagInfo? Symbol::Add(pTagInfo->name) : Symbol::Empty;
	if (tagId == TagId::JPEGInterchangeFormat) {
		return new Tag_JPEGInterchangeFormat(pSymbol);
	}
#endif
	switch (typeId) {
	case TypeId::BYTE: return new Tag_BYTE(tagId, pSymbol);
	case TypeId::ASCII: return new Tag_ASCII(tagId, pSymbol);
	case TypeId::SHORT: return new Tag_SHORT(tagId, pSymbol);
	case TypeId::LONG: return new Tag_LONG(tagId, pSymbol);
	case TypeId::RATIONAL: return new Tag_RATIONAL(tagId, pSymbol);
	case TypeId::UNDEFINED: return new Tag_UNDEFINED(tagId, pSymbol);
	case TypeId::SLONG: return new Tag_SLONG(tagId, pSymbol);
	case TypeId::SRATIONAL: return new Tag_SRATIONAL(tagId, pSymbol);
	case TypeId::JPEGInterchangeFormat: return new Tag_JPEGInterchangeFormat(pSymbol);
	case TypeId::IFD: return new Tag_IFD(tagId, pSymbol);
	default: break;
	}
	IssueError_InvalidFormat();
	return nullptr;
}

bool Tag::CheckRangedNumber(const Value& value, Double numMin, Double numMax) const
{
	auto CheckSub = [this, numMin, numMax](const Value& value) {
		if (!value.IsType(VTYPE_Number)) return false;
		Double num = Value_Number::GetNumber<Double>(value);
		return numMin <= num && num <= numMax;
	};
	if (!value.IsType(VTYPE_List)) return CheckSub(value);
	for (const Value* pValue : Value_List::GetValueOwner(value)) {
		if (!CheckSub(value)) return false;
	}
	return true;
};

String Tag::ToString(const StringStyle& ss) const
{
	return String().Format("jpeg.Tag:%s:%s:%s", _pSymbol->GetName(),
		TypeIdToSymbol(_typeId)->GetName(), _pValue->ToString(ss).c_str());
}

//------------------------------------------------------------------------------
// Tag_BYTE
//------------------------------------------------------------------------------
VType& Tag_BYTE::GetVTypeAcceptable()
{
	return VTYPE_Binary;
}

bool Tag_BYTE::AssignValue(RefPtr<Value> pValue)
{
	if (!pValue->IsType(VTYPE_Binary)) {
		Error::Issue(ErrorType::TypeError, "Binary value is expected for %s",
			GetSymbol()->GetName());
		return false;
	}
	SetValue(pValue.release());
	return true;
}

template<typename TypeDef> bool Tag_BYTE::DoSerialize(Binary& buff, TagList& tagsPointed)
{
	const Binary& buffSrc = Value_Binary::GetBinary(GetValue());
	UInt32 count = static_cast<UInt32>(buffSrc.size());
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	if (count <= 4) {
		::memcpy(tagPacked.variable.BYTE, buffSrc.data(), count);
	} else {
		_posPointer = CalcPosPointer(buff);
		tagsPointed.push_back(this);
	}
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_BYTE::DoDeserialize(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	const UInt8* pBuff = variable.BYTE;
	if (count > 4) {
		UInt32 offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
		_orderHint = offsetToValue;
		if (offsetToValue + count * sizeof(UInt8) > bytesBuff) {
			IssueError_InvalidFormat();
			return false;
		}
		pBuff = buff + offsetToValue;
	}
	SetValue(new Value_Binary(Binary(pBuff, count)));
	return true;
}

template<typename TypeDef> bool Tag_BYTE::DoSerializePointed(Binary& buff)
{
	ReplaceLONG<TypeDef>(buff, _posPointer, CalcOffset(buff));
	const Binary& buffSrc = Value_Binary::GetBinary(GetValue());
	buff.append(buffSrc);
	return true;
}

bool Tag_BYTE::Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag)
{
	return beFlag? DoDeserialize<TypeDef_BE>(buff, bytesBuff, offset) :
					DoDeserialize<TypeDef_LE>(buff, bytesBuff, offset);
}

bool Tag_BYTE::Serialize(Binary& buff, bool beFlag, TagList& tagsPointed)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff, tagsPointed) : DoSerialize<TypeDef_LE>(buff, tagsPointed);
}

bool Tag_BYTE::SerializePointed(Binary& buff, bool beFlag)
{
	return beFlag? DoSerializePointed<TypeDef_BE>(buff) : DoSerializePointed<TypeDef_LE>(buff);
}

//------------------------------------------------------------------------------
// Tag_ASCII
//------------------------------------------------------------------------------
VType& Tag_ASCII::GetVTypeAcceptable()
{
	return VTYPE_String;
}

bool Tag_ASCII::AssignValue(RefPtr<Value> pValue)
{
	if (!pValue->IsType(VTYPE_String)) {
		Error::Issue(ErrorType::TypeError, "String value is expected for %s", GetSymbol()->GetName());
		return false;
	}
	SetValue(pValue.release());
	return true;
}

template<typename TypeDef> bool Tag_ASCII::DoDeserialize(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	const char* pBuff = variable.ASCII;
	if (count > 4) {
		UInt32 offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
		_orderHint = offsetToValue;
		if (offsetToValue + count * sizeof(char) > bytesBuff) {
			IssueError_InvalidFormat();
			return false;
		}
		pBuff = reinterpret_cast<const char*>(buff + offsetToValue);
	}
	SetValue(new Value_String(String(pBuff, count)));
	return true;
}

template<typename TypeDef> bool Tag_ASCII::DoSerialize(Binary& buff, TagList& tagsPointed)
{
	const String& str = Value_String::GetString(GetValue());
	size_t len = ::strlen(str.c_str());
	UInt32 count = static_cast<UInt32>((len + 2) / 2 * 2);
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	if (count <= 4) {
		::memcpy(tagPacked.variable.BYTE, str.c_str(), len);
	} else {
		_posPointer = CalcPosPointer(buff);
		tagsPointed.push_back(this);
	}
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_ASCII::DoSerializePointed(Binary& buff)
{
	ReplaceLONG<TypeDef>(buff, _posPointer, CalcOffset(buff));
	const String& str = Value_String::GetString(GetValue());
	size_t len = ::strlen(str.c_str());
	buff.Append(str.c_str(), len);
	buff.Append("\0\0", (len + 2) / 2 * 2 - len);
	return true;
}

bool Tag_ASCII::Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag)
{
	return beFlag? DoDeserialize<TypeDef_BE>(buff, bytesBuff, offset) :
					DoDeserialize<TypeDef_LE>(buff, bytesBuff, offset);
}

bool Tag_ASCII::Serialize(Binary& buff, bool beFlag, TagList& tagsPointed)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff, tagsPointed) : DoSerialize<TypeDef_LE>(buff, tagsPointed);
}

bool Tag_ASCII::SerializePointed(Binary& buff, bool beFlag)
{
	return beFlag? DoSerializePointed<TypeDef_BE>(buff) : DoSerializePointed<TypeDef_LE>(buff);
}

//------------------------------------------------------------------------------
// Tag_SHORT
//------------------------------------------------------------------------------
VType& Tag_SHORT::GetVTypeAcceptable()
{
	return VTYPE_Number;
}

bool Tag_SHORT::AssignValue(RefPtr<Value> pValue)
{
	if (!CheckRangedNumber(*pValue, 0x0000, 0xffff)) {
		Error::Issue(ErrorType::TypeError, "Number value between 0 and 0xffff is expected for %s",
			GetSymbol()->GetName());
		return false;
	}
	SetValue(pValue.release());
	return true;
}

template<typename TypeDef> bool Tag_SHORT::DoDeserialize(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	using SHORT_T = typename TypeDef::SHORT;
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	if (count == 1) {
		UInt16 num = Gurax_UnpackUInt16(variable.SHORT.num);
		SetValue(new Value_Number(num));
	} else if (count == 2) {
		UInt16 num1 = Gurax_UnpackUInt16(variable.SHORT.num);
		UInt16 num2 = Gurax_UnpackUInt16(variable.SHORT.num2nd);
		SetValue(Value_Tuple::Create(new Value_Number(num1), new Value_Number(num2)));
	} else {
		UInt32 offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
		_orderHint = offsetToValue;
		if (offsetToValue + count * sizeof(SHORT_T) > bytesBuff) {
			IssueError_InvalidFormat();
			return false;
		}
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		pValueOwner->reserve(count);
		size_t offset = offsetToValue;
		for (size_t i = 0; i < count; i++, offset += sizeof(SHORT_T)) {
			const SHORT_T* pSHORT = reinterpret_cast<const SHORT_T*>(buff + offset);
			UInt16 num = Gurax_UnpackUInt16(pSHORT->num);
			pValueOwner->push_back(new Value_Number(num));
		}
		SetValue(new Value_List(VTYPE_Number, pValueOwner.release()));
	}
	return true;
}

template<typename TypeDef> bool Tag_SHORT::DoSerialize(Binary& buff, TagList& tagsPointed)
{
	typename TypeDef::TagPacked tagPacked;
	if (GetValue().IsList()) {
		const ValueOwner& valueOwner = Value_List::GetValueOwner(GetValue());
		UInt32 count = static_cast<UInt32>(valueOwner.size());
		if (count <= 2) {
			if (count >= 1) {
				UInt16 num = Value_Number::GetNumber<UInt16>(*valueOwner[0]);
				Gurax_PackUInt16(tagPacked.variable.SHORT.num, num);
			}
			if (count >= 2) {
				UInt16 num = Value_Number::GetNumber<UInt16>(*valueOwner[1]);
				Gurax_PackUInt16(tagPacked.variable.SHORT.num2nd, num);
			}
		} else {
			_posPointer = CalcPosPointer(buff);
			tagsPointed.push_back(this);
		}
	} else {
		UInt16 num = Value_Number::GetNumber<UInt16>(GetValue());
		UInt32 count = 1;
		tagPacked = MakeTagPacked<TypeDef>(count);
		Gurax_PackUInt16(tagPacked.variable.SHORT.num, num);
	}
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_SHORT::DoSerializePointed(Binary& buff)
{
	ReplaceLONG<TypeDef>(buff, _posPointer, CalcOffset(buff));
	const ValueOwner& valueOwner = Value_List::GetValueOwner(GetValue());
	typename TypeDef::SHORT packed;
	for (const Value* pValue : valueOwner) {
		UInt16 num = Value_Number::GetNumber<UInt16>(*pValue);
		Gurax_PackUInt16(packed.num, num);
		buff.Append(&packed, sizeof(packed));
	}
	return true;
}

bool Tag_SHORT::Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag)
{
	return beFlag? DoDeserialize<TypeDef_BE>(buff, bytesBuff, offset) :
					DoDeserialize<TypeDef_LE>(buff, bytesBuff, offset);
}

bool Tag_SHORT::Serialize(Binary& buff, bool beFlag, TagList& tagsPointed)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff, tagsPointed) : DoSerialize<TypeDef_LE>(buff, tagsPointed);
}

bool Tag_SHORT::SerializePointed(Binary& buff, bool beFlag)
{
	return beFlag? DoSerializePointed<TypeDef_BE>(buff) : DoSerializePointed<TypeDef_LE>(buff);
}

//------------------------------------------------------------------------------
// Tag_LONG
//------------------------------------------------------------------------------
VType& Tag_LONG::GetVTypeAcceptable()
{
	return VTYPE_Number;
}

bool Tag_LONG::AssignValue(RefPtr<Value> pValue)
{
	if (!CheckRangedNumber(*pValue, 0x00000000, 0xffffffff)) {
		Error::Issue(ErrorType::TypeError, "Number value between 0 and 0xffffffff is expected for %s",
			GetSymbol()->GetName());
		return false;
	}
	SetValue(pValue.release());
	return true;
}

template<typename TypeDef> bool Tag_LONG::DoDeserialize(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	using LONG_T = typename TypeDef::LONG;
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	if (count == 1) {
		UInt32 num = Gurax_UnpackUInt32(variable.LONG.num);
		SetValue(new Value_Number(num));
	} else {
		UInt32 offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
		_orderHint = offsetToValue;
		if (offsetToValue + count * sizeof(LONG_T) > bytesBuff) {
			IssueError_InvalidFormat();
			return false;
		}
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		pValueOwner->reserve(count);
		size_t offset = offsetToValue;
		for (size_t i = 0; i < count; i++, offset += sizeof(LONG_T)) {
			const LONG_T* pLONG = reinterpret_cast<const LONG_T*>(buff + offset);
			UInt32 num = Gurax_UnpackUInt32(pLONG->num);
			pValueOwner->push_back(new Value_Number(num));
		}
		SetValue(new Value_List(VTYPE_Number, pValueOwner.release()));
	}
	return true;
}

template<typename TypeDef> bool Tag_LONG::DoSerialize(Binary& buff, TagList& tagsPointed)
{
	typename TypeDef::TagPacked tagPacked;
	if (GetValue().IsList()) {
		const ValueOwner& valueOwner = Value_List::GetValueOwner(GetValue());
		UInt32 count = static_cast<UInt32>(valueOwner.size());
		tagPacked = MakeTagPacked<TypeDef>(count);
		if (count == 1) {
			UInt32 num = Value_Number::GetNumber<UInt32>(*valueOwner[0]);
			Gurax_PackUInt32(tagPacked.variable.LONG.num, num);
		} else {
			_posPointer = CalcPosPointer(buff);
			tagsPointed.push_back(this);
		}
	} else {
		UInt32 num = Value_Number::GetNumber<UInt32>(GetValue());
		UInt32 count = 1;
		tagPacked = MakeTagPacked<TypeDef>(count);
		Gurax_PackUInt32(tagPacked.variable.LONG.num, num);
	}
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_LONG::DoSerializePointed(Binary& buff)
{
	ReplaceLONG<TypeDef>(buff, _posPointer, CalcOffset(buff));
	const ValueOwner& valueOwner = Value_List::GetValueOwner(GetValue());
	typename TypeDef::LONG packed;
	for (const Value* pValue : valueOwner) {
		UInt32 num = Value_Number::GetNumber<UInt32>(*pValue);
		Gurax_PackUInt32(packed.num, num);
		buff.Append(&packed, sizeof(packed));
	}
	return true;
}

bool Tag_LONG::Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag)
{
	return beFlag? DoDeserialize<TypeDef_BE>(buff, bytesBuff, offset) :
					DoDeserialize<TypeDef_LE>(buff, bytesBuff, offset);
}

bool Tag_LONG::Serialize(Binary& buff, bool beFlag, TagList& tagsPointed)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff, tagsPointed) : DoSerialize<TypeDef_LE>(buff, tagsPointed);
}

bool Tag_LONG::SerializePointed(Binary& buff, bool beFlag)
{
	return beFlag? DoSerializePointed<TypeDef_BE>(buff) : DoSerializePointed<TypeDef_LE>(buff);
}

//------------------------------------------------------------------------------
// Tag_RATIONAL
//------------------------------------------------------------------------------
VType& Tag_RATIONAL::GetVTypeAcceptable()
{
	return VTYPE_Rational;
}

bool Tag_RATIONAL::AssignValue(RefPtr<Value> pValue)
{
	if (!(pValue->IsType(VTYPE_Rational) ||
		(pValue->IsType(VTYPE_List) &&
			Value_List::GetValueTypedOwner(*pValue).RefreshVTypeOfElems().IsIdentical(VTYPE_Rational)))) {
		Error::Issue(ErrorType::TypeError, "Rational value is expected for %s", GetSymbol()->GetName());
		return false;
	}
	SetValue(pValue.release());
	return true;
}

template<typename TypeDef> bool Tag_RATIONAL::DoDeserialize(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	using RATIONAL_T = typename TypeDef::RATIONAL;
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	UInt32 offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
	_orderHint = offsetToValue;
	if (offsetToValue + count * sizeof(RATIONAL_T) > bytesBuff) {
		IssueError_InvalidFormat();
		return false;
	}
	if (count == 1) {
		const RATIONAL_T* pRATIONAL = reinterpret_cast<const RATIONAL_T*>(buff + offsetToValue);
		RefPtr<Value> pValue(CreateValueFromRATIONAL(*pRATIONAL));
		if (!pValue) return false;
		SetValue(pValue.release());
	} else {
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		pValueOwner->reserve(count);
		size_t offset = offsetToValue;
		for (size_t i = 0; i < count; i++, offset += sizeof(RATIONAL_T)) {
			const RATIONAL_T* pRATIONAL = reinterpret_cast<const RATIONAL_T*>(buff + offset);
			RefPtr<Value> pValueElem(CreateValueFromRATIONAL(*pRATIONAL));
			if (!pValueElem) return false;
			pValueOwner->push_back(pValueElem.release());
		}
		SetValue(new Value_List(VTYPE_Number, pValueOwner.release()));
	}
	return true;
}

template<typename TypeDef> bool Tag_RATIONAL::DoSerialize(Binary& buff, TagList& tagsPointed)
{
	UInt32 count = GetValue().IsList()?
		static_cast<UInt32>(Value_List::GetValueOwner(GetValue()).size()) : 1;
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	_posPointer = CalcPosPointer(buff);
	tagsPointed.push_back(this);
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_RATIONAL::DoSerializePointed(Binary& buff)
{
	ReplaceLONG<TypeDef>(buff, _posPointer, CalcOffset(buff));
	if (GetValue().IsList()) {
		const ValueOwner& valueOwner = Value_List::GetValueOwner(GetValue());
		typename TypeDef::RATIONAL packed;
		for (const Value* pValue : valueOwner) {
			const Rational& num = Value_Rational::GetRational(*pValue);
			int numer = num.GetNumer(), denom = num.GetDenom();
			Gurax_PackUInt32(packed.numerator, numer);
			Gurax_PackUInt32(packed.denominator, denom);
			buff.Append(&packed, sizeof(packed));
		}
	} else {
		typename TypeDef::RATIONAL packed;
		const Rational& num = Value_Rational::GetRational(GetValue());
		int numer = num.GetNumer(), denom = num.GetDenom();
		Gurax_PackUInt32(packed.numerator, numer);
		Gurax_PackUInt32(packed.denominator, denom);
		buff.Append(&packed, sizeof(packed));
	}
	return true;
}

bool Tag_RATIONAL::Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag)
{
	return beFlag? DoDeserialize<TypeDef_BE>(buff, bytesBuff, offset) :
					DoDeserialize<TypeDef_LE>(buff, bytesBuff, offset);
}

bool Tag_RATIONAL::Serialize(Binary& buff, bool beFlag, TagList& tagsPointed)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff, tagsPointed) : DoSerialize<TypeDef_LE>(buff, tagsPointed);
}

bool Tag_RATIONAL::SerializePointed(Binary& buff, bool beFlag)
{
	return beFlag? DoSerializePointed<TypeDef_BE>(buff) : DoSerializePointed<TypeDef_LE>(buff);
}

//------------------------------------------------------------------------------
// Tag_UNDEFINED
//------------------------------------------------------------------------------
VType& Tag_UNDEFINED::GetVTypeAcceptable()
{
	return VTYPE_Binary;
}

bool Tag_UNDEFINED::AssignValue(RefPtr<Value> pValue)
{
	if (!pValue->IsType(VTYPE_Binary)) {
		Error::Issue(ErrorType::TypeError, "Binary value is expected for %s",
			GetSymbol()->GetName());
		return false;
	}
	SetValue(pValue.release());
	return true;
}

template<typename TypeDef> bool Tag_UNDEFINED::DoDeserialize(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	const UInt8* pBuff = variable.BYTE;
	if (count > 4) {
		UInt32 offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
		_orderHint = offsetToValue;
		if (offsetToValue + count * sizeof(UInt8) > bytesBuff) {
			IssueError_InvalidFormat();
			return false;
		}
		pBuff = buff + offsetToValue;
	}
	SetValue(new Value_Binary(Binary(pBuff, count)));
	return true;
}

template<typename TypeDef> bool Tag_UNDEFINED::DoSerialize(Binary& buff, TagList& tagsPointed)
{
	const Binary& buffSrc = Value_Binary::GetBinary(GetValue());
	UInt32 count = static_cast<UInt32>(buffSrc.size());
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	if (count <= 4) {
		::memcpy(tagPacked.variable.BYTE, buffSrc.data(), count);
	} else {
		_posPointer = CalcPosPointer(buff);
		tagsPointed.push_back(this);
	}
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_UNDEFINED::DoSerializePointed(Binary& buff)
{
	ReplaceLONG<TypeDef>(buff, _posPointer, CalcOffset(buff));
	const Binary& buffSrc = Value_Binary::GetBinary(GetValue());
	buff.append(buffSrc);
	return true;
}

bool Tag_UNDEFINED::Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag)
{
	return beFlag? DoDeserialize<TypeDef_BE>(buff, bytesBuff, offset) :
					DoDeserialize<TypeDef_LE>(buff, bytesBuff, offset);
}

bool Tag_UNDEFINED::Serialize(Binary& buff, bool beFlag, TagList& tagsPointed)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff, tagsPointed) : DoSerialize<TypeDef_LE>(buff, tagsPointed);
}

bool Tag_UNDEFINED::SerializePointed(Binary& buff, bool beFlag)
{
	return beFlag? DoSerializePointed<TypeDef_BE>(buff) : DoSerializePointed<TypeDef_LE>(buff);
}

//------------------------------------------------------------------------------
// Tag_SLONG
//------------------------------------------------------------------------------
VType& Tag_SLONG::GetVTypeAcceptable()
{
	return VTYPE_Number;
}

bool Tag_SLONG::AssignValue(RefPtr<Value> pValue)
{
	if (!CheckRangedNumber(*pValue, -0x80000000, 0x7fffffff)) {
		Error::Issue(ErrorType::TypeError, "Number value between -0x80000000 and 0x7fffffff is expected for %s",
			GetSymbol()->GetName());
		return false;
	}
	SetValue(pValue.release());
	return true;
}

template<typename TypeDef> bool Tag_SLONG::DoDeserialize(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	using SLONG_T = typename TypeDef::SLONG;
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	if (count == 1) {
		Int32 num = Gurax_UnpackInt32(variable.SLONG.num);
		SetValue(new Value_Number(num));
	} else {
		UInt32 offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
		_orderHint = offsetToValue;
		if (offsetToValue + count * sizeof(SLONG_T) > bytesBuff) {
			IssueError_InvalidFormat();
			return false;
		}
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		pValueOwner->reserve(count);
		size_t offset = offsetToValue;
		for (size_t i = 0; i < count; i++, offset += sizeof(SLONG_T)) {
			const SLONG_T* pSLONG = reinterpret_cast<const SLONG_T*>(buff + offset);
			Int32 num = Gurax_UnpackInt32(pSLONG->num);
			pValueOwner->push_back(new Value_Number(num));
		}
		SetValue(new Value_List(VTYPE_Number, pValueOwner.release()));
	}
	return true;
}

template<typename TypeDef> bool Tag_SLONG::DoSerialize(Binary& buff, TagList& tagsPointed)
{
	typename TypeDef::TagPacked tagPacked;
	if (GetValue().IsList()) {
		const ValueOwner& valueOwner = Value_List::GetValueOwner(GetValue());
		UInt32 count = static_cast<UInt32>(valueOwner.size());
		tagPacked = MakeTagPacked<TypeDef>(count);
		if (count == 1) {
			Int32 num = Value_Number::GetNumber<Int32>(*valueOwner[0]);
			Gurax_PackInt32(tagPacked.variable.LONG.num, num);
		} else {
			_posPointer = CalcPosPointer(buff);
		}
	} else {
		Int32 num = Value_Number::GetNumber<Int32>(GetValue());
		UInt32 count = 1;
		tagPacked = MakeTagPacked<TypeDef>(count);
		Gurax_PackInt32(tagPacked.variable.LONG.num, num);
	}
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_SLONG::DoSerializePointed(Binary& buff)
{
	ReplaceLONG<TypeDef>(buff, _posPointer, CalcOffset(buff));
	const ValueOwner& valueOwner = Value_List::GetValueOwner(GetValue());
	typename TypeDef::SLONG packed;
	for (const Value* pValue : valueOwner) {
		Int32 num = Value_Number::GetNumber<Int32>(*pValue);
		Gurax_PackInt32(packed.num, num);
		buff.Append(&packed, sizeof(packed));
	}
	return true;
}

bool Tag_SLONG::Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag)
{
	return beFlag? DoDeserialize<TypeDef_BE>(buff, bytesBuff, offset) :
					DoDeserialize<TypeDef_LE>(buff, bytesBuff, offset);
}

bool Tag_SLONG::Serialize(Binary& buff, bool beFlag, TagList& tagsPointed)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff, tagsPointed) : DoSerialize<TypeDef_LE>(buff, tagsPointed);
}

bool Tag_SLONG::SerializePointed(Binary& buff, bool beFlag)
{
	return beFlag? DoSerializePointed<TypeDef_BE>(buff) : DoSerializePointed<TypeDef_LE>(buff);
}

//------------------------------------------------------------------------------
// Tag_SRATIONAL
//------------------------------------------------------------------------------
VType& Tag_SRATIONAL::GetVTypeAcceptable()
{
	return VTYPE_Rational;
}

bool Tag_SRATIONAL::AssignValue(RefPtr<Value> pValue)
{
	if (!(pValue->IsType(VTYPE_Rational) ||
		(pValue->IsType(VTYPE_List) &&
			Value_List::GetValueTypedOwner(*pValue).RefreshVTypeOfElems().IsIdentical(VTYPE_Rational)))) {
		Error::Issue(ErrorType::TypeError, "Rational value is expected for %s",
			GetSymbol()->GetName());
		return false;
	}
	SetValue(pValue.release());
	return true;
}

template<typename TypeDef> bool Tag_SRATIONAL::DoDeserialize(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	using SRATIONAL_T = typename TypeDef::SRATIONAL;
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	UInt32 offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
	_orderHint = offsetToValue;
	if (offsetToValue + count * sizeof(SRATIONAL_T) > bytesBuff) {
		IssueError_InvalidFormat();
		return false;
	}
	if (count == 1) {
		const SRATIONAL_T* pSRATIONAL = reinterpret_cast<const SRATIONAL_T*>(buff + offsetToValue);
		RefPtr<Value> pValue(CreateValueFromSRATIONAL(*pSRATIONAL));
		if (!pValue) return false;
		SetValue(pValue.release());
	} else {
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		pValueOwner->reserve(count);
		size_t offset = offsetToValue;
		for (size_t i = 0; i < count; i++, offset += sizeof(SRATIONAL_T)) {
			const SRATIONAL_T* pSRATIONAL = reinterpret_cast<const SRATIONAL_T*>(buff + offset);
			RefPtr<Value> pValueElem(CreateValueFromSRATIONAL(*pSRATIONAL));
			if (!pValueElem) return false;
			pValueOwner->push_back(pValueElem.release());
		}
		SetValue(new Value_List(VTYPE_Number, pValueOwner.release()));
	}
	return true;
}

template<typename TypeDef> bool Tag_SRATIONAL::DoSerialize(Binary& buff, TagList& tagsPointed)
{
	UInt32 count = GetValue().IsList()?
		static_cast<UInt32>(Value_List::GetValueOwner(GetValue()).size()) : 1;
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	_posPointer = CalcPosPointer(buff);
	tagsPointed.push_back(this);
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_SRATIONAL::DoSerializePointed(Binary& buff)
{
	ReplaceLONG<TypeDef>(buff, _posPointer, CalcOffset(buff));
	if (GetValue().IsList()) {
		const ValueOwner& valueOwner = Value_List::GetValueOwner(GetValue());
		typename TypeDef::SRATIONAL packed;
		for (const Value* pValue : valueOwner) {
			const Rational& num = Value_Rational::GetRational(*pValue);
			int numer = num.GetNumer(), denom = num.GetDenom();
			Gurax_PackUInt32(packed.numerator, numer);
			Gurax_PackUInt32(packed.denominator, denom);
			buff.Append(&packed, sizeof(packed));
		}
	} else {
		typename TypeDef::SRATIONAL packed;
		const Rational& num = Value_Rational::GetRational(GetValue());
		int numer = num.GetNumer(), denom = num.GetDenom();
		Gurax_PackUInt32(packed.numerator, numer);
		Gurax_PackUInt32(packed.denominator, denom);
		buff.Append(&packed, sizeof(packed));
	}
	return true;
}

bool Tag_SRATIONAL::Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag)
{
	return beFlag? DoDeserialize<TypeDef_BE>(buff, bytesBuff, offset) :
					DoDeserialize<TypeDef_LE>(buff, bytesBuff, offset);
}

bool Tag_SRATIONAL::Serialize(Binary& buff, bool beFlag, TagList& tagsPointed)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff, tagsPointed) : DoSerialize<TypeDef_LE>(buff, tagsPointed);
}

bool Tag_SRATIONAL::SerializePointed(Binary& buff, bool beFlag)
{
	return beFlag? DoSerializePointed<TypeDef_BE>(buff) : DoSerializePointed<TypeDef_LE>(buff);
}

//------------------------------------------------------------------------------
// Tag_IFD
//------------------------------------------------------------------------------
VType& Tag_IFD::GetVTypeAcceptable()
{
	return VTYPE_List;
}

bool Tag_IFD::AssignValue(RefPtr<Value> pValue)
{
	if (!pValue->IsList()) return false;
	RefPtr<IFD> pIFD(IFD::CreateFromList(_pSymbol, Value_List::GetValueOwner(*pValue)));
	if (!pIFD) return false;
	SetValue(new Value_IFD(pIFD.release()));
	return true;
}

template<typename TypeDef> bool Tag_IFD::DoDeserialize(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	UInt32 offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
	_orderHint = 0xffffffff;
	RefPtr<IFD> pIFD(IFD::Deserialize<TypeDef>(buff, bytesBuff, offsetToValue, _pSymbol));
	if (!pIFD) return false;
	SetValue(new Value_IFD(pIFD.release()));
	return true;
}

template<typename TypeDef> bool Tag_IFD::DoSerialize(Binary& buff, TagList& tagsPointed)
{
	UInt32 count = 1;
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	_posPointer = CalcPosPointer(buff);
	tagsPointed.push_back(this);
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

bool Tag_IFD::Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag)
{
	return beFlag? DoDeserialize<TypeDef_BE>(buff, bytesBuff, offset) :
					DoDeserialize<TypeDef_LE>(buff, bytesBuff, offset);
}

bool Tag_IFD::Serialize(Binary& buff, bool beFlag, TagList& tagsPointed)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff, tagsPointed) : DoSerialize<TypeDef_LE>(buff, tagsPointed);
}

bool Tag_IFD::SerializePointed(Binary& buff, bool beFlag)
{
	if (beFlag) {
		ReplaceLONG<TypeDef_BE>(buff, _posPointer, CalcOffset(buff));
	} else {
		ReplaceLONG<TypeDef_LE>(buff, _posPointer, CalcOffset(buff));
	}
	IFD& ifd = Value_IFD::GetIFD(GetValue());
	return ifd.Serialize(buff, beFlag);
}

//------------------------------------------------------------------------------
// Tag_JPEGInterchangeFormat
//------------------------------------------------------------------------------
VType& Tag_JPEGInterchangeFormat::GetVTypeAcceptable()
{
	return VTYPE_Nil;
}

bool Tag_JPEGInterchangeFormat::AssignValue(RefPtr<Value> pValue)
{
	return false;
}

template<typename TypeDef> bool Tag_JPEGInterchangeFormat::DoDeserialize(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	auto& variable = tagPacked.variable;
	UInt32 offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
	_orderHint = offsetToValue;
	if (offsetToValue >= bytesBuff) {
		IssueError_InvalidFormat();
		return false;
	}
	const UInt8* pBuff = buff + offsetToValue;
	SetValue(new Value_Binary(Binary(pBuff, bytesBuff - offsetToValue)));
	return true;
}

template<typename TypeDef> bool Tag_JPEGInterchangeFormat::DoSerialize(Binary& buff, TagList& tagsPointed)
{
	const Binary& buffSrc = Value_Binary::GetBinary(GetValue());
	UInt32 count = 1;
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	_posPointer = CalcPosPointer(buff);
	tagsPointed.push_back(this);
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_JPEGInterchangeFormat::DoSerializePointed(Binary& buff)
{
	static const UInt8 buffPad[] = {
		0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	};
	buff.append(buffPad, sizeof(buffPad));
	ReplaceLONG<TypeDef>(buff, _posPointer, CalcOffset(buff));
	const Binary& buffSrc = Value_Binary::GetBinary(GetValue());
	buff.append(buffSrc);
	return true;
}

bool Tag_JPEGInterchangeFormat::Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag)
{
	return beFlag? DoDeserialize<TypeDef_BE>(buff, bytesBuff, offset) :
					DoDeserialize<TypeDef_LE>(buff, bytesBuff, offset);
}

bool Tag_JPEGInterchangeFormat::Serialize(Binary& buff, bool beFlag, TagList& tagsPointed)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff, tagsPointed) : DoSerialize<TypeDef_LE>(buff, tagsPointed);
}

bool Tag_JPEGInterchangeFormat::SerializePointed(Binary& buff, bool beFlag)
{
	return beFlag? DoSerializePointed<TypeDef_BE>(buff) : DoSerializePointed<TypeDef_LE>(buff);
}

//------------------------------------------------------------------------------
// TagList
//------------------------------------------------------------------------------
Tag* TagList::FindBySymbol(const Symbol* pSymbol)
{
	for (iterator ppTag = begin(); ppTag != end(); ppTag++) {
		if ((*ppTag)->GetSymbol()->IsIdentical(pSymbol)) return *ppTag;
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// TagOwner
//------------------------------------------------------------------------------
void TagOwner::Clear()
{
	for (Tag* pTag : *this) Tag::Delete(pTag);
	clear();
}

bool TagOwner::DeleteBySymbol(const Symbol* pSymbol)
{
	for (iterator ppTag = begin(); ppTag != end(); ppTag++) {
		if ((*ppTag)->GetSymbol()->IsIdentical(pSymbol)) {
			Tag::Delete(*ppTag);
			erase(ppTag);
			return true;
		}
	}
	return false;
}

//------------------------------------------------------------------------------
// TagMap
//------------------------------------------------------------------------------
void TagMap::Clear()
{
	for (auto iter = begin(); iter != end(); iter++) Tag::Delete(iter->second);
	clear();
}

Tag* TagMap::Lookup(const Symbol* pSymbol) const
{
	auto iter = find(pSymbol);
	return (iter == end())? nullptr : iter->second;
}

void TagMap::Add(const Symbol* pSymbol, Tag* pTag)
{
	(*this)[pSymbol] = pTag;
}

void TagMap::Erase(const Symbol* pSymbol)
{
	auto ppTag = find(pSymbol);
	if (ppTag != end()) {
		Tag::Delete(ppTag->second);
		erase(ppTag);
	}
}

Gurax_EndModuleScope(jpeg)
