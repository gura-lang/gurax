//==============================================================================
// Tag.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Tag
//------------------------------------------------------------------------------
Tag::Tag(UInt16 typeId, UInt16 tagId, UInt32 count, const Symbol* pSymbol,
	size_t offset, size_t offsetToValue, Value* pValue, Value* pValueCooked) :
	_typeId(typeId), _tagId(tagId), _count(count), _pSymbol(pSymbol),
	_offset(offset), _offsetToValue(offsetToValue), _posPointer(0), _orderHint(0),
	_pValue(pValue), _pValueCooked(pValueCooked)
{
}

bool Tag::CheckRangedNumber(const Value& value, Double numMin, Double numMax)
{
	auto CheckSub = [numMin, numMax](const Value& value) {
		if (!value.IsType(VTYPE_Number)) {
			Error::Issue(ErrorType::ValueError, "number value is expected");
			return false;
		}
		Double num = Value_Number::GetNumber<Double>(value);
		if (num <= numMin && num <= numMax) return true;
		Error::Issue(ErrorType::RangeError, "value number is out of range");
		return false;
	};
	if (!value.IsType(VTYPE_List)) return CheckSub(value);
	for (const Value* pValue : Value_List::GetValueOwner(value)) {
		if (!CheckSub(value)) return false;
	}
	return true;
};

String Tag::ToString(const StringStyle& ss) const
{
	String str;
	str += _pSymbol->GetName();
	str += ":";
	str += _pValue->ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// Tag_BYTE
//------------------------------------------------------------------------------
bool Tag_BYTE::CheckAcceptableValue(Value& value) const
{
	return value.IsType(VTYPE_Binary);
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

template<typename TypeDef> bool Tag_BYTE::DoSerializePointed(Binary& buff)
{
	ReplaceLONG<TypeDef>(buff, _posPointer, CalcOffset(buff));
	const Binary& buffSrc = Value_Binary::GetBinary(GetValue());
	buff.append(buffSrc);
	return true;
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
bool Tag_ASCII::CheckAcceptableValue(Value& value) const
{
	return value.IsType(VTYPE_String);
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
bool Tag_SHORT::CheckAcceptableValue(Value& value) const
{
	return CheckRangedNumber(value, 0x0000, 0xffff);
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
bool Tag_LONG::CheckAcceptableValue(Value& value) const
{
	return CheckRangedNumber(value, 0x00000000, 0xffffffff);
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
bool Tag_RATIONAL::CheckAcceptableValue(Value& value) const
{
	return value.IsType(VTYPE_Rational);
		(value.IsType(VTYPE_List) &&
			Value_List::GetValueTypedOwner(value).RefreshVTypeOfElems().IsIdentical(VTYPE_Rational));
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
bool Tag_UNDEFINED::CheckAcceptableValue(Value& value) const
{
	return value.IsType(VTYPE_Binary);
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
bool Tag_SLONG::CheckAcceptableValue(Value& value) const
{
	return CheckRangedNumber(value, -0x80000000, 0x7fffffff);
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
bool Tag_SRATIONAL::CheckAcceptableValue(Value& value) const
{
	return value.IsType(VTYPE_Rational);
		(value.IsType(VTYPE_List) &&
			Value_List::GetValueTypedOwner(value).RefreshVTypeOfElems().IsIdentical(VTYPE_Rational));
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
bool Tag_IFD::CheckAcceptableValue(Value& value) const
{
	return false;
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
bool Tag_JPEGInterchangeFormat::CheckAcceptableValue(Value& value) const
{
	return value.IsType(VTYPE_Binary);
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

//------------------------------------------------------------------------------
// TagOwner
//------------------------------------------------------------------------------
void TagOwner::Clear()
{
	for (Tag* pTag : *this) Tag::Delete(pTag);
	clear();
}

void TagOwner::Erase(const Symbol* pSymbol)
{
	for (auto ppTag = begin(); ppTag != end(); ppTag++) {
		if ((*ppTag)->GetSymbol()->IsIdentical(pSymbol)) {
			Tag::Delete(*ppTag);
			erase(ppTag);
			break;
		}
	}
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

void TagMap::Erase(const Symbol* pSymbol)
{
	auto ppTag = find(pSymbol);
	if (ppTag != end()) {
		Tag::Delete(ppTag->second);
		erase(ppTag);
	}
}

Gurax_EndModuleScope(jpeg)
