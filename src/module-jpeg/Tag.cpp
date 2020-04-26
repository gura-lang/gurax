//==============================================================================
// Tag.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Tag
//------------------------------------------------------------------------------
Tag::Tag(UInt16 typeId, UInt16 tagId, const Symbol* pSymbol,
	size_t offset, size_t offsetToValue, Value* pValue, Value* pValueCooked) :
	_typeId(typeId), _tagId(tagId), _pSymbol(pSymbol),
	_offset(offset), _offsetToValue(offsetToValue), _pValue(pValue), _pValueCooked(pValueCooked)
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

template<typename TypeDef> bool Tag_BYTE::DoSerializePre(SerialBuff& serialBuff)
{
	_offsetToValue = _offset;
	return true;
}

template<typename TypeDef> bool Tag_BYTE::DoSerialize(SerialBuff& serialBuff) const
{
	const Binary& buff = Value_Binary::GetBinary(GetValue());
	UInt32 count = static_cast<UInt32>(buff.size());
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	if (count <= 4) {
		::memcpy(tagPacked.variable.BYTE, buff.data(), count);
	} else {
		UInt32 offset = static_cast<UInt32>(_offsetToValue);
		Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
	}
	serialBuff.GetBuff().append(reinterpret_cast<const UInt8*>(&tagPacked), sizeof(tagPacked));
	return true;
}

bool Tag_BYTE::SerializePre(SerialBuff& serialBuff, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff) : DoSerializePre<TypeDef_LE>(serialBuff);
}

bool Tag_BYTE::Serialize(SerialBuff& serialBuff, bool beFlag) const
{
	return beFlag? DoSerialize<TypeDef_BE>(serialBuff) : DoSerialize<TypeDef_LE>(serialBuff);
}

//------------------------------------------------------------------------------
// Tag_ASCII
//------------------------------------------------------------------------------
bool Tag_ASCII::CheckAcceptableValue(Value& value) const
{
	return value.IsType(VTYPE_String);
}

template<typename TypeDef> bool Tag_ASCII::DoSerializePre(SerialBuff& serialBuff)
{
	return true;
}

template<typename TypeDef> bool Tag_ASCII::DoSerialize(SerialBuff& serialBuff) const
{
	const String& str = Value_String::GetString(GetValue());
	UInt32 count = static_cast<UInt32>(str.size());
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	if (count <= 4) {
		::memcpy(tagPacked.variable.BYTE, str.data(), count);
	} else {
		UInt32 offset = static_cast<UInt32>(_offsetToValue);
		Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
	}
	serialBuff.GetBuff().append(reinterpret_cast<const UInt8*>(&tagPacked), sizeof(tagPacked));
	return true;
}

bool Tag_ASCII::SerializePre(SerialBuff& serialBuff, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff) : DoSerializePre<TypeDef_LE>(serialBuff);
}

bool Tag_ASCII::Serialize(SerialBuff& serialBuff, bool beFlag) const
{
	return beFlag? DoSerialize<TypeDef_BE>(serialBuff) : DoSerialize<TypeDef_LE>(serialBuff);
}

//------------------------------------------------------------------------------
// Tag_SHORT
//------------------------------------------------------------------------------
bool Tag_SHORT::CheckAcceptableValue(Value& value) const
{
	return CheckRangedNumber(value, 0x0000, 0xffff);
}

template<typename TypeDef> bool Tag_SHORT::DoSerializePre(SerialBuff& serialBuff)
{
	return true;
}

template<typename TypeDef> bool Tag_SHORT::DoSerialize(SerialBuff& serialBuff) const
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
			UInt32 offset = static_cast<UInt32>(_offsetToValue);
			Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
		}
	} else {
		UInt16 num = Value_Number::GetNumber<UInt16>(GetValue());
		UInt32 count = 1;
		tagPacked = MakeTagPacked<TypeDef>(count);
		Gurax_PackUInt16(tagPacked.variable.SHORT.num, num);
	}
	serialBuff.GetBuff().append(reinterpret_cast<const UInt8*>(&tagPacked), sizeof(tagPacked));
	return true;
}

bool Tag_SHORT::SerializePre(SerialBuff& serialBuff, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff) : DoSerializePre<TypeDef_LE>(serialBuff);
}

bool Tag_SHORT::Serialize(SerialBuff& serialBuff, bool beFlag) const
{
	return beFlag? DoSerialize<TypeDef_BE>(serialBuff) : DoSerialize<TypeDef_LE>(serialBuff);
}

//------------------------------------------------------------------------------
// Tag_LONG
//------------------------------------------------------------------------------
bool Tag_LONG::CheckAcceptableValue(Value& value) const
{
	return CheckRangedNumber(value, 0x00000000, 0xffffffff);
}

template<typename TypeDef> bool Tag_LONG::DoSerializePre(SerialBuff& serialBuff)
{
	return true;
}

template<typename TypeDef> bool Tag_LONG::DoSerialize(SerialBuff& serialBuff) const
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
			UInt32 offset = static_cast<UInt32>(_offsetToValue);
			Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
		}
	} else {
		UInt32 num = Value_Number::GetNumber<UInt32>(GetValue());
		UInt32 count = 1;
		tagPacked = MakeTagPacked<TypeDef>(count);
		Gurax_PackUInt32(tagPacked.variable.LONG.num, num);
	}
	serialBuff.GetBuff().append(reinterpret_cast<const UInt8*>(&tagPacked), sizeof(tagPacked));
	return true;
}

bool Tag_LONG::SerializePre(SerialBuff& serialBuff, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff) : DoSerializePre<TypeDef_LE>(serialBuff);
}

bool Tag_LONG::Serialize(SerialBuff& serialBuff, bool beFlag) const
{
	return beFlag? DoSerialize<TypeDef_BE>(serialBuff) : DoSerialize<TypeDef_LE>(serialBuff);
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

template<typename TypeDef> bool Tag_RATIONAL::DoSerializePre(SerialBuff& serialBuff)
{
	return true;
}

template<typename TypeDef> bool Tag_RATIONAL::DoSerialize(SerialBuff& serialBuff) const
{
	UInt32 count = GetValue().IsList()?
		static_cast<UInt32>(Value_List::GetValueOwner(GetValue()).size()) : 1;
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	UInt32 offset = static_cast<UInt32>(_offsetToValue);
	Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
	serialBuff.GetBuff().append(reinterpret_cast<const UInt8*>(&tagPacked), sizeof(tagPacked));
	return true;
}

bool Tag_RATIONAL::SerializePre(SerialBuff& serialBuff, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff) : DoSerializePre<TypeDef_LE>(serialBuff);
}

bool Tag_RATIONAL::Serialize(SerialBuff& serialBuff, bool beFlag) const
{
	return beFlag? DoSerialize<TypeDef_BE>(serialBuff) : DoSerialize<TypeDef_LE>(serialBuff);
}

//------------------------------------------------------------------------------
// Tag_UNDEFINED
//------------------------------------------------------------------------------
bool Tag_UNDEFINED::CheckAcceptableValue(Value& value) const
{
	return value.IsType(VTYPE_Binary);
}

template<typename TypeDef> bool Tag_UNDEFINED::DoSerializePre(SerialBuff& serialBuff)
{
	return true;
}

template<typename TypeDef> bool Tag_UNDEFINED::DoSerialize(SerialBuff& serialBuff) const
{
	const Binary& buff = Value_Binary::GetBinary(GetValue());
	UInt32 count = static_cast<UInt32>(buff.size());
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	if (count <= 4) {
		::memcpy(tagPacked.variable.BYTE, buff.data(), count);
	} else {
		UInt32 offset = static_cast<UInt32>(_offsetToValue);
		Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
	}
	serialBuff.GetBuff().append(reinterpret_cast<const UInt8*>(&tagPacked), sizeof(tagPacked));
	return true;
}

bool Tag_UNDEFINED::SerializePre(SerialBuff& serialBuff, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff) : DoSerializePre<TypeDef_LE>(serialBuff);
}

bool Tag_UNDEFINED::Serialize(SerialBuff& serialBuff, bool beFlag) const
{
	return beFlag? DoSerialize<TypeDef_BE>(serialBuff) : DoSerialize<TypeDef_LE>(serialBuff);
}

//------------------------------------------------------------------------------
// Tag_SLONG
//------------------------------------------------------------------------------
bool Tag_SLONG::CheckAcceptableValue(Value& value) const
{
	return CheckRangedNumber(value, -0x80000000, 0x7fffffff);
}

template<typename TypeDef> bool Tag_SLONG::DoSerializePre(SerialBuff& serialBuff)
{
	return true;
}

template<typename TypeDef> bool Tag_SLONG::DoSerialize(SerialBuff& serialBuff) const
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
			UInt32 offset = static_cast<UInt32>(_offsetToValue);
			Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
		}
	} else {
		Int32 num = Value_Number::GetNumber<Int32>(GetValue());
		UInt32 count = 1;
		tagPacked = MakeTagPacked<TypeDef>(count);
		Gurax_PackInt32(tagPacked.variable.LONG.num, num);
	}
	serialBuff.GetBuff().append(reinterpret_cast<const UInt8*>(&tagPacked), sizeof(tagPacked));
	return true;
}

bool Tag_SLONG::SerializePre(SerialBuff& serialBuff, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff) : DoSerializePre<TypeDef_LE>(serialBuff);
}

bool Tag_SLONG::Serialize(SerialBuff& serialBuff, bool beFlag) const
{
	return beFlag? DoSerialize<TypeDef_BE>(serialBuff) : DoSerialize<TypeDef_LE>(serialBuff);
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

template<typename TypeDef> bool Tag_SRATIONAL::DoSerializePre(SerialBuff& serialBuff)
{
	return true;
}

template<typename TypeDef> bool Tag_SRATIONAL::DoSerialize(SerialBuff& serialBuff) const
{
	UInt32 count = GetValue().IsList()?
		static_cast<UInt32>(Value_List::GetValueOwner(GetValue()).size()) : 1;
	typename TypeDef::TagPacked tagPacked = MakeTagPacked<TypeDef>(count);
	UInt32 offset = static_cast<UInt32>(_offsetToValue);
	Gurax_PackUInt32(tagPacked.variable.LONG.num, offset);
	serialBuff.GetBuff().append(reinterpret_cast<const UInt8*>(&tagPacked), sizeof(tagPacked));
	return true;
}

bool Tag_SRATIONAL::SerializePre(SerialBuff& serialBuff, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff) : DoSerializePre<TypeDef_LE>(serialBuff);
}

bool Tag_SRATIONAL::Serialize(SerialBuff& serialBuff, bool beFlag) const
{
	return beFlag? DoSerialize<TypeDef_BE>(serialBuff) : DoSerialize<TypeDef_LE>(serialBuff);
}

//------------------------------------------------------------------------------
// Tag_IFD
//------------------------------------------------------------------------------
bool Tag_IFD::CheckAcceptableValue(Value& value) const
{
	return false;
}

template<typename TypeDef> bool Tag_IFD::DoSerializePre(SerialBuff& serialBuff)
{
	return true;
}

template<typename TypeDef> bool Tag_IFD::DoSerialize(SerialBuff& serialBuff) const
{
	return true;
}

bool Tag_IFD::SerializePre(SerialBuff& serialBuff, bool beFlag)
{
	return beFlag? DoSerializePre<TypeDef_BE>(serialBuff) : DoSerializePre<TypeDef_LE>(serialBuff);
}

bool Tag_IFD::Serialize(SerialBuff& serialBuff, bool beFlag) const
{
	return beFlag? DoSerialize<TypeDef_BE>(serialBuff) : DoSerialize<TypeDef_LE>(serialBuff);
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
