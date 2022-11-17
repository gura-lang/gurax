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
			_beFlag = true;
			size_t offset = Gurax_UnpackUInt32(hdr.offset0thIFD);
			if (Gurax_UnpackUInt16(hdr.code) != 0x002a || bytesAvail < offset) {
				IssueError_InvalidFormat();
				return false;
			}
			_pIFD0.reset(IFD::Deserialize<TypeDef_BE>(
						pBuff, bytesAvail, offset, Gurax_Symbol(ifd0), &offset));
			if (!_pIFD0) return false;
			if (offset != 0) {
				_pIFD1.reset(IFD::Deserialize<TypeDef_BE>(
						pBuff, bytesAvail, offset, Gurax_Symbol(ifd1), &offset));
				if (!_pIFD1) return false;
			}
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
			_pIFD0.reset(IFD::Deserialize<TypeDef_LE>(
						pBuff, bytesAvail, offset, Gurax_Symbol(ifd0), &offset));
			if (!_pIFD0) return false;
			if (offset != 0) {
				_pIFD1.reset(IFD::Deserialize<TypeDef_LE>(
						pBuff, bytesAvail, offset, Gurax_Symbol(ifd1), &offset));
				if (!_pIFD1) return false;
			}
		} else {
			IssueError_InvalidFormat();
			return false;
		}
	} while (0);
	return true;
}

bool Exif::WriteToStream(Stream& stream)
{
	return UpdateBinary() && Segment::WriteToStream(stream);
}

bool Exif::UpdateBinary()
{
	RefPtr<BinaryReferable> pBuff(new BinaryReferable());
	Binary& buff = pBuff->GetBinary();
	buff.Append("Exif\0\0", 6);
	const UInt32 offset0thIFD = 2 + sizeof(TypeDef_BE::TIFFHeader);
	if (_beFlag) {
		buff.Append("MM", 2);
		TypeDef_BE::TIFFHeader hdr;
		Gurax_PackUInt16(hdr.code, 0x002a);
		Gurax_PackUInt32(hdr.offset0thIFD, offset0thIFD);
		buff.Append(&hdr, sizeof(hdr));
	} else {
		buff.Append("II", 2);
		TypeDef_LE::TIFFHeader hdr;
		Gurax_PackUInt16(hdr.code, 0x002a);
		Gurax_PackUInt32(hdr.offset0thIFD, offset0thIFD);
		buff.Append(&hdr, sizeof(hdr));
	}
	if (_pIFD0) {
		if (!_pIFD0->Serialize(buff, _beFlag)) return false;
		if (_pIFD1) {
			if (_beFlag) {
				Tag::ReplaceLONG<TypeDef_BE>(buff, _pIFD0->GetPosNextIFDOffset(), Tag::CalcOffset(buff));
			} else {
				Tag::ReplaceLONG<TypeDef_LE>(buff, _pIFD0->GetPosNextIFDOffset(), Tag::CalcOffset(buff));
			}
			if (!_pIFD1->Serialize(buff, _beFlag)) return false;
		}
	}
	_pBuff.reset(pBuff.release());
	return true;
}

void Exif::SetIFD0(IFD* pIFD)
{
	if (pIFD) pIFD->SetSymbolOfIFD(Gurax_Symbol(ifd0));
	_pIFD0.reset(pIFD);
}

void Exif::SetIFD1(IFD* pIFD)
{
	if (pIFD) pIFD->SetSymbolOfIFD(Gurax_Symbol(ifd1));
	_pIFD1.reset(pIFD);
}

String Exif::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("<jpeg.Segment:%s(Exif)>", GetMarkerSymbol()->GetName());
	return str;
}

Gurax_EndModuleScope(jpeg)
