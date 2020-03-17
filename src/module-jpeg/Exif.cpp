//==============================================================================
// Exif.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Exif
//------------------------------------------------------------------------------
Value* Exif::CreateValue() const
{
	return new Value_Exif(Reference());
}

template<typename TypeDef> IFD* Exif::AnalyzeIFD(
	const Symbol* pSymbolOfIFD, const UInt8* buff, size_t bytesBuff, size_t offset)
{
	using IFDHeader_T	= typename TypeDef::IFDHeader;
	using RATIONAL_T	= typename TypeDef::RATIONAL;
	using SRATIONAL_T	= typename TypeDef::SRATIONAL;
	using SHORT_T		= typename TypeDef::SHORT;
	using LONG_T		= typename TypeDef::LONG;
	using SLONG_T		= typename TypeDef::SLONG;
	using Variable_T	= typename TypeDef::Variable;
	using TagPacked_T	= typename TypeDef::TagPacked;
	if (offset + sizeof(IFDHeader_T) > bytesBuff) {
		IssueError_InvalidFormat();
		return nullptr;
	}
	RefPtr<TagOwner> pTagOwner(new TagOwner());
	auto& hdr = *reinterpret_cast<const IFDHeader_T*>(buff + offset);
	size_t tagCount = Gurax_UnpackUInt16(hdr.tagCount);
	offset += sizeof(IFDHeader_T);
	if (offset + sizeof(TagPacked_T) * tagCount > bytesBuff) {
		IssueError_InvalidFormat();
		return nullptr;
	}
	for (size_t iTag = 0; iTag < tagCount; iTag++) {
		auto &tagPacked = *reinterpret_cast<const TagPacked_T*>(buff + offset);
		offset += sizeof(TagPacked_T);
		UInt16 tagId = Gurax_UnpackUInt16(tagPacked.tagId);
		UInt16 typeId = Gurax_UnpackUInt16(tagPacked.typeId);
		UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
		const Variable_T& variable = tagPacked.variable;
		const TagInfo* pTagInfo = TagInfo::LookupByTagId(pSymbolOfIFD, tagId);
		//::printf("[%04x] %s type:%04x, count=%d\n",
		//		 tagId, (pTagInfo == nullptr)? "(unknown)" : pTagInfo->name, typeId, count);
		if (pTagInfo && pTagInfo->nameForIFD) {
			size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
			const Symbol *pSymbolOfIFDSub = Symbol::Add(pTagInfo->nameForIFD);
			RefPtr<IFD> pIFD(AnalyzeIFD<TypeDef>(pSymbolOfIFDSub, buff, bytesBuff, offset));
			if (!pIFD) return nullptr;
			RefPtr<Value> pValue(new Value_IFD(pIFD.release()));
			pTagOwner->push_back(new Tag(tagId, typeId, pSymbolOfIFDSub, pValue.release()));
			continue;
		}
		const Symbol* pSymbol = pTagInfo? Symbol::Add(pTagInfo->name) : Symbol::Empty;
		RefPtr<Value> pValue;
		RefPtr<Value> pValueCooked;
		switch (typeId) {
		case TypeId::BYTE: {
			const UInt8* pBuff = variable.BYTE;
			if (count > 4) {
				size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
				if (offset + count * sizeof(UInt8) > bytesBuff) {
					IssueError_InvalidFormat();
					return nullptr;
				}
				pBuff = buff + offset;
			}
			pValue.reset(new Value_Binary(Binary(pBuff, count)));
			break;
		}
		case TypeId::ASCII: {
			const char* pBuff = variable.ASCII;
			if (count > 4) {
				size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
				if (offset + count * sizeof(char) > bytesBuff) {
					IssueError_InvalidFormat();
					return nullptr;
				}
				pBuff = reinterpret_cast<const char*>(buff + offset);
			}
			pValue.reset(new Value_String(String(pBuff, count)));
			break;
		}
		case TypeId::SHORT: {
			if (count == 1) {
				UInt16 num = Gurax_UnpackUInt16(variable.SHORT.num);
				pValue.reset(new Value_Number(num));
			} else if (count == 2) {
				UInt16 num1 = Gurax_UnpackUInt16(variable.SHORT.num);
				UInt16 num2 = Gurax_UnpackUInt16(variable.SHORT.num2nd);
				pValue.reset(Value_List::Create(new Value_Number(num1), new Value_Number(num2)));
			} else {
				size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
				if (offset + count * sizeof(SHORT_T) > bytesBuff) {
					IssueError_InvalidFormat();
					return nullptr;
				}
				RefPtr<ValueOwner> pValueOwner(new ValueOwner());
				pValueOwner->reserve(count);
				for (size_t i = 0; i < count; i++, offset += sizeof(SHORT_T)) {
					const SHORT_T* pSHORT = reinterpret_cast<const SHORT_T*>(buff + offset);
					UInt16 num = Gurax_UnpackUInt16(pSHORT->num);
					pValueOwner->push_back(new Value_Number(num));
				}
				pValue.reset(new Value_List(VTYPE_Number, pValueOwner.release()));
			}
			break;
		}
		case TypeId::LONG: {
			if (count == 1) {
				UInt32 num = Gurax_UnpackUInt32(variable.LONG.num);
				pValue.reset(new Value_Number(num));
			} else {
				size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
				if (offset + count * sizeof(LONG_T) > bytesBuff) {
					IssueError_InvalidFormat();
					return nullptr;
				}
				RefPtr<ValueOwner> pValueOwner(new ValueOwner());
				pValueOwner->reserve(count);
				for (size_t i = 0; i < count; i++, offset += sizeof(LONG_T)) {
					const LONG_T* pLONG = reinterpret_cast<const LONG_T*>(buff + offset);
					UInt32 num = Gurax_UnpackUInt32(pLONG->num);
					pValueOwner->push_back(new Value_Number(num));
				}
				pValue.reset(new Value_List(VTYPE_Number, pValueOwner.release()));
			}
			break;
		}
		case TypeId::RATIONAL: {
			size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
			if (offset + count * sizeof(RATIONAL_T) > bytesBuff) {
				IssueError_InvalidFormat();
				return nullptr;
			}
			if (count == 1) {
				const RATIONAL_T* pRATIONAL = reinterpret_cast<const RATIONAL_T*>(buff + offset);
				pValue.reset(CreateValueFromRATIONAL(*pRATIONAL));
				if (!pValue) return nullptr;
			} else {
				RefPtr<ValueOwner> pValueOwner(new ValueOwner());
				pValueOwner->reserve(count);
				for (size_t i = 0; i < count; i++, offset += sizeof(RATIONAL_T)) {
					const RATIONAL_T* pRATIONAL = reinterpret_cast<const RATIONAL_T*>(buff + offset);
					RefPtr<Value> pValueElem(CreateValueFromRATIONAL(*pRATIONAL));
					if (!pValueElem) return nullptr;
					pValueOwner->push_back(pValueElem.release());
				}
				pValue.reset(new Value_List(VTYPE_Number, pValueOwner.release()));
			}
			break;
		}
		case TypeId::UNDEFINED: {
			const UInt8* pBuff = variable.BYTE;
			if (count > 4) {
				size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
				if (offset + count * sizeof(UInt8) > bytesBuff) {
					IssueError_InvalidFormat();
					return nullptr;
				}
				pBuff = buff + offset;
			}
			pValue.reset(new Value_Binary(Binary(pBuff, count)));
			break;
		}
		case TypeId::SLONG: {
			if (count == 1) {
				Int32 num = Gurax_UnpackInt32(variable.SLONG.num);
				pValue.reset(new Value_Number(num));
			} else {
				size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
				if (offset + count * sizeof(SLONG_T) > bytesBuff) {
					IssueError_InvalidFormat();
					return nullptr;
				}
				RefPtr<ValueOwner> pValueOwner(new ValueOwner());
				pValueOwner->reserve(count);
				for (size_t i = 0; i < count; i++, offset += sizeof(SLONG_T)) {
					const SLONG_T* pSLONG = reinterpret_cast<const SLONG_T*>(buff + offset);
					Int32 num = Gurax_UnpackInt32(pSLONG->num);
					pValueOwner->push_back(new Value_Number(num));
				}
			}
			break;
		}
		case TypeId::SRATIONAL: {
			size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
			if (offset + count * sizeof(SRATIONAL_T) > bytesBuff) {
				IssueError_InvalidFormat();
				return nullptr;
			}
			if (count == 1) {
				const SRATIONAL_T* pSRATIONAL = reinterpret_cast<const SRATIONAL_T*>(buff + offset);
				pValue.reset(CreateValueFromSRATIONAL(*pSRATIONAL));
				if (!pValue) return nullptr;
			} else {
				RefPtr<ValueOwner> pValueOwner(new ValueOwner());
				pValueOwner->reserve(count);
				for (size_t i = 0; i < count; i++, offset += sizeof(SRATIONAL_T)) {
					const SRATIONAL_T* pSRATIONAL = reinterpret_cast<const SRATIONAL_T*>(buff + offset);
					RefPtr<Value> pValueElem(CreateValueFromSRATIONAL(*pSRATIONAL));
					if (!pValueElem) return nullptr;
					pValueOwner->push_back(pValueElem.release());
				}
				pValue.reset(new Value_List(VTYPE_Number, pValueOwner.release()));
			}
			break;
		}
		default: {
			IssueError_InvalidFormat();
			return nullptr;
		}
		}
		pTagOwner->push_back(new Tag(tagId, typeId, pSymbol, pValue.release()));
	}
	return new IFD(pTagOwner.release());
}

bool Exif::AnalyzeBinary()
{
	//GetBinary()->Dump(Basement::Inst.GetStreamCOut());
	const UInt8* pBuff = GetBinary()->data();
	size_t bytesAvail = GetBinary()->size();
	do {
		if (bytesAvail < 6 || ::memcmp(pBuff, "Exif\0\0", 6) != 0) {
			IssueError_InvalidFormat();
			return false;
		}
		pBuff += 6, bytesAvail -= 6;
		if (bytesAvail < 2) {
			IssueError_InvalidFormat();
			return false;
		} else if (::memcmp(pBuff, "MM", 2) == 0) {
			size_t bytes = sizeof(TypeDef_BE::TIFFHeader);
			if (bytesAvail - 2 < bytes) {
				IssueError_InvalidFormat();
				return false;
			}
			auto& hdr = *reinterpret_cast<const TypeDef_BE::TIFFHeader*>(pBuff + 2);
			_bigEndianFlag = true;
			size_t offset = Gurax_UnpackUInt32(hdr.offset0thIFD);
			if (Gurax_UnpackUInt16(hdr.code) != 0x002a || bytesAvail < offset) {
				IssueError_InvalidFormat();
				return false;
			}
			RefPtr<IFD> pIFD(AnalyzeIFD<TypeDef_BE>(nullptr, pBuff, bytesAvail, offset));
			if (!pIFD) return false;
			_ifdOwner.push_back(pIFD.release());
		} else if (::memcmp(pBuff, "II", 2) == 0) {
			size_t bytes = sizeof(TypeDef_LE::TIFFHeader);
			if (bytesAvail - 2 < bytes) {
				IssueError_InvalidFormat();
				return false;
			}
			auto& hdr = *reinterpret_cast<const TypeDef_LE::TIFFHeader*>(pBuff + 2);
			size_t offset = Gurax_UnpackUInt32(hdr.offset0thIFD);
			if (Gurax_UnpackUInt16(hdr.code) != 0x002a || bytesAvail < offset) {
				IssueError_InvalidFormat();
				return false;
			}
			RefPtr<IFD> pIFD(AnalyzeIFD<TypeDef_LE>(nullptr, pBuff, bytesAvail, offset));
			if (!pIFD) return false;
			_ifdOwner.push_back(pIFD.release());
		} else {
			IssueError_InvalidFormat();
			return false;
		}
	} while (0);

	return true;
}

bool Exif::Write(Stream& stream) const
{
	return Segment::Write(stream);
}

String Exif::ToString(const StringStyle& ss) const
{
	return "jpeg.Exif";
}

Gurax_EndModuleScope(jpeg)
