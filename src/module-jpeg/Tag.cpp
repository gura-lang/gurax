//==============================================================================
// Tag.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// SerialBuff
//------------------------------------------------------------------------------
bool SerialBuff::WriteToBinary(Binary& buff)
{
	buff.append(_buff);
	buff.append(_buffData);
	return true;
}

//------------------------------------------------------------------------------
// Tag
//------------------------------------------------------------------------------
Tag::Tag(UInt16 typeId, UInt16 tagId, UInt32 count, const Symbol* pSymbol,
	size_t offset, size_t offsetToValue, Value* pValue, Value* pValueCooked) :
	_typeId(typeId), _tagId(tagId), _count(count), _pSymbol(pSymbol),
	_offset(offset), _offsetToValue(offsetToValue), _offsetPointer(0),
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

template<typename TypeDef> bool Tag_BYTE::DoSerializePre(SerialBuff& serialBuff, size_t offsetToData)
{
	const Binary& buff = Value_Binary::GetBinary(GetValue());
	UInt32 count = static_cast<UInt32>(buff.size());
	if (count > 4) {
		_offsetToValue = serialBuff.CalcOffsetToValue(offsetToData);
		serialBuff.GetBuffData_BYTE().append(buff);
	}
	return true;
}

template<typename TypeDef> bool Tag_BYTE::DoSerialize(Binary& buff)
{
	const Binary& buffSrc = Value_Binary::GetBinary(GetValue());
	UInt32 count = static_cast<UInt32>(buffSrc.size());
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	if (count <= 4) {
		::memcpy(tagPacked.variable.BYTE, buffSrc.data(), count);
	} else {
		_offsetPointer = buff.size() + 4;
		UInt32 offset = 0x00000000;
		Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
	}
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_BYTE::DoSerializePointed(Binary& buff)
{
	return true;
}

bool Tag_BYTE::SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff, offset) : DoSerializePre<TypeDef_LE>(serialBuff, offset);
}

bool Tag_BYTE::Serialize(Binary& buff, bool beFlag)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff) : DoSerialize<TypeDef_LE>(buff);
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

template<typename TypeDef> bool Tag_ASCII::DoSerializePre(SerialBuff& serialBuff, size_t offsetToData)
{
	const String& str = Value_String::GetString(GetValue());
	UInt32 count = static_cast<UInt32>((::strlen(str.c_str()) + 2) / 2 * 2);
	if (count > 4) {
		_offsetToValue = serialBuff.CalcOffsetToValue(offsetToData);
		Binary& buff = serialBuff.GetBuffData_BYTE();
		buff.Append(str.data(), count);
		if (count % 2 != 0) buff.Append("", 1);
	}
	return true;
}

template<typename TypeDef> bool Tag_ASCII::DoSerialize(Binary& buff)
{
	const String& str = Value_String::GetString(GetValue());
	UInt32 count = static_cast<UInt32>((::strlen(str.c_str()) + 2) / 2 * 2);
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	if (count <= 4) {
		::memcpy(tagPacked.variable.BYTE, str.data(), count);
	} else {
		_offsetPointer = buff.size() + 4;
		UInt32 offset = 0x00000000;
		Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
	}
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_ASCII::DoSerializePointed(Binary& buff)
{
	return true;
}

bool Tag_ASCII::SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff, offset) : DoSerializePre<TypeDef_LE>(serialBuff, offset);
}

bool Tag_ASCII::Serialize(Binary& buff, bool beFlag)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff) : DoSerialize<TypeDef_LE>(buff);
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

template<typename TypeDef> bool Tag_SHORT::DoSerializePre(SerialBuff& serialBuff, size_t offsetToData)
{
	if (!GetValue().IsList()) return true;
	const ValueOwner& valueOwner = Value_List::GetValueOwner(GetValue());
	UInt32 count = static_cast<UInt32>(valueOwner.size());
	if (count <= 2) return true;
	_offsetToValue = serialBuff.CalcOffsetToValue(offsetToData);
	typename TypeDef::SHORT packed;
	for (const Value* pValue : valueOwner) {
		UInt16 num = Value_Number::GetNumber<UInt16>(*pValue);
		Gurax_PackUInt16(packed.num, num);
		serialBuff.GetBuffData_SHORT().Append(&packed, sizeof(packed));
	}
	return true;
}

template<typename TypeDef> bool Tag_SHORT::DoSerialize(Binary& buff)
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
			_offsetPointer = buff.size() + 4;
			UInt32 offset = 0x00000000;
			Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
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
	return true;
}

bool Tag_SHORT::SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff, offset) : DoSerializePre<TypeDef_LE>(serialBuff, offset);
}

bool Tag_SHORT::Serialize(Binary& buff, bool beFlag)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff) : DoSerialize<TypeDef_LE>(buff);
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

template<typename TypeDef> bool Tag_LONG::DoSerializePre(SerialBuff& serialBuff, size_t offsetToData)
{
	if (!GetValue().IsList()) return true;
	const ValueOwner& valueOwner = Value_List::GetValueOwner(GetValue());
	UInt32 count = static_cast<UInt32>(valueOwner.size());
	if (count <= 1) return true;
	_offsetToValue = serialBuff.CalcOffsetToValue(offsetToData);
	typename TypeDef::LONG packed;
	for (const Value* pValue : valueOwner) {
		UInt32 num = Value_Number::GetNumber<UInt32>(*pValue);
		Gurax_PackUInt32(packed.num, num);
		serialBuff.GetBuffData_LONG().Append(&packed, sizeof(packed));
	}
	return true;
}

template<typename TypeDef> bool Tag_LONG::DoSerialize(Binary& buff)
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
			_offsetPointer = buff.size() + 4;
			UInt32 offset = 0x00000000;
			Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
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
	return true;
}

bool Tag_LONG::SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff, offset) : DoSerializePre<TypeDef_LE>(serialBuff, offset);
}

bool Tag_LONG::Serialize(Binary& buff, bool beFlag)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff) : DoSerialize<TypeDef_LE>(buff);
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

template<typename TypeDef> bool Tag_RATIONAL::DoSerializePre(SerialBuff& serialBuff, size_t offsetToData)
{
	_offsetToValue = serialBuff.CalcOffsetToValue(offsetToData);
	if (GetValue().IsList()) {
		const ValueOwner& valueOwner = Value_List::GetValueOwner(GetValue());
		typename TypeDef::RATIONAL packed;
		for (const Value* pValue : valueOwner) {
			const Rational& num = Value_Rational::GetRational(*pValue);
			int numer = num.GetNumer(), denom = num.GetDenom();
			Gurax_PackUInt32(packed.numerator, numer);
			Gurax_PackUInt32(packed.denominator, denom);
			serialBuff.GetBuffData_RATIONAL().Append(&packed, sizeof(packed));
		}
	} else {
		typename TypeDef::RATIONAL packed;
		const Rational& num = Value_Rational::GetRational(GetValue());
		int numer = num.GetNumer(), denom = num.GetDenom();
		Gurax_PackUInt32(packed.numerator, numer);
		Gurax_PackUInt32(packed.denominator, denom);
		serialBuff.GetBuffData_RATIONAL().Append(&packed, sizeof(packed));
	}
	return true;
}

template<typename TypeDef> bool Tag_RATIONAL::DoSerialize(Binary& buff)
{
	UInt32 count = GetValue().IsList()?
		static_cast<UInt32>(Value_List::GetValueOwner(GetValue()).size()) : 1;
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	UInt32 offsetToValue = static_cast<UInt32>(_offsetToValue);
	Gurax_PackUInt32(tagPacked.variable.LONG.num, offsetToValue);
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_RATIONAL::DoSerializePointed(Binary& buff)
{
	return true;
}

bool Tag_RATIONAL::SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff, offset) : DoSerializePre<TypeDef_LE>(serialBuff, offset);
}

bool Tag_RATIONAL::Serialize(Binary& buff, bool beFlag)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff) : DoSerialize<TypeDef_LE>(buff);
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

template<typename TypeDef> bool Tag_UNDEFINED::DoSerializePre(SerialBuff& serialBuff, size_t offsetToData)
{
	const Binary& buff = Value_Binary::GetBinary(GetValue());
	UInt32 count = static_cast<UInt32>(buff.size());
	if (count > 4) {
		_offsetToValue = serialBuff.CalcOffsetToValue(offsetToData);
		serialBuff.GetBuffData_BYTE().append(buff);
	}
	return true;
}

template<typename TypeDef> bool Tag_UNDEFINED::DoSerialize(Binary& buff)
{
	const Binary& buffSrc = Value_Binary::GetBinary(GetValue());
	UInt32 count = static_cast<UInt32>(buffSrc.size());
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	if (count <= 4) {
		::memcpy(tagPacked.variable.BYTE, buffSrc.data(), count);
	} else {
		_offsetPointer = buff.size() + 4;
		UInt32 offset = 0x00000000;
		Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
	}
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_UNDEFINED::DoSerializePointed(Binary& buff)
{
	return true;
}

bool Tag_UNDEFINED::SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff, offset) : DoSerializePre<TypeDef_LE>(serialBuff, offset);
}

bool Tag_UNDEFINED::Serialize(Binary& buff, bool beFlag)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff) : DoSerialize<TypeDef_LE>(buff);
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

template<typename TypeDef> bool Tag_SLONG::DoSerializePre(SerialBuff& serialBuff, size_t offsetToData)
{
	if (!GetValue().IsList()) return true;
	const ValueOwner& valueOwner = Value_List::GetValueOwner(GetValue());
	UInt32 count = static_cast<UInt32>(valueOwner.size());
	if (count <= 1) return true;
	_offsetToValue = serialBuff.CalcOffsetToValue(offsetToData);
	typename TypeDef::SLONG packed;
	for (const Value* pValue : valueOwner) {
		Int32 num = Value_Number::GetNumber<Int32>(*pValue);
		Gurax_PackInt32(packed.num, num);
		serialBuff.GetBuffData_SLONG().Append(&packed, sizeof(packed));
	}
	return true;
}

template<typename TypeDef> bool Tag_SLONG::DoSerialize(Binary& buff)
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
			_offsetPointer = buff.size() + 4;
			UInt32 offset = 0x00000000;
			Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
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
	return true;
}

bool Tag_SLONG::SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff, offset) : DoSerializePre<TypeDef_LE>(serialBuff, offset);
}

bool Tag_SLONG::Serialize(Binary& buff, bool beFlag)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff) : DoSerialize<TypeDef_LE>(buff);
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

template<typename TypeDef> bool Tag_SRATIONAL::DoSerializePre(SerialBuff& serialBuff, size_t offsetToData)
{
	_offsetToValue = serialBuff.CalcOffsetToValue(offsetToData);
	if (!GetValue().IsList()) return true;
	const ValueOwner& valueOwner = Value_List::GetValueOwner(GetValue());
	typename TypeDef::SRATIONAL packed;
	for (const Value* pValue : valueOwner) {
		const Rational& num = Value_Rational::GetRational(*pValue);
		int numer = num.GetNumer(), denom = num.GetDenom();
		Gurax_PackUInt32(packed.numerator, numer);
		Gurax_PackUInt32(packed.denominator, denom);
		serialBuff.GetBuffData_SRATIONAL().Append(&packed, sizeof(packed));
	}
	return true;
}

template<typename TypeDef> bool Tag_SRATIONAL::DoSerialize(Binary& buff)
{
	UInt32 count = GetValue().IsList()?
		static_cast<UInt32>(Value_List::GetValueOwner(GetValue()).size()) : 1;
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	UInt32 offsetToValue = static_cast<UInt32>(_offsetToValue);
	Gurax_PackUInt32(tagPacked.variable.LONG.num, offsetToValue);
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_SRATIONAL::DoSerializePointed(Binary& buff)
{
	return true;
}

bool Tag_SRATIONAL::SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff, offset) : DoSerializePre<TypeDef_LE>(serialBuff, offset);
}

bool Tag_SRATIONAL::Serialize(Binary& buff, bool beFlag)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff) : DoSerialize<TypeDef_LE>(buff);
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

template<typename TypeDef> bool Tag_IFD::DoSerializePre(SerialBuff& serialBuff, size_t offsetToData)
{
	// nothing to do
	return true;
}

template<typename TypeDef> bool Tag_IFD::DoSerialize(Binary& buff)
{
	UInt32 count = 1;
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	UInt32 offsetToValue = static_cast<UInt32>(_offsetToValue);
	Gurax_PackUInt32(tagPacked.variable.LONG.num, offsetToValue);
	buff.Append(&tagPacked, sizeof(tagPacked));
	return true;
}

template<typename TypeDef> bool Tag_IFD::DoSerializePointed(Binary& buff)
{
	return true;
}

bool Tag_IFD::SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff, offset) : DoSerializePre<TypeDef_LE>(serialBuff, offset);
}

bool Tag_IFD::Serialize(Binary& buff, bool beFlag)
{
	return beFlag? DoSerialize<TypeDef_BE>(buff) : DoSerialize<TypeDef_LE>(buff);
}

bool Tag_IFD::SerializePointed(Binary& buff, bool beFlag)
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

Gurax_EndModuleScope(jpeg)
