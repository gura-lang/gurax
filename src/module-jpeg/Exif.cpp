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
			for (int i = 0; i < 2 && offset != 0; i++) {
				RefPtr<IFD> pIFD(IFD::ReadFromBuff<TypeDef_BE>(
								pBuff, bytesAvail, offset, nullptr, &offset));
				if (!pIFD) return false;
				_ifdOwner.push_back(pIFD.release());
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
			for (int i = 0; i < 2 && offset != 0; i++) {
				RefPtr<IFD> pIFD(IFD::ReadFromBuff<TypeDef_LE>(
								pBuff, bytesAvail, offset, nullptr, &offset));
				if (!pIFD) return false;
				_ifdOwner.push_back(pIFD.release());
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
	IFD* pIFDPrev = nullptr;
	for (IFD* pIFD : GetIFDOwner()) {
		if (!pIFDPrev) {
			// nothing to do
		} else if (_beFlag) {
			Tag::ReplaceLONG<TypeDef_BE>(buff, pIFDPrev->GetPosNextIFDOffset(), Tag::CalcOffset(buff));
		} else {
			Tag::ReplaceLONG<TypeDef_LE>(buff, pIFDPrev->GetPosNextIFDOffset(), Tag::CalcOffset(buff));
		}
		if (!pIFD->Serialize(buff, _beFlag)) return false;
		pIFDPrev = pIFD;
	}
	_pBuff.reset(pBuff.release());
	return true;
}

String Exif::ToString(const StringStyle& ss) const
{
	return "jpeg.Exif";
}

Gurax_EndModuleScope(jpeg)
